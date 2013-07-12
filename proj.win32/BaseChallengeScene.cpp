#include "BaseChallengeScene.h"

using namespace cocos2d;
  
bool BaseChallengeScene::init()
{
  m_gameScore.totalPoints = 0;
  m_gameScore.totalLevelBonus = 0;
  m_gameScore.totalButtonBonus = 0;
  m_gameScore.level = 0;
  m_gameScore.totalTimeElapsed = 0;

  return CCScene::init();
}
void BaseChallengeScene::onExit()
{
  if(this->m_isLayoutInitialized)
  {   
    CC_SAFE_DELETE(m_lastButtonPressedTime);
    CC_SAFE_DELETE(m_lastLevelStartTime); 
  }

  CCScene::onExit();
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
    
    float availableWidth = visibleRect.size.width / 2;         

    // TODO (Roman): loading screen
    m_loadingScreenText = CCLabelBMFont::create("LOADING", m_pGameContext->getFontLargePath().c_str());
    m_loadingScreenText->setPosition(center);
    this->addChild(m_loadingScreenText, 1001);
    
    m_loadingScreen = RepeatingSprite::create(
      m_pGameContext
      , m_pGameContext->getImageMap()->getTile("background")
      , HORIZONTAL
      , NORMAL
      , visibleRect.size);    
    m_loadingScreen->setPosition(center);
    this->addChild(m_loadingScreen, 1000);
    
    
    RepeatingSprite* bg = RepeatingSprite::create(
      m_pGameContext
      , m_pGameContext->getImageMap()->getTile("background")
      , HORIZONTAL
      , NORMAL
      , visibleRect.size);    
    bg->setPosition(center);
    this->addChild(bg, 0);
    bg = NULL;
        
    /********** TOP BAR **********/
    m_topBar = new TopBar(m_pGameContext);
    m_topBar->autorelease();
    this->addChild(m_topBar);

    m_topBar->setLevel(1);      
    m_topBar->setScore(0);
    /********** TOP BAR **********/
    
    /********** CONSOLE **********/    
    m_consoleBackground = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("console"));
    this->addChild(m_consoleBackground);    
    
    CCSize consoleBackgroundSize = m_consoleBackground->getContentSize();
    float consoleBackgroundScale = availableWidth / (consoleBackgroundSize.width/2);

    m_consoleBackground->setScale(consoleBackgroundScale);
            
    CCSprite* consoleButtonBackground = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("gameConsoleButtonBackground"));
    consoleButtonBackground->setScale(consoleBackgroundScale);
    this->addChild(consoleButtonBackground);    
    
    int releasingFrames[] = { 0 };
    int pressingFrames[] = { 0 };
    m_consoleButton = ImageButton::create(this
      , callfuncO_selector( BaseChallengeScene::consoleButtonTouchEndedCallback )
      , NULL
      , m_pGameContext
      , "coin_large"
      , 0
      , 0
      , pressingFrames, 1
      , releasingFrames, 1
      , 0
      , 0
      , TOUCH_PRIORITY_NORMAL);
    m_consoleButton->setScale(consoleBackgroundScale);
    this->addChild(m_consoleButton);
    CCRect topBarBoundingBox = m_topBar->getBoundingBox();
    CCSize consoleSize = m_consoleBackground->getContentSize();
    
    // we have the top bar, so we can get the border...
    this->m_anchor = ccpRounded(
      center.x
      , (   topBarBoundingBox.origin.y 
          - (consoleBackgroundScale * consoleSize.height)/2 
          - topBarBoundingBox.size.height/8.0f
        ));
    
    float consoleHeight = consoleBackgroundSize.height * consoleBackgroundScale;
    float availableHeight = topBarBoundingBox.origin.y - visibleRect.origin.y;
    
    consoleButtonBackground->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));
    m_consoleBackground->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));
    m_consoleButton->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));

    /********** CONSOLE **********/

    /********** LEVEL DONE MESSAGE **********/
    m_levelDoneLabel = CCLabelBMFont::create("WELL DONE", m_pGameContext->getFontLargePath().c_str());
    float posY = this->m_anchor.y - consoleBackgroundSize.height*consoleBackgroundScale/2
                                  - m_pGameContext->getFontHeightLarge()/2;

    float minPosY = m_pGameContext->getFontHeightLarge()/2 * 1.1 
                    + m_pGameContext->getDefaultPadding(); // 1.1 = scale factor in animation
    if (posY < minPosY)
      posY = minPosY;

    m_levelDoneLabel->setPosition(ccp(this->m_anchor.x, posY));
    m_levelDoneLabel->setOpacity(.0f);
    this->addChild(m_levelDoneLabel, 1000);
    /********** LEVEL DONE MESSAGE **********/
	

    /********** MODAL LAYER **********/
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
    /********** MODAL LAYER **********/

    /********** MODAL LAYER **********/
    m_gameScorePopup = new GameScorePopup(
      this->m_pGameContext
      , callfuncO_selector(BaseChallengeScene::newGameCallback) 
      , callfuncO_selector(BaseChallengeScene::mainMenuCallback) 
      , this
      );
    m_gameScorePopup->autorelease();
    m_gameScorePopup->setPosition(ccp(0, 0));    
    m_gameScorePopup->setZOrder( MODAL_ZORDER ); 
    
    this->addChild(m_gameScorePopup);
    /********** MODAL LAYER **********/
        
    /********** DESCRIPTION POPUP **********/
    m_descriptionPopup = new DescriptionPopup(
      this->m_pGameContext
      , callfuncO_selector(BaseChallengeScene::newGameCallback)
      , this);
    m_descriptionPopup->setZOrder(100);
    this->addChild(m_descriptionPopup);
    /********** DESCRIPTION POPUP **********/
	
    this->onLoadLayout();
    
    this->m_lastButtonPressedTime = new struct cc_timeval();
    this->m_lastLevelStartTime = new struct cc_timeval();

    this->m_isLayoutInitialized = true;

    this->m_sceneState = LOADING;
    this->scheduleOnce(schedule_selector(BaseChallengeScene::preLoadCallback), 0);
  }
}

void BaseChallengeScene::preLoadCallback(float dt)
{  
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

  this->onPreLoad();
}

void BaseChallengeScene::buttonBlinkCallback(CCObject* pSender)
{
  onSequenceBlinkCallback((GameButton*)pSender);
}

int BaseChallengeScene::updateChallengeInfo(const ChallengePointScoreDefinition* challengePointScoreDefinition)
{
  int challengeInfo = m_pGameContext->getChallengeInfo(this->m_challengeIndex);
  if ( this->m_gameScore.totalPoints >= challengePointScoreDefinition->MininimumPointsForThreeStars )
  {
    m_pGameContext->setChallengeInfo(this->m_challengeIndex, 3);
    return 3;
  }
  else if ( this->m_gameScore.totalPoints >= challengePointScoreDefinition->MininimumPointsForTwoStars 
    && challengeInfo < 2 )
  {       
    m_pGameContext->setChallengeInfo(this->m_challengeIndex, 3);
    return 2;
  }
  else if ( this->m_gameScore.totalPoints >= challengePointScoreDefinition->MininimumPointsForOneStar
    && challengeInfo < 1 )
  {       
    m_pGameContext->setChallengeInfo(this->m_challengeIndex, 2);
    return 1;
  }

  return 0;
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