#include "ArcadeGameScene.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>

using namespace cocos2d;

bool ArcadeGameScene::init()
{
  m_gameScore.totalPoints = 0;
  m_gameScore.totalLevelBonus = 0;
  m_gameScore.totalButtonBonus = 0;
  m_gameScore.level = 0;
  m_gameScore.totalTimeElapsed = 0;

  return CCScene::init();
}

void ArcadeGameScene::onExit()
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

void ArcadeGameScene::initialize(float dt)
{  
  CCPoint top = VisibleRect::top();
  CCPoint right = VisibleRect::right();
  CCPoint center = VisibleRect::center();
  CCPoint left = VisibleRect::left();
        
  CCRect visibleRect = VisibleRect::getVisibleRect();   
    
  float availableWidth = visibleRect.size.width / 2;         
      
  LayoutController::AddBackground(m_pGameContext, this, 0);
        
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
  
  int releasingFrames[] = { 0 };
  int pressingFrames[] = { 0 };
  m_consoleButton = ImageButton::create(this
    , callfuncO_selector( ArcadeGameScene::consoleButtonTouchEndedCallback )
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
    
  // we have the top bar, so we can get the border...
  this->m_anchor = ccpRounded(
    center.x
    , (   topBarBoundingBox.origin.y 
        - (consoleBackgroundScale * consoleBackgroundSize.height)/2 
        - topBarBoundingBox.size.height/8.0f
      ));
    
  float consoleHeight = consoleBackgroundSize.height * consoleBackgroundScale;
  float availableHeight = topBarBoundingBox.origin.y - visibleRect.origin.y;
    
  CCSize size = consoleBackground_l->getContentSize();
  consoleBackground_l->setPosition(ccp(this->m_anchor.x - consoleBackgroundScale*size.width/2, this->m_anchor.y + consoleBackgroundScale*size.height/2));
  consoleBackground_r->setPosition(ccp(this->m_anchor.x + consoleBackgroundScale*size.width/2, this->m_anchor.y + consoleBackgroundScale*size.height/2));
  consoleBackground_lb->setPosition(ccp(this->m_anchor.x - consoleBackgroundScale*size.width/2, this->m_anchor.y - consoleBackgroundScale*size.height/2));
  consoleBackground_rb->setPosition(ccp(this->m_anchor.x + consoleBackgroundScale*size.width/2, this->m_anchor.y - consoleBackgroundScale*size.height/2));
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
  m_wildcardPopup = WildcardPopup::create(
    this->m_pGameContext
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
  std::vector<WildcardButtonDefinition> wildcardButtonDefinitions;

  m_gameScorePopup = GameScorePopup::create(
    this->m_pGameContext
    , "GAME OVER"
    , callfuncO_selector(ArcadeGameScene::newGameCallback) 
    , callfuncO_selector(ArcadeGameScene::mainMenuCallback) 
    , NULL
    , wildcardButtonDefinitions
    , this
    , GSPTYPE_POINTS
    , GSPMODE_ARCADE);
  m_gameScorePopup->setPosition(ccp(0, 0));    
  m_gameScorePopup->setZOrder( MODAL_ZORDER ); 
    
  this->addChild(m_gameScorePopup);
  /********** MODAL LAYER **********/
    
  this->onPostInitialize();
    
  this->m_lastButtonPressedTime = new struct cc_timeval();
  this->m_firstUserSequencePressedTime = new struct cc_timeval();

  this->m_isLayoutInitialized = true;

  this->m_sceneState = LOADING;
  this->scheduleOnce(schedule_selector(ArcadeGameScene::preLoadCallback), 0);
}

void ArcadeGameScene::preLoadCallback(float dt)
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
}
void ArcadeGameScene::runSequenceAnimation(bool doAddButton, int startIndex, int endIndex)
{
  this->m_sceneState = RUNNING_SEQUENCE_ANIMATION;

  this->unschedule(schedule_selector(ArcadeGameScene::update));
  
  if (doAddButton)
  {
    std::srand(time(NULL));
    GameButton* button = (GameButton*)m_buttons->objectAtIndex(rand() % this->m_totalVisibleButtons);
    while (!button->getIsEnabled())
    {
      button = NULL;
      button = (GameButton*)m_buttons->objectAtIndex(rand() % this->m_totalVisibleButtons);
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
    }

    // animation has finished, now we allow input again
    this->m_buttonSequenceIndex = this->m_lastStartIndex;
    this->m_sceneState = AWAITING_INPUT;
  }
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
  if (m_buttonSequenceIndex >= m_buttonSequence.size())
    return; // this could happen on rapid clicks where the last click was not fully processed yet - like a lock...

  m_lastButtonPressed = ((GameButton*)pSender);
  m_nextSequenceButton = m_buttonSequence.at(m_buttonSequenceIndex);
    
  if (m_nextSequenceButton == m_lastButtonPressed)
  {// correct click

    this->m_lastButtonPressed->playAnimation(BLINK, false); // we don't play the sound here as this will be played only on a correct click
    
    float deltaTime = .0f;
    float bonus = 0;
    if ( m_buttonSequenceIndex > 0 )
    {
      deltaTime = updateTimeVal(this->m_lastButtonPressedTime);

      if (deltaTime < this->m_challengePointScoreDefinition.clickTimeThreshold)
      {
        bonus = this->m_challengePointScoreDefinition.maxTimeBonus * (1 - deltaTime / this->m_challengePointScoreDefinition.clickTimeThreshold); 
        bonus = (int)bonus - (int)bonus % 10;
        m_gameScore.totalButtonBonus += bonus;
        m_gameScore.totalPoints += bonus;
      }
    }
    else
    {
      CCTime::gettimeofdayCocos2d(this->m_firstUserSequencePressedTime, NULL);
    }
    this->m_buttonSequenceIndex++;

    m_gameScore.totalPoints += this->m_challengePointScoreDefinition.correctButtonScore;
    m_gameScore.totalPoints = (int)m_gameScore.totalPoints - (int)m_gameScore.totalPoints % 10;
    
    m_gameScore.level = m_buttonSequence.size();

    if (m_buttonSequenceIndex >= m_gameScore.level)
    {// correct, new animation

      deltaTime = updateTimeVal(this->m_firstUserSequencePressedTime);
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
    
      ccColor3B color = { 255.0f, 60.0f, .0f};
      if (mark > .92f)
      {
        sprintf(str, "PERFECT");
        color.r = .0f;
        color.g = 255.0f;
        color.b = .0f;
      }
      else if (mark > .88f)
      {
        sprintf(str, "GREAT");
        color.r = 180.0f;
        color.g = 255.0f;
        color.b = .0f;
      }
      else if (mark > .75)
      {
        sprintf(str, "GOOD");
        color.r = 250.0f;
        color.g = 255.0f;
        color.b = .0f;
      }
      else
      {  
        sprintf(str, "CORRECT");
        color.r = 255.0f;
        color.g = 160.0f;
        color.b = .0f;
      }
      
      m_levelDoneLabel->setString(str);

      m_levelDoneLabel->setColor(color);
      m_levelDoneLabel->setScale(1.0f);
      m_levelDoneLabel->runAction(CCSequence::create(
        CCFadeIn::create(.12f)
        , CCDelayTime::create(.2f)
        , CCFadeOut::create(.5f)
        , NULL));
      m_levelDoneLabel->runAction(CCSequence::create(
        CCScaleTo::create(1.2f, 1.1f)
        , NULL));

      this->scheduleOnce(schedule_selector(ArcadeGameScene::runSequenceAnimationTimerCallback), .32f);
    }      
  }
  else
  {// incorrect
    this->m_sceneState = RUNNING_END_OF_GAME_ANIMATION;
    
    m_topBar->setScore((long)this->m_gameScore.totalPoints);
    
    this->m_gameScore.coinsEarned = round( (float)m_gameScore.level * m_challengePointScoreDefinition.coinsEarnedMultiplier );
    this->m_pGameContext->setTotalCoins(this->m_pGameContext->getTotalCoins() + m_gameScore.coinsEarned);

    m_pGameContext->setGameScore( m_gameScore );

    onGameOver();

    if (this->m_pGameContext->getIsSoundOn())
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(m_pGameContext->getSoundPath("buttonsound_wrong").c_str());      
          
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
  
  ccColor3B orignialColor = m_lastButtonPressed->getOriginalColor();    
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
    
  hideSplashScreen();
  
  this->runAction(CCSequence::create(
    CCDelayTime::create(DEFAULT_NEW_GAME_START_DELAY)
    , CCCallFunc::create(this, callfunc_selector(ArcadeGameScene::startNewGame))
    , NULL));
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
  if (this->m_sceneState != AWAITING_INPUT)
    return;

  if (this->m_wildcardPopup->isVisible())
  {
    this->m_wildcardPopup->hide();
  }
  else
  {
    NavigationManager::showMainMenu(m_pGameContext, NEW, false, HOME);
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
  
  runSequenceAnimation(true, 0, -1);
}

/******** GAME OVER POPUP CALLBACKS  *********/
void ArcadeGameScene::newGameCallback(CCObject* pSender)
{
  this->startNewGame();
}

void ArcadeGameScene::mainMenuCallback(CCObject* pSender)
{
  NavigationManager::showMainMenu(m_pGameContext, NEW, false, HOME);
}  