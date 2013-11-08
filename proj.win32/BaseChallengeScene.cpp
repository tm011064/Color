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
    CC_SAFE_DELETE(m_firstUserSequencePressedTime); 
        
    m_lastButtonPressed = NULL;    
    m_nextSequenceButton = NULL;  
  }

  CCScene::onExit();
}

void BaseChallengeScene::onEnter()
{
  CCScene::onEnter();
  if (!this->m_isLayoutInitialized)
  {   
    this->m_isLayoutInitialized = true;
        
    this->onLoadDescriptionPopup();

    this->scheduleOnce(schedule_selector(BaseChallengeScene::initialize), 0.01f);
  }
}
void BaseChallengeScene::initialize(float dt)
{  
  this->onPreInitialize();

  CCPoint top = VisibleRect::top();
  CCPoint right = VisibleRect::right();
  CCPoint center = VisibleRect::center();
  CCPoint left = VisibleRect::left();
        
  CCRect visibleRect = VisibleRect::getVisibleRect();   
    
  LayoutController::addBackground(m_pGameContext, this, -1);

  float availableWidth = visibleRect.size.width / 2;    
            
  /********** TOP BAR **********/
  m_topBar = new TopBar(m_pGameContext);
  m_topBar->autorelease();
  this->addChild(m_topBar);

  m_topBar->setLevel(1);      
  m_topBar->setScore(0);
  /********** TOP BAR **********/
    
  /********** CONSOLE **********/      
  CCSpriteFrame* consoleTile = m_pGameContext->getImageMap()->getTile("console");
  CCSprite* consoleBackground_l = CCSprite::createWithSpriteFrame(consoleTile);
  CCSprite* consoleBackground_lb = CCSprite::createWithSpriteFrame(consoleTile);
  CCSprite* consoleBackground_r = CCSprite::createWithSpriteFrame(consoleTile);
  CCSprite* consoleBackground_rb = CCSprite::createWithSpriteFrame(consoleTile);

  this->addChild(consoleBackground_l);    
  this->addChild(consoleBackground_lb);    
  this->addChild(consoleBackground_r);    
  this->addChild(consoleBackground_rb);    
    
  CCSize consoleBackgroundSize = CCSizeMake( consoleBackground_l->getContentSize().width*2, consoleBackground_l->getContentSize().height*2);
  float consoleBackgroundScale = availableWidth / (consoleBackgroundSize.width/2);

  consoleBackground_l->setScale(consoleBackgroundScale);
  consoleBackground_lb->setScale(consoleBackgroundScale);
  consoleBackground_lb->setFlipY(true);
  consoleBackground_r->setScale(consoleBackgroundScale);
  consoleBackground_r->setFlipX(true);
  consoleBackground_rb->setScale(consoleBackgroundScale);
  consoleBackground_rb->setFlipY(true);
  consoleBackground_rb->setFlipX(true);
  
  std::string str;
  switch ( this->m_challengeSceneType )
  {
  case REACH_LEVEL: str = "console_button_memory"; break;
  case REPEAT_ONE_OFF: str = "console_button_speed"; break;
  case EXACT_LENGTH: str = "console_button_balance"; break;
  case RHYTHM: str = "console_button_rhythm"; break;
  }

  CCSprite* consoleButtonBackground = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile(str));
  consoleButtonBackground->setScale(consoleBackgroundScale);
  this->addChild(consoleButtonBackground);
  
  CCRect topBarBoundingBox = m_topBar->getBoundingBox();
    
  // we have the top bar, so we can get the border...
  this->m_anchor = ccpRounded(
    center.x
    , (   topBarBoundingBox.origin.y 
        - (consoleBackgroundScale * consoleBackgroundSize.height)/2
        - topBarBoundingBox.size.height/8.0f
      ));
    
  float consoleHeight = consoleBackgroundSize.height * consoleBackgroundScale;
  float availableHeight = topBarBoundingBox.origin.y - visibleRect.origin.y;
    
  consoleButtonBackground->setPosition(ccp(this->m_anchor.x, this->m_anchor.y));
  CCSize size = consoleBackground_l->getContentSize();
  consoleBackground_l->setPosition(ccp(this->m_anchor.x - consoleBackgroundScale*size.width/2, this->m_anchor.y + consoleBackgroundScale*size.height/2));
  consoleBackground_r->setPosition(ccp(this->m_anchor.x + consoleBackgroundScale*size.width/2, this->m_anchor.y + consoleBackgroundScale*size.height/2));
  consoleBackground_lb->setPosition(ccp(this->m_anchor.x - consoleBackgroundScale*size.width/2, this->m_anchor.y - consoleBackgroundScale*size.height/2));
  consoleBackground_rb->setPosition(ccp(this->m_anchor.x + consoleBackgroundScale*size.width/2, this->m_anchor.y - consoleBackgroundScale*size.height/2));
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
  m_wildcardPopup = WildcardPopup::create(
    this->m_pGameContext
    , NULL
    , NULL 
    , NULL
    , callfuncO_selector(BaseChallengeScene::closeCallback) 
    , this
    );
  m_wildcardPopup->setPosition(ccp(0, 0));    
  m_wildcardPopup->setZOrder( MODAL_ZORDER );
    
  this->addChild(m_wildcardPopup);
  /********** MODAL LAYER **********/
    
  /********** MODAL LAYER **********/
  m_lifeTimeTickerPopup = LifeTimeTickerPopup::create(
    this->m_pGameContext
    , this
    , callfuncO_selector(BaseChallengeScene::newGameCallback) 
    );
  m_lifeTimeTickerPopup->setPosition(ccp(0, 0));    
  m_lifeTimeTickerPopup->setZOrder( MODAL_ZORDER ); 
    
  this->addChild(m_lifeTimeTickerPopup);
  /********** MODAL LAYER **********/  

  /********** MODAL LAYER **********/
  m_gameScorePopup = GameScorePopup::create(
    this->m_pGameContext
    , "GAME OVER"
    , callfuncO_selector(BaseChallengeScene::newGameCallback) 
    , callfuncO_selector(BaseChallengeScene::mainMenuCallback) 
    , callfuncO_selector(BaseChallengeScene::nextChallengeCallback) 
    , m_wildcardButtonDefinitions
    , this
    , m_gameScorePopupType
    , GSPMODE_CHALLENGE
    );
  m_gameScorePopup->setPosition(ccp(0, 0));    
  m_gameScorePopup->setZOrder( MODAL_ZORDER ); 
    
  this->addChild(m_gameScorePopup);
  /********** MODAL LAYER **********/
	
  this->onPostInitialize();
    
  this->m_lastButtonPressedTime = new struct cc_timeval();
  this->m_firstUserSequencePressedTime = new struct cc_timeval();

  this->m_isLayoutInitialized = true;

  this->m_sceneState = LOADING;
  this->scheduleOnce(schedule_selector(BaseChallengeScene::preLoadCallback), 0.1f);
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
  
  this->m_lifeTimeTickerPopup->hide();
  this->m_wildcardPopup->hide();
  this->m_gameScorePopup->hide();
}

void BaseChallengeScene::buttonLoadedCallback(CCObject* pSender)
{  
  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    if (!((GameButton*)o)->getIsLoaded())
      return;
  }

  this->m_descriptionPopup->setEnablePlayButton(true);
}

void BaseChallengeScene::buttonBlinkCallback(CCObject* pSender)
{
  onSequenceBlinkCallback((GameButton*)pSender);
}

int BaseChallengeScene::updateChallengeInfo(const ChallengePointScoreDefinition* challengePointScoreDefinition)
{
  int challengeInfo = m_pGameContext->getChallengeInfo(this->m_challengeIndex);
  this->m_gameScore.starsEarned = 0;

  if ( this->m_gameScore.totalPoints >= challengePointScoreDefinition->mininimumPointsForThreeStars )
  {
    this->m_gameScore.starsEarned = 3;
    if (challengeInfo < 3)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 3);
  }
  else if ( this->m_gameScore.totalPoints >= challengePointScoreDefinition->mininimumPointsForTwoStars )
  {       
    this->m_gameScore.starsEarned = 2;
    if (challengeInfo < 2)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 2);
  }
  else if ( this->m_gameScore.totalPoints >= challengePointScoreDefinition->mininimumPointsForOneStar )
  {       
    this->m_gameScore.starsEarned = 1;
    if (challengeInfo < 1)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 1);
  }

  return this->m_gameScore.starsEarned;
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
  if (m_buttonSequenceIndex >= m_buttonSequence.size()
    || this->m_sceneState != AWAITING_INPUT)
    return; // this could happen on rapid clicks where the last click was not fully processed yet - like a lock...
  
  m_lastButtonPressed = ((GameButton*)pSender);
  m_nextSequenceButton = m_buttonSequence.at(m_buttonSequenceIndex);
    
  if (m_nextSequenceButton == m_lastButtonPressed)
  {
    this->onCorrectButtonPressed();
  }
  else
  {// incorrect
    this->onIncorrectButtonPressed();
  }
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
  if (this->m_wildcardPopup->isVisible())
  {
    this->m_wildcardPopup->hide();
  }
  else if (this->m_gameScorePopup->isVisible())
  {
    NavigationManager::showMainMenu(m_pGameContext, NEW, false, STORY_MODE);
  }
  else if (this->m_lifeTimeTickerPopup->isVisible())
  {
    NavigationManager::showMainMenu(m_pGameContext, NEW, false, STORY_MODE);
  }
  else
  {    
    if (this->m_sceneState != AWAITING_INPUT)
      return;

    // TODO (Roman): check whether the user has started the game, if not, give him back his life...
    if ( !m_hasUserStartedGame )
    {
      this->m_pGameContext->setTotalLifes(this->m_pGameContext->getTotalLifes() + 1);
    }

    NavigationManager::showMainMenu(m_pGameContext, NEW, false, STORY_MODE);
  }
}

void BaseChallengeScene::playConsoleLabelAnimation(std::string text, int colorShade)
{ 
  this->playConsoleLabelAnimation(text, .82f, 1.1f, .0f, colorShade); 
}
void BaseChallengeScene::playConsoleLabelAnimation(std::string text, float d, float maxScale, float delay, int colorShade)
{
  ccColor3B color = { 255.0f, 60.0f, .0f};
  
  switch (colorShade)
  {
  case 1:
    color.r = .0f;
    color.g = 255.0f;
    color.b = .0f;
    break;
  case 2:
    color.r = 180.0f;
    color.g = 255.0f;
    color.b = .0f;
    break;
  case 3:
    color.r = 250.0f;
    color.g = 255.0f;
    color.b = .0f;
    break;
  case 4:
    color.r = 255.0f;
    color.g = 160.0f;
    color.b = .0f;
    break;
  case 5:
    color.r = 255.0f;
    color.g = 60.0f;
    color.b = .0f;
    break;
  }
  this->playConsoleLabelAnimation(text, d, maxScale, delay, color); 
}

void BaseChallengeScene::playConsoleLabelAnimation(std::string text){ this->playConsoleLabelAnimation(text, .82f, 1.1f, .0f); }
void BaseChallengeScene::playConsoleLabelAnimation(std::string text, float d, float maxScale, float delay)
{
  ccColor3B color = { 255.0f, 255.0f, 255.0f };
  playConsoleLabelAnimation(text, d, maxScale, delay, color);
}
void BaseChallengeScene::playConsoleLabelAnimation(std::string text, float d, float maxScale, float delay, ccColor3B color)
{
  m_levelDoneLabel->setString(text.c_str());

  m_levelDoneLabel->setScale(1.0f);

  float fadeInTime = .12f;
  float fadeOutTime = .5f;
  float delayTime = d - fadeInTime - fadeOutTime;
  if (delayTime < .0f)
  {
    fadeInTime = d*.2f;
    fadeOutTime = d*.8f;
    delayTime = .0f;
  }

  m_levelDoneLabel->setColor(color);
  m_levelDoneLabel->runAction(CCSequence::create(
    CCDelayTime::create( delay )
    , CCFadeIn::create( fadeInTime )
    , CCDelayTime::create( delayTime )
    , CCFadeOut::create( fadeOutTime )
    , NULL));
  m_levelDoneLabel->runAction(CCSequence::create(
    CCScaleTo::create(d, maxScale)
    , NULL));
}

void BaseChallengeScene::playHighlightButtonsAnimation(float d, float delay)
{
  this->scheduleOnce(schedule_selector(BaseChallengeScene::allButtonsPressingAnimationCallback), delay);
  this->scheduleOnce(schedule_selector(BaseChallengeScene::allButtonsReleaseAnimationCallback), delay + d);
}
void BaseChallengeScene::allButtonsPressingAnimationCallback(float dt)
{
  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    if (((GameButton*)o)->getIsEnabled())
      ((GameButton*)o)->playAnimation(PRESSING);      
  }
}
void BaseChallengeScene::allButtonsReleaseAnimationCallback(float dt)
{
  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    if (((GameButton*)o)->getIsEnabled())
      ((GameButton*)o)->playAnimation(RELEASING);      
  }
}

void BaseChallengeScene::playBlinkButtonsAnimation(int totalBlinks, float interval, float delay)
{
  this->schedule(schedule_selector(BaseChallengeScene::blinkButtonCallback), interval, totalBlinks, delay);
}
void BaseChallengeScene::blinkButtonCallback(float dt)
{
  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    if (((GameButton*)o)->getIsEnabled())
      ((GameButton*)o)->playAnimation(BLINK, true);      
  }
}

void BaseChallengeScene::showGameScorePopupCallback(float dt)
{
  m_gameScorePopup->show(!m_showWildcardScoreInfo, "play on?", m_showWildcardScoreInfo
    , m_wildcardScoreInfoLeft, m_wildcardScoreInfoRight);
}

/******** END OF GAME ANIMATION **********/

void BaseChallengeScene::eogReleaseLastButton(float dt)
{
  m_lastButtonPressed->playAnimation(RELEASING);
}
void BaseChallengeScene::eogBlinkCorrectButton(float dt)
{
  this->m_eogTotalWrongButtonBlinks--;
  if (this->m_eogTotalWrongButtonBlinks < 0)
  {
    this->m_nextSequenceButton->setColor(BUTTON_COLOR_BLACK);
    this->unschedule(schedule_selector(BaseChallengeScene::eogBlinkCorrectButton)); 
    this->schedule(schedule_selector(BaseChallengeScene::eogAnimationFinish), 0, 0, .65f); // framerate: 1/48        
  }
  else
  {
    this->m_nextSequenceButton->setColor(this->m_nextSequenceButton->getOriginalColor());
    this->m_nextSequenceButton->playAnimation(BLINK);
  }
}
void BaseChallengeScene::eogAnimationFinish(float dt)
{
  this->showGameScorePopupCallback(.0f);

  this->m_eogElaspedTime = 0;
  this->schedule(schedule_selector(BaseChallengeScene::eogResetButtons), 0.021f); // framerate: 1/48
}
void BaseChallengeScene::eogResetButtons(float dt)
{
  m_eogElaspedTime += dt;
  float percentageDone = this->m_eogElaspedTime / this->m_eogTargetTime;
  if (percentageDone >= 1.0)
  {
    percentageDone = 1.0;
    this->unschedule(schedule_selector(BaseChallengeScene::eogResetButtons));              
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
void BaseChallengeScene::eogGrayOutLastButton(float dt)
{  
  m_eogElapsedTimeWrongButton += dt;
  float percentageDone = this->m_eogElapsedTimeWrongButton / this->m_eogTargetTimeLastButton;
  if (percentageDone >= 1.0)
  {
    percentageDone = 1.0;
    this->unschedule(schedule_selector(BaseChallengeScene::eogGrayOutLastButton));              
  }
  
  ccColor3B  orignialColor = m_lastButtonPressed->getOriginalColor();    
  ccColor3B currentColor;
  currentColor.r = orignialColor.r + (float)(BUTTON_COLOR_BLACK.r - orignialColor.r) * percentageDone;
  currentColor.g = orignialColor.g + (float)(BUTTON_COLOR_BLACK.g - orignialColor.g) * percentageDone;
  currentColor.b = orignialColor.b + (float)(BUTTON_COLOR_BLACK.b - orignialColor.b) * percentageDone;

  m_lastButtonPressed->setColor(currentColor);  
}
void BaseChallengeScene::eogGrayOutButtons(float dt)
{
  m_eogElaspedTime += dt;
  float percentageDone = this->m_eogElaspedTime / this->m_eogTargetTime;
  if (percentageDone >= 1.0)
  {
    percentageDone = 1.0;
    this->unschedule(schedule_selector(BaseChallengeScene::eogGrayOutButtons));              
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

/******** WILDCARD POPUP CALLBACKS  *********/
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
  
  if (this->m_pGameContext->getTotalLifes() > 0)
  {
    this->m_hasUserStartedGame = false;

    this->m_pGameContext->setTotalLifes(this->m_pGameContext->getTotalLifes() - 1);
    this->m_wildcardPopup->hide();
    this->m_gameScorePopup->hide();
    this->m_lifeTimeTickerPopup->hide();
    
    this->runAction(CCSequence::create(
      CCDelayTime::create(DEFAULT_NEW_GAME_START_SHORT_DELAY)
      , CCCallFunc::create(this, callfunc_selector(BaseChallengeScene::startNewGame))
      , NULL));
  }
  else
  {
    // hide them in case they were visible...
    this->m_wildcardPopup->hide();
    this->m_gameScorePopup->hide();
    
    this->m_lifeTimeTickerPopup->show();
  }
}

void BaseChallengeScene::nextChallengeCallback(CCObject* pSender)
{
  NavigationManager::showChallengeScene(m_pGameContext, m_challengeIndex + 1, NEW, true);
}

void BaseChallengeScene::mainMenuCallback(CCObject* pSender)
{
  NavigationManager::showMainMenu(m_pGameContext, NEW, false, STORY_MODE);
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