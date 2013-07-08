#include "BaseChallengeScene.h"

using namespace cocos2d;

BaseChallengeScene::BaseChallengeScene(GameContext* gameContext, int challengeIndex, ChallengeSceneType challengeSceneType, int totalButtons)   
  : BaseScene(gameContext)
  , m_isLayoutInitialized(false) 
  , m_bIsFirstDraw(true)
  , m_buttons(0)
  , m_loadingScreen(0)
  , m_lastButtonPressedTime(0)
  , m_lastLevelStartTime(0)
  , m_totalButtons(totalButtons)
  , m_challengeSceneType(challengeSceneType)
  , m_consoleBackground(NULL)
  , m_topBar(NULL)
  , m_wildcardPopup(NULL)
  , m_gameScorePopup(NULL)
  , m_challengeIndex(challengeIndex)
{ 
  m_gameScore.totalPoints = 0;
  m_gameScore.totalLevelBonus = 0;
  m_gameScore.totalButtonBonus = 0;
  m_gameScore.level = 0;
  m_gameScore.totalTimeElapsed = 0;
}
void BaseChallengeScene::onExit()
{
  if(this->m_isLayoutInitialized)
  {
    CC_SAFE_FREE(m_buttons);    
    CC_SAFE_DELETE(m_lastButtonPressedTime);
    CC_SAFE_DELETE(m_lastLevelStartTime);    
  }
}

void BaseChallengeScene::onEnter()
{
  CCScene::onEnter();
  if (!this->m_isLayoutInitialized)
  {              
    CCPoint top = VisibleRect::top();
    CCPoint right = VisibleRect::right();
    CCPoint center = VisibleRect::center();
    CCPoint left = VisibleRect::left();
        
    CCRect visibleRect = VisibleRect::getVisibleRect();   
    
    // set the anchor here, will be used later on
    this->m_anchor.setPoint(center.x, top.y * .5); // TODO (Roman): positioning   
        
    // TODO (Roman): loading screen
    m_loadingScreen = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("background"));
    m_loadingScreen->setPosition(center);
    m_loadingScreen->setVisible(true);

    this->addChild(m_loadingScreen, 1000);        
        
    
    RepeatingSprite* bg = RepeatingSprite::create(
      m_pGameContext
      , m_pGameContext->getImageMap()->getTile("background")
      , HORIZONTAL
      , NORMAL
      , visibleRect.size);
    this->addChild(bg, 0);
    bg = NULL;

    /********** CONSOLE **********/    
    m_consoleBackground = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("console"));
    m_consoleBackground->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));
    this->addChild(m_consoleBackground);    

    CCSize consoleBackgroundSize = m_consoleBackground->getContentSize();
    float availableWidth = visibleRect.size.width / 2;         
    float consoleBackgroundScale = availableWidth * 1.12 / (consoleBackgroundSize.height/2);

    m_consoleBackground->setScale(consoleBackgroundScale);    
        
    int releasingFrames[] = { 0 };
    int pressingFrames[] = { 0 };
    m_consoleButton = ImageButton::create(this
      , callfuncO_selector( BaseChallengeScene::consoleButtonTouchEndedCallback )
      , NULL
      , m_pGameContext
      , "gameConsoleButton"
      , 0
      , 0
      , pressingFrames, 1
      , releasingFrames, 1
      , 0
      , 0
      , TOUCH_PRIORITY_NORMAL);
    this->addChild(m_consoleButton);
    m_consoleButton->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));
    m_consoleButton->setScale(consoleBackgroundScale);
    /********** CONSOLE **********/
        
    /********** TOP BAR **********/
    m_topBar = new TopBar(m_pGameContext);
    m_topBar->autorelease();
    this->addChild(m_topBar);
    
    m_topBar->setLevel(1);      
    m_topBar->setScore(0);
    /********** TOP BAR **********/

    /********** WILDCARD POPUP **********/
    m_wildcardPopup = new WildcardPopup(
      this->m_pGameContext
      , callfuncO_selector(BaseChallengeScene::replaySequenceCallback) 
      , callfuncO_selector(BaseChallengeScene::showNextSequenceItemCallback) 
      , callfuncO_selector(BaseChallengeScene::replayFromCurrentCallback) 
      , callfuncO_selector(BaseChallengeScene::closeCallback) 
      , this
      );
    m_wildcardPopup->autorelease();
    m_wildcardPopup->setPosition(ccp(0, 0));    
    m_wildcardPopup->setZOrder( MODAL_ZORDER );
    
    this->addChild(m_wildcardPopup);
    /********** WILDCARD POPUP **********/

    /********** GAME SCORE POPUP **********/
    m_gameScorePopup = new GameScorePopup(
      this->m_pGameContext
      , callfuncO_selector(BaseChallengeScene::newGameCallback) 
      , callfuncO_selector(BaseChallengeScene::mainMenuCallback) 
      , this
      );
    m_gameScorePopup->setPosition(ccp(0, 0));    
    m_gameScorePopup->setZOrder( MODAL_ZORDER );
    
    this->addChild(m_gameScorePopup);
    /********** GAME SCORE POPUP **********/
    
    /********** DESCRIPTION POPUP **********/
    m_descriptionPopup = new DescriptionPopup(
      this->m_pGameContext
      , callfuncO_selector(BaseChallengeScene::newGameCallback)
      , this);
    m_descriptionPopup->setZOrder(100);
    this->addChild(m_descriptionPopup);
    /********** DESCRIPTION POPUP **********/

    this->onLoadLayout(); // for derived classes    
    
    this->m_lastButtonPressedTime = new struct cc_timeval();
    this->m_lastLevelStartTime = new struct cc_timeval();

    this->m_isLayoutInitialized = true;
  }    
}

void BaseChallengeScene::buttonBlinkCallback(CCObject* pSender)
{
  onSequenceBlinkCallback((GameButton*)pSender);
}

void BaseChallengeScene::draw()
{
  if ( this->m_bIsFirstDraw )
  {
    this->m_sceneState = LOADING;

    CCObject* o;
    CCARRAY_FOREACH(this->m_buttons, o)
    {
      if (!((GameButton*)o)->hasAlphaMap())
        ((GameButton*)o)->refreshAlphaMap(m_pGameContext->getOriginalSize(), m_pGameContext->getResolutionPolicy());  

      ((GameButton*)o)->load();
    }

    if (!this->m_consoleButton->hasAlphaMap())
      this->m_consoleButton->refreshAlphaMap(m_pGameContext->getOriginalSize(), m_pGameContext->getResolutionPolicy());

    this->m_wildcardPopup->hide();
    this->m_gameScorePopup->hide();
    this->m_descriptionPopup->show();
    
    this->m_bIsFirstDraw = false;
  }
  
  CCScene::draw();
}

int BaseChallengeScene::updateChallengeInfo(const ChallengePointScoreDefinition* challengePointScoreDefinition)
{
  int challengeInfo = m_pGameContext->getChallengeInfo(this->m_challengeIndex);
  if ( this->m_gameScore.totalPoints >= challengePointScoreDefinition->MininimumPointsForThreeStars )
  {
    m_pGameContext->setChallengeInfo(this->m_challengeIndex, 4);
    return 4;
  }
  else if ( this->m_gameScore.totalPoints >= challengePointScoreDefinition->MininimumPointsForTwoStars 
    && challengeInfo < 3 )
  {       
    m_pGameContext->setChallengeInfo(this->m_challengeIndex, 3);
    return 3;
  }
  else if ( this->m_gameScore.totalPoints >= challengePointScoreDefinition->MininimumPointsForOneStar
    && challengeInfo < 2 )
  {       
    m_pGameContext->setChallengeInfo(this->m_challengeIndex, 2);
    return 2;
  }

  return 1;
}
float BaseChallengeScene::updateTimeVal(cc_timeval* time)
{
  struct cc_timeval now;
  CCTime::gettimeofdayCocos2d(&now, NULL);

  float delta = MAX(0, (now.tv_sec - time->tv_sec) + (now.tv_usec - time->tv_usec) / 1000000.0f);
  *time = now;

  return delta;
}

void BaseChallengeScene::buttonTouchEndedCallback(CCObject* pSender)
{
  GameButton* bSeq = m_buttonSequence.at(m_buttonSequenceIndex);
  GameButton* button = ((GameButton*)pSender);
    
  if (bSeq == button)
  {
    this->onCorrectButtonPressed();
  }
  else
  {// incorrect
    this->onIncorrectButtonPressed();
  }
}

void BaseChallengeScene::buttonLoadedCallback(CCObject* pSender)
{  
  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    if (!((GameButton*)o)->getIsLoaded())
      return;
  }

  this->onLayoutLoaded();
}

void BaseChallengeScene::consoleButtonTouchEndedCallback(CCObject* pSender)
{
  if (this->m_sceneState != AWAITING_INPUT)
    return;

  m_wildcardPopup->refresh();
  m_wildcardPopup->show();
}

void BaseChallengeScene::onBackKeyPressed()
{  
  if (this->m_descriptionPopup->isVisible())
  {
    this->m_descriptionPopup->hide();
  }
  else if (this->m_wildcardPopup->isVisible())
  {
    this->m_wildcardPopup->hide();
  }
  else
  {
    NavigationManager::showScene(MENU_SCENE, m_pGameContext, NEW);
  }
}

/******** WILDCARD POPUP CALLBACKS  *********/
void BaseChallengeScene::replaySequenceCallback(CCObject* pSender)
{
  this->m_wildcardPopup->hide();

  // wildcard
  this->onReplaySequenceCallback();
}
void BaseChallengeScene::showNextSequenceItemCallback(CCObject* pSender)
{
  this->m_wildcardPopup->hide();
  
  // wildcard
  this->onShowNextSequenceItemCallback();
}
void BaseChallengeScene::replayFromCurrentCallback(CCObject* pSender)
{
  this->m_wildcardPopup->hide();
  
  // wildcard
  this->onReplayFromCurrentCallback();
}
void BaseChallengeScene::closeCallback(CCObject* pSender)
{
  this->m_wildcardPopup->hide();
}

/******** GAME OVER POPUP CALLBACKS  *********/
void BaseChallengeScene::newGameCallback(CCObject* pSender)
{
  if (this->m_descriptionPopup->isVisible())
  {
    this->m_descriptionPopup->hide();
  }
  this->startNewGame();
}

void BaseChallengeScene::mainMenuCallback(CCObject* pSender)
{
  NavigationManager::showScene(MENU_SCENE, m_pGameContext, NEW);
}



      /*
      // Note: this is all anchor point math in case we want the anchor point in the center and rotate around...
      CCPoint anch = this->m_buttonRed->getAnchorPoint();
            
      CCPoint position = ccp(this->m_anchor.x - size.width/2, this->m_anchor.y + size.height/2);

      float deltaX = (position.x - scaledWidth/2) - this->m_anchor.x;
      float deltaY = (position.y - scaledHeight/2) - this->m_anchor.y;
      
      float unitsX = deltaX / scaledWidth * -1;
      float unitsY = deltaY / scaledHeight * -1;

      //this->m_buttonRed->setAnchorPoint(ccp ( unitsX, unitsY ) );
      this->m_buttonRed->setPosition(VisibleRect::center());
      this->m_buttonRed->setAnchorPoint(ccp ( unitsX, unitsY ) );
      
      CCPoint anch2 = this->m_buttonRed->getAnchorPoint();
      */