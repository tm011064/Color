#include "ArcadeGameScene.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>

using namespace cocos2d;

ArcadeGameScene::ArcadeGameScene(GameContext* gameContext, SceneType sceneType, int totalButtons)   
  : BaseScene(gameContext)
  , m_isLayoutInitialized(false) 
  , m_bIsFirstDraw(true)
  , m_buttonScale(.0f)
  , m_buttons(NULL)
  , m_loadingScreen(0)
  , m_loadingScreenText(NULL)
  , m_lastButtonPressedTime(0)
  , m_lastLevelStartTime(0)
  , m_totalButtons(totalButtons)
  , m_sceneType(sceneType)
  , m_consoleBackground(NULL)
  , m_topBar(NULL)
  , m_wildcardPopup(NULL)
  , m_gameScorePopup(NULL)
  , m_lastButtonPressed(NULL)
  , m_nextSequenceButton(NULL)
{ 
  m_gameScore.totalPoints = 0;
  m_gameScore.totalLevelBonus = 0;
  m_gameScore.totalButtonBonus = 0;
  m_gameScore.level = 0;
  m_gameScore.totalTimeElapsed = 0;
}

ArcadeGameScene::~ArcadeGameScene()
{  
  
}

void ArcadeGameScene::onExit()
{
  if(this->m_isLayoutInitialized)
  {   
    CC_SAFE_DELETE(m_lastButtonPressedTime);
    CC_SAFE_DELETE(m_lastLevelStartTime); 
        
    m_lastButtonPressed = NULL;    
    m_nextSequenceButton = NULL;    
  }

  CCScene::onExit();
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
    m_loadingScreenText = CCLabelBMFont::create("LOADING", m_gameContext->getFontLargePath().c_str());
    m_loadingScreenText->setPosition(center);
    this->addChild(m_loadingScreenText, 1001);
    
    m_loadingScreen = RepeatingSprite::create(
      m_gameContext
      , m_gameContext->getImageMap()->getTile("background")
      , HORIZONTAL
      , NORMAL
      , visibleRect.size);    
    m_loadingScreen->setPosition(center);
    this->addChild(m_loadingScreen, 1000);
    
    
    RepeatingSprite* bg = RepeatingSprite::create(
      m_gameContext
      , m_gameContext->getImageMap()->getTile("background")
      , HORIZONTAL
      , NORMAL
      , visibleRect.size);    
    bg->setPosition(center);
    this->addChild(bg, 0);
    bg = NULL;
        
    /********** TOP BAR **********/
    m_topBar = new TopBar(m_gameContext);
    m_topBar->autorelease();
    this->addChild(m_topBar);

    m_topBar->setLevel(1);      
    m_topBar->setScore(0);
    /********** TOP BAR **********/
    
    /********** CONSOLE **********/    
    m_consoleBackground = CCSprite::createWithSpriteFrame(m_gameContext->getImageMap()->getTile("console"));
    this->addChild(m_consoleBackground);    
    
    CCSize consoleBackgroundSize = m_consoleBackground->getContentSize();
    float consoleBackgroundScale = availableWidth / (consoleBackgroundSize.width/2);

    m_consoleBackground->setScale(consoleBackgroundScale);
            
    CCSprite* consoleButtonBackground = CCSprite::createWithSpriteFrame(m_gameContext->getImageMap()->getTile("gameConsoleButtonBackground"));
    consoleButtonBackground->setScale(consoleBackgroundScale);
    this->addChild(consoleButtonBackground);    
    
    int releasingFrames[] = { 0 };
    int pressingFrames[] = { 0 };
    m_consoleButton = ImageButton::create(this
      , callfuncO_selector( ArcadeGameScene::consoleButtonTouchEndedCallback )
      , NULL
      , m_gameContext
      , "coin_large"
      , 0
      , 0
      , pressingFrames, 1
      , releasingFrames, 1
      , 0
      , 0
      , TOUCH_PRIORITY_NORMAL);

    CCRect topBarBoundingBox = m_topBar->getBoundingBox();
    CCSize consoleSize = m_consoleBackground->getContentSize();
    
    // we have the top bar, so we can get the border...
    this->m_anchor = ccpRounded(
      center.x
      , (topBarBoundingBox.origin.y - (consoleBackgroundScale * consoleSize.height)/2 - topBarBoundingBox.size.height/8.0f));
    
    consoleButtonBackground->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));
    m_consoleBackground->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));
    m_consoleButton->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));

    /********** CONSOLE **********/

    /********** LEVEL DONE MESSAGE **********/
    m_levelDoneLabel = CCLabelBMFont::create("WELL DONE", m_gameContext->getFontLargePath().c_str());
    m_levelDoneLabel->setPosition(ccp(this->m_anchor.x, this->m_anchor.y - consoleBackgroundSize.height*consoleBackgroundScale/2
                                                                         - m_gameContext->getFontHeightLarge()/2));
    m_levelDoneLabel->setOpacity(.0f);
    this->addChild(m_levelDoneLabel, 1000);
    /********** LEVEL DONE MESSAGE **********/
	

    /********** MODAL LAYER **********/
    m_wildcardPopup = new WildcardPopup(
      this->m_gameContext
      , callfuncO_selector(ArcadeGameScene::replaySequenceCallback) 
      , callfuncO_selector(ArcadeGameScene::showNextSequenceItemCallback) 
      , callfuncO_selector(ArcadeGameScene::replayFromCurrentCallback) 
      , callfuncO_selector(ArcadeGameScene::closeCallback) 
      , this
      );
    m_wildcardPopup->autorelease();
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
    while (!button->getIsEnabled())
    {
      button = NULL;
      button = (GameButton*)m_buttons->objectAtIndex(rand() % m_totalButtons);
    }
    m_buttonSequence.push_back(button);
    button = NULL;
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
  button = NULL;
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
  m_lastButtonPressed = ((GameButton*)pSender);
  m_nextSequenceButton = m_buttonSequence.at(m_buttonSequenceIndex);
    
  if (m_nextSequenceButton == m_lastButtonPressed)
  {// correct click
    m_lastButtonPressed->playSound();

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
      else
      {
        bonus = 0;
      }
      m_gameScore.totalPoints += this->m_challengePointScoreDefinition.levelBonus;
      m_gameScore.totalPoints = (int)m_gameScore.totalPoints - (int)m_gameScore.totalPoints % 10;
            
      m_topBar->setLevel(m_gameScore.level + 1);      
      m_topBar->setScore((long)this->m_gameScore.totalPoints);
 
      float mark = bonus / this->m_challengePointScoreDefinition.maxLevelTimeBonus;
      char str[256];  
    
      if (mark > .92f)
        sprintf(str, "PERFECT");
      else if (mark > .88f)
        sprintf(str, "GREAT");
      else if (mark > .75)
        sprintf(str, "GOOD");
      else
        sprintf(str, "CORRECT");
      
      m_levelDoneLabel->setString(str);

      m_levelDoneLabel->setScale(1.0f);
      m_levelDoneLabel->runAction(CCSequence::create(
        CCFadeIn::create(.12f)
        , CCDelayTime::create(.2f)
        , CCFadeOut::create(.5f)
        , NULL));
      m_levelDoneLabel->runAction(CCSequence::create(
        CCScaleTo::create(1.2f, 1.1)
        , NULL));

      this->scheduleOnce(schedule_selector(ArcadeGameScene::runSequenceAnimationTimerCallback), .32f);
    }      
  }
  else
  {// incorrect
    this->m_sceneState = RUNNING_END_OF_GAME_ANIMATION;
    
    m_topBar->setScore((long)this->m_gameScore.totalPoints);
    
    this->m_gameScore.coinsEarned = round( (float)m_gameScore.level * m_challengePointScoreDefinition.coinsEarnedMultiplier );
    this->m_gameContext->setTotalCoins(this->m_gameContext->getTotalCoins() + m_gameScore.coinsEarned);

    m_gameContext->setGameScore( m_gameScore );

    onGameOver();

    if (this->m_gameContext->getIsSoundOn())
    {      
      // TODO (Roman): global path
      std::string s = m_gameContext->getSoundPath() + "button_wrong.wav";
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s.c_str());      
    }
      
    float wrongDelay = 1.6f;
    float correctBlinkDelay = 2.3f;
    this->m_eogTotalWrongButtonBlinks = 3;
    this->m_eogElaspedTime = 0;
    this->m_eogTargetTime = .8f;
    this->m_eogTargetTimeLastButton = .55f;
    this->m_eogElapsedTimeWrongButton = -wrongDelay;
          
    m_lastButtonPressed->playAnimation(PRESSED);

    this->schedule(schedule_selector(ArcadeGameScene::eogGrayOutButtons), 0.021f); // framerate: 1/48
    this->schedule(schedule_selector(ArcadeGameScene::eogGrayOutLastButton), 0.021f, -1, wrongDelay); // framerate: 1/48
    this->schedule(schedule_selector(ArcadeGameScene::eogReleaseLastButton), 0.021f, 0, wrongDelay); // framerate: 1/48
    this->schedule(schedule_selector(ArcadeGameScene::eogBlinkCorrectButton), 0.2f, -1, correctBlinkDelay); // framerate: 1/48    
  }
}
void ArcadeGameScene::runSequenceAnimationTimerCallback(float dt)
{      
  runSequenceAnimation(true, 0, -1);
}
void ArcadeGameScene::eogReleaseLastButton(float dt)
{
  m_lastButtonPressed->playAnimation(RELEASING);
}
void ArcadeGameScene::eogBlinkCorrectButton(float dt)
{
  this->m_eogTotalWrongButtonBlinks--;
  if (this->m_eogTotalWrongButtonBlinks < 0)
  {
    this->m_nextSequenceButton->setColor(BUTTON_COLOR_BLACK);
    this->unschedule(schedule_selector(ArcadeGameScene::eogBlinkCorrectButton)); 
    this->schedule(schedule_selector(ArcadeGameScene::eogAnimationFinish), 0, 0, .65f); // framerate: 1/48        
  }
  else
  {
    this->m_nextSequenceButton->setColor(this->m_nextSequenceButton->getOriginalColor());
    this->m_nextSequenceButton->playAnimation(BLINK);
  }
}
void ArcadeGameScene::eogAnimationFinish(float dt)
{
  m_gameScorePopup->show();

  this->m_eogElaspedTime = 0;
  this->schedule(schedule_selector(ArcadeGameScene::eogResetButtons), 0.021f); // framerate: 1/48
}
void ArcadeGameScene::eogResetButtons(float dt)
{
  m_eogElaspedTime += dt;
  float percentageDone = this->m_eogElaspedTime / this->m_eogTargetTime;
  if (percentageDone >= 1.0)
  {
    percentageDone = 1.0;
    this->unschedule(schedule_selector(ArcadeGameScene::eogResetButtons));              
  }
  
  CCObject* o;
  ccColor3B orignialColor;
  ccColor3B currentColor;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    orignialColor = ((GameButton*)o)->getOriginalColor();
    
    currentColor.r = BUTTON_COLOR_BLACK.r + (float)(orignialColor.r - BUTTON_COLOR_BLACK.r) * percentageDone;
    currentColor.g = BUTTON_COLOR_BLACK.g + (float)(orignialColor.g - BUTTON_COLOR_BLACK.g) * percentageDone;
    currentColor.b = BUTTON_COLOR_BLACK.b + (float)(orignialColor.b - BUTTON_COLOR_BLACK.b) * percentageDone;

    ((GameButton*)o)->setColor(currentColor);
  }
}
void ArcadeGameScene::eogGrayOutLastButton(float dt)
{  
  m_eogElapsedTimeWrongButton += dt;
  float percentageDone = this->m_eogElapsedTimeWrongButton / this->m_eogTargetTimeLastButton;
  if (percentageDone >= 1.0)
  {
    percentageDone = 1.0;
    this->unschedule(schedule_selector(ArcadeGameScene::eogGrayOutLastButton));              
  }
  
  ccColor3B  orignialColor = m_lastButtonPressed->getOriginalColor();    
  ccColor3B currentColor;
  currentColor.r = orignialColor.r + (float)(BUTTON_COLOR_BLACK.r - orignialColor.r) * percentageDone;
  currentColor.g = orignialColor.g + (float)(BUTTON_COLOR_BLACK.g - orignialColor.g) * percentageDone;
  currentColor.b = orignialColor.b + (float)(BUTTON_COLOR_BLACK.b - orignialColor.b) * percentageDone;

  m_lastButtonPressed->setColor(currentColor);  
}
void ArcadeGameScene::eogGrayOutButtons(float dt)
{
  m_eogElaspedTime += dt;
  float percentageDone = this->m_eogElaspedTime / this->m_eogTargetTime;
  if (percentageDone >= 1.0)
  {
    percentageDone = 1.0;
    this->unschedule(schedule_selector(ArcadeGameScene::eogGrayOutButtons));              
  }
  
  CCObject* o;
  ccColor3B orignialColor;
  ccColor3B currentColor;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    if ( ((GameButton*)o) == m_lastButtonPressed )
      continue;

    orignialColor = ((GameButton*)o)->getOriginalColor();
    
    currentColor.r = orignialColor.r + (float)(BUTTON_COLOR_BLACK.r - orignialColor.r) * percentageDone;
    currentColor.g = orignialColor.g + (float)(BUTTON_COLOR_BLACK.g - orignialColor.g) * percentageDone;
    currentColor.b = orignialColor.b + (float)(BUTTON_COLOR_BLACK.b - orignialColor.b) * percentageDone;

    ((GameButton*)o)->setColor(currentColor);
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
  
  //this->scheduleOnce(schedule_selector(ArcadeGameScene::startNewGame), 3.0f);
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
    NavigationManager::showScene(MENU_SCENE, m_gameContext, NEW);
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
  this->m_loadingScreenText->setVisible(false);    
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