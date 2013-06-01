#include "ArcadeGameScene.h"
#include <cstdlib>

using namespace cocos2d;

ArcadeGameScene::ArcadeGameScene(GameContext* gameContext, SceneType sceneType, int totalButtons)   
  : BaseScene(gameContext)
  , m_isInitialized(false) 
  , m_isLayoutInitialized(false)
  , m_bIsFirstDraw(true)
  , m_buttonScale(.0f)
  , m_buttons(0)
  , m_loadingScreen(0)
  , m_lastButtonPressedTime(0)
  , m_lastLevelStartTime(0)
  , m_totalButtons(totalButtons)
  , m_sceneType(sceneType)
  , m_consoleBackground(NULL)
  , m_topBar(NULL)
  , m_wildcardPopup(NULL)
  , m_gameScorePopup(NULL)
{ 
  m_gameScore.totalPoints = 0;
  m_gameScore.totalLevelBonus = 0;
  m_gameScore.totalButtonBonus = 0;
  m_gameScore.level = 0;
  m_gameScore.totalTimeElapsed = 0;
}

ArcadeGameScene::~ArcadeGameScene()
{
  if(this->m_isInitialized)
  {
    CC_SAFE_FREE(m_buttons);    
    CC_SAFE_DELETE(m_lastButtonPressedTime);
    CC_SAFE_DELETE(m_lastLevelStartTime);    
  }
}

void ArcadeGameScene::onEnter()
{
  CCScene::onEnter();
  if (!this->m_isLayoutInitialized)
  {    
    CCPoint top = VisibleRect::top();
    CCPoint right = VisibleRect::right();
    CCPoint center = VisibleRect::center();
    CCPoint left = VisibleRect::left();
        
    CCRect visibleRect = VisibleRect::getVisibleRect();   
    
    float availableWidth = visibleRect.size.width / 2;         

    // TODO (Roman): loading screen
    m_loadingScreen = CCSprite::createWithSpriteFrame(m_gameContext->getImageMap()->getTile(0));
    m_loadingScreen->setPosition(center);
    m_loadingScreen->setVisible(true);

    this->addChild(m_loadingScreen, 1000);        

    m_backgroundNormal = CCSprite::createWithSpriteFrame(m_gameContext->getImageMap()->getTile(0));
    m_backgroundNormal->setPosition(center);
    m_loadingScreen->setVisible(true);
    this->addChild(m_backgroundNormal, 0);              
    
        
    /********** TOP BAR **********/
    m_topBar = new TopBar(m_gameContext);
    this->addChild(m_topBar);

    m_topBar->setLevel(1);      
    m_topBar->setScore(0);
    /********** TOP BAR **********/
    
    /********** CONSOLE **********/    
    m_consoleBackground = CCSprite::createWithSpriteFrame(m_gameContext->getImageMap()->getTile(1));
    this->addChild(m_consoleBackground);    
    
    CCSize consoleBackgroundSize = m_consoleBackground->getContentSize();
    float consoleBackgroundScale = availableWidth * 1.12 / (consoleBackgroundSize.height/2);

    m_consoleBackground->setScale(consoleBackgroundScale);
        
    int releasingFrames[] = { 9 };
    int pressingFrames[] = { 9 };
    m_consoleButton = ImageButton::create(this
      , callfuncO_selector( ArcadeGameScene::consoleButtonTouchEndedCallback )
      , NULL
      , m_gameContext
      , this->m_gameContext->getImageMapPListPath().c_str()
      , this->m_gameContext->getImageMapPngPath().c_str()
      , 9
      , 9
      , pressingFrames, 1
      , releasingFrames, 1
      , 9
      , 9
      , TOUCH_PRIORITY_NORMAL);
    m_consoleButton->setScale(consoleBackgroundScale);

    CCRect topBarBoundingBox = m_topBar->getBoundingBox();
    CCSize consoleSize = m_consoleBackground->getContentSize();
    
    // we have the top bar, so we can get the border...
    this->m_anchor = ccp(
      center.x
      , topBarBoundingBox.origin.y - (consoleBackgroundScale * consoleSize.height)/2 - topBarBoundingBox.size.height/8.0f);
    
    m_consoleBackground->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));
    m_consoleButton->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));

    /********** CONSOLE **********/

    /********** MODAL LAYER **********/
    m_wildcardPopup = new WildcardPopup(
      this->m_gameContext
      , callfuncO_selector(ArcadeGameScene::replaySequenceCallback) 
      , callfuncO_selector(ArcadeGameScene::showNextSequenceItemCallback) 
      , callfuncO_selector(ArcadeGameScene::replayFromCurrentCallback) 
      , callfuncO_selector(ArcadeGameScene::closeCallback) 
      , this
      );
    m_wildcardPopup->setPosition(ccp(0, 0));    
    m_wildcardPopup->setZOrder( MODAL_ZORDER );
    
    this->addChild(m_wildcardPopup);
    /********** MODAL LAYER **********/

    /********** MODAL LAYER **********/
    m_gameScorePopup = new GameScorePopup(
      this->m_gameContext
      , callfuncO_selector(ArcadeGameScene::newGameCallback) 
      , callfuncO_selector(ArcadeGameScene::mainMenuCallback) 
      , this
      );
    m_gameScorePopup->setPosition(ccp(0, 0));    
    m_gameScorePopup->setZOrder( MODAL_ZORDER ); 
    
    this->addChild(m_gameScorePopup);
    /********** MODAL LAYER **********/
    
    this->onLoadLayout();

    this->m_lastButtonPressedTime = new struct cc_timeval();
    this->m_lastLevelStartTime = new struct cc_timeval();

    this->m_isLayoutInitialized = true;
  }    
}

void ArcadeGameScene::runSequenceAnimation(bool doAddButton, int startIndex, int endIndex)
{
  this->m_sceneState = RUNNING_SEQUENCE_ANIMATION;

  this->unschedule(schedule_selector(ArcadeGameScene::update));
  
  if (doAddButton)
  {
    std::srand(time(NULL));
    GameButton* button = (GameButton*)m_buttons->objectAtIndex(rand() % m_totalButtons);
    m_buttonSequence.push_back(button);
  }

  m_buttonSequenceIndex = startIndex;

  this->m_lastStartIndex = startIndex;
  if (endIndex == -1)
    this->m_lastEndIndex = m_buttonSequence.size();
  else
    this->m_lastEndIndex = endIndex;

  float seqLength = (float)m_buttonSequence.size();
  float delay = BLINK_SPEED_NORMAL - (BLINK_SPEED_STEP * seqLength);
  if (delay < BLINK_SPEED_THRESHOLD)
    delay = BLINK_SPEED_THRESHOLD;
  
  this->schedule(schedule_selector(ArcadeGameScene::update), delay);
}

void ArcadeGameScene::update(float delta)
{  
  GameButton* button = m_buttonSequence.at(m_buttonSequenceIndex);
  
  button->playAnimation(BLINK);
  m_buttonSequenceIndex++;

  if (m_buttonSequenceIndex >= this->m_lastEndIndex)
  {
    this->unschedule(schedule_selector(ArcadeGameScene::update));
  }  
}

void ArcadeGameScene::buttonBlinkCallback(CCObject* pSender)
{
  GameButton* button = (GameButton*)pSender;
  if (m_buttonSequenceIndex >= this->m_lastEndIndex)
  {
    if (this->m_lastEndIndex == m_buttonSequence.size()
      && this->m_lastStartIndex == 0)
    {
      // this was a normal level run, so reset the time. We don't do that if the player used a wildcard in which
      // case the sequence animation might not have started from zero or the last index is not the last sequence element
      
      // reset timer
      CCTime::gettimeofdayCocos2d(this->m_lastButtonPressedTime, NULL);
      CCTime::gettimeofdayCocos2d(this->m_lastLevelStartTime, NULL);
    }

    // animation has finished, now we allow input again
    this->m_buttonSequenceIndex = this->m_lastStartIndex;
    this->m_sceneState = AWAITING_INPUT;
  }
}

void ArcadeGameScene::draw()
{
  if ( this->m_bIsFirstDraw )
  {
    this->m_sceneState = LOADING;

    CCObject* o;
    CCARRAY_FOREACH(this->m_buttons, o)
    {
      if (!((GameButton*)o)->hasAlphaMap())
        ((GameButton*)o)->refreshAlphaMap(m_gameContext->getOriginalSize(), m_gameContext->getResolutionPolicy());  

      ((GameButton*)o)->load();
    }

    if (!this->m_consoleButton->hasAlphaMap())
      this->m_consoleButton->refreshAlphaMap(m_gameContext->getOriginalSize(), m_gameContext->getResolutionPolicy());

    this->m_wildcardPopup->hide();
    this->m_gameScorePopup->hide();

    this->m_bIsFirstDraw = false;
  }
  
  CCScene::draw();

}

float ArcadeGameScene::updateTimeVal(cc_timeval* time)
{
  struct cc_timeval now;
  CCTime::gettimeofdayCocos2d(&now, NULL);

  float delta = MAX(0, (now.tv_sec - time->tv_sec) + (now.tv_usec - time->tv_usec) / 1000000.0f);
  *time = now;

  return delta;
}

void ArcadeGameScene::buttonTouchEndedCallback(CCObject* pSender)
{
  GameButton* bSeq = m_buttonSequence.at(m_buttonSequenceIndex);
  GameButton* button = ((GameButton*)pSender);
    
  if (bSeq == button)
  {// correct click
    this->m_buttonSequenceIndex++;

    float deltaTime = updateTimeVal(this->m_lastButtonPressedTime);

    float bonus = 0;
    if (deltaTime < this->m_challengePointScoreDefinition.clickTimeThreshold)
    {
      bonus = this->m_challengePointScoreDefinition.maxTimeBonus * (1 - deltaTime / this->m_challengePointScoreDefinition.clickTimeThreshold); 
      bonus = (int)bonus - (int)bonus % 10;
      m_gameScore.totalButtonBonus += bonus;
      m_gameScore.totalPoints += bonus;
    }
    m_gameScore.totalPoints += this->m_challengePointScoreDefinition.correctButtonScore;
    m_gameScore.totalPoints = (int)m_gameScore.totalPoints - (int)m_gameScore.totalPoints % 10;
    
    m_gameScore.level = m_buttonSequence.size();

    if (m_buttonSequenceIndex >= m_gameScore.level)
    {// correct, new animation

      deltaTime = updateTimeVal(this->m_lastLevelStartTime);
      float levelTimeThreshold = this->m_challengePointScoreDefinition.clickTimeThreshold * m_gameScore.level;
      if (deltaTime < levelTimeThreshold)
      {
        bonus = this->m_challengePointScoreDefinition.maxLevelTimeBonus * (1 - deltaTime / levelTimeThreshold);  
        bonus = (int)bonus - (int)bonus % 10;
        m_gameScore.totalLevelBonus += bonus;
        m_gameScore.totalPoints += bonus;
      }
      m_gameScore.totalPoints += this->m_challengePointScoreDefinition.levelBonus;
      m_gameScore.totalPoints = (int)m_gameScore.totalPoints - (int)m_gameScore.totalPoints % 10;

      this->m_gameContext->setTotalCoins(this->m_gameContext->getTotalCoins() + 1);           
      
      m_topBar->setLevel(m_gameScore.level + 1);      
      m_topBar->setScore((long)this->m_gameScore.totalPoints);

      runSequenceAnimation(true, 0, -1);
    }      
  }
  else
  {// incorrect
    
    m_topBar->setScore((long)this->m_gameScore.totalPoints);
    m_gameContext->setGameScore( m_gameScore );
    
    onGameOver();

    m_gameScorePopup->show();
  }
}
void ArcadeGameScene::buttonLoadedCallback(CCObject* pSender)
{  
  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    if (!((GameButton*)o)->getIsLoaded())
      return;
  }

  // GAME START
  this->startNewGame();
}

void ArcadeGameScene::consoleButtonTouchEndedCallback(CCObject* pSender)
{
  if (this->m_sceneState != AWAITING_INPUT)
    return;

  m_wildcardPopup->refresh();
  m_wildcardPopup->show();
}

void ArcadeGameScene::onBackKeyPressed()
{
  if (this->m_wildcardPopup->isVisible())
  {
    this->m_wildcardPopup->hide();
  }
  else
  {
    NavigationManager::showScene(MENU_SCENE, m_gameContext, PUSH);
  }
}

/******** WILDCARD POPUP CALLBACKS  *********/
void ArcadeGameScene::replaySequenceCallback(CCObject* pSender)
{
  this->m_wildcardPopup->hide();

  // wildcard
  runSequenceAnimation(false, 0, -1);
}
void ArcadeGameScene::showNextSequenceItemCallback(CCObject* pSender)
{
  this->m_wildcardPopup->hide();
  
  // wildcard
  runSequenceAnimation(false, m_buttonSequenceIndex, m_buttonSequenceIndex + 1);
}
void ArcadeGameScene::replayFromCurrentCallback(CCObject* pSender)
{
  this->m_wildcardPopup->hide();
  
  // wildcard
  runSequenceAnimation(false, m_buttonSequenceIndex, -1);
}
void ArcadeGameScene::closeCallback(CCObject* pSender)
{
  this->m_wildcardPopup->hide();
}

void ArcadeGameScene::startNewGame()
{  
  if (this->m_wildcardPopup->isVisible())
    this->m_wildcardPopup->hide();
  if (this->m_gameScorePopup->isVisible())
    this->m_gameScorePopup->hide();
    
  this->m_buttonSequence.clear();
  this->m_buttonSequenceIndex = 0;

  this->m_gameScore.level = 0;
  this->m_gameScore.totalButtonBonus = 0;
  this->m_gameScore.totalLevelBonus = 0;
  this->m_gameScore.totalPoints= 0;
  this->m_gameScore.totalTimeElapsed = 0;

  this->m_topBar->setScore(0);
  this->m_topBar->setLevel(1);

  this->m_loadingScreen->setVisible(false);  
  runSequenceAnimation(true, 0, -1);
}

/******** GAME OVER POPUP CALLBACKS  *********/
void ArcadeGameScene::newGameCallback(CCObject* pSender)
{
  this->startNewGame();
}

void ArcadeGameScene::mainMenuCallback(CCObject* pSender)
{
  NavigationManager::showScene(MENU_SCENE, m_gameContext, NEW);
}  