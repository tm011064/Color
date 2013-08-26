#include "ExactLengthChallengeScene.h"
#include "LayoutController.h"
#include "SimpleAudioEngine.h"
#include <algorithm>

using namespace cocos2d;

ExactLengthChallengeScene* ExactLengthChallengeScene::create(GameContext* gameContext, bool showSplashScreen, int challengeIndex
  , int totalEnabledButtons, float minButtonSignalLength, float maxButtonSignalLength
  , float minNextSignalDeltaFromLastEndTime, float maxNextSignalDeltaFromLastEndTime
  , ChallengePointScoreDefinition challengePointScoreDefinition)
{
  ExactLengthChallengeScene* scene = new ExactLengthChallengeScene(gameContext, showSplashScreen, challengeIndex
    , totalEnabledButtons, minButtonSignalLength, maxButtonSignalLength
    , minNextSignalDeltaFromLastEndTime, maxNextSignalDeltaFromLastEndTime
    , EXACT_LENGTH, challengePointScoreDefinition);
  scene->init();

  return scene;
}

void ExactLengthChallengeScene::onLoadLayout()
{  
  switch (this->m_totalEnabledButtons)
  {
  case 1:
    this->m_buttons = LayoutController::createOneButton(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ExactLengthChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_ENDED, OSCIL);      
    break;

  case 2:
    this->m_buttons = LayoutController::createTwoButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ExactLengthChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_ENDED, OSCIL);      
    break;

  case 3:
        
    this->m_buttons = LayoutController::createThreeButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ExactLengthChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_ENDED, OSCIL);      
    break;

  case 4:
    this->m_buttons = LayoutController::createFourButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ExactLengthChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_ENDED, OSCIL);      
    break;
  }     
  
  this->m_totalVisibleButtons = this->m_buttons->count();

  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    this->addChild((GameButton*)o);
  }  
}

void ExactLengthChallengeScene::onLoadDescriptionPopup()
{       
  ccColor4F bgColor = { .0f, .0f, .0f, 1.0f };
  ccColor4F bgDialogColor = { 50.0f/255.0f, 158.0f/255.0f, 78.0f/255.0f, 1.0f };
  ccColor4F bgDialogBorderColor = { 1.0f, 1.0f, 1.0f, 1.0f };
  
  /********** DESCRIPTION POPUP **********/
  m_descriptionPopup = DescriptionPopup::create(
    this->m_pGameContext
    , callfuncO_selector(ExactLengthChallengeScene::newGameCallback)
    , this
    , "Balance\nChallenge"
    , "Target Score: " + UtilityHelper::convertToString(this->m_challengePointScoreDefinition.minimumTotalTimePercentageForOneStar * 100.0f, 0) 
      + " / 100\n\nRepeat the button\nsequence.\nTry to get as many\nas blinks as\npossible." // TODO (Roman): text
    , this->m_pGameContext->getImageMap()->getTile("iconBalance")
    , bgColor, bgDialogColor, bgDialogBorderColor);
  m_descriptionPopup->setZOrder(SPLASH_ZORDER);
  this->addChild(m_descriptionPopup);
  /********** DESCRIPTION POPUP **********/
}

void ExactLengthChallengeScene::onLayoutLoaded()
{  

}

void ExactLengthChallengeScene::startNewGame()
{  
  if (this->m_wildcardPopup->isVisible())
    this->m_wildcardPopup->hide();
  if (this->m_gameScorePopup->isVisible())
    this->m_gameScorePopup->hide();
    
  this->m_buttonSequence.clear();
  this->m_buttonSequenceIndex = 0;

  this->m_gameScore.starsEarned = 0;
  this->m_gameScore.level = 0;
  this->m_gameScore.totalButtonBonus = 0;
  this->m_gameScore.totalLevelBonus = 0;
  this->m_gameScore.totalPoints= 0;
  this->m_gameScore.totalTimeElapsed = 0;

  this->m_topBar->setScore(0);
  this->m_topBar->setLevel(1); 
  
  runSequenceAnimation();
}

void ExactLengthChallengeScene::runSequenceAnimation()
{
  this->m_sceneState = RUNNING_SEQUENCE_ANIMATION;
    
  m_buttonBlinkTimePeriods.clear();
  m_userPressedTimePeriods.clear();
  
  CCObject* o;
  GameButton* button = NULL;
  std::srand(time(NULL));
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    button = ((GameButton*)o);
    if (button->getIsEnabled())
    {
      ButtonBlinkTimePeriod buttonBlinkTimePeriod;
      buttonBlinkTimePeriod.duration = getRandom(m_minButtonSignalLength, m_maxButtonSignalLength);
      buttonBlinkTimePeriod.button = button;
      buttonBlinkTimePeriod.hasEnded = false;
      m_buttonBlinkTimePeriods.push_back(buttonBlinkTimePeriod);
    }
  }

  ButtonBlinkTimePeriod buttonBlinkTimePeriod;
  int index;
  for (int j = 0; j < 3; ++j)
  {// shuffle three times
    for (int i = 0; i < m_totalEnabledButtons - 1; ++i)
    {
      index = (int)round( getRandom(i + 1, m_totalEnabledButtons - 1) );
      buttonBlinkTimePeriod = m_buttonBlinkTimePeriods[index];
      m_buttonBlinkTimePeriods[index] = m_buttonBlinkTimePeriods[i];
      m_buttonBlinkTimePeriods[i] = buttonBlinkTimePeriod;
    }
  }
  
  float seqLength = (float)m_buttonSequence.size();
  float delay = BLINK_SPEED_NORMAL - (BLINK_SPEED_STEP * seqLength);
  if (delay < BLINK_SPEED_THRESHOLD)
    delay = BLINK_SPEED_THRESHOLD;
  
  m_buttonBlinkTimePeriods[0].startTime = UtilityHelper::getTimeValFromSeconds(.0f);
  m_buttonBlinkTimePeriods[0].endTime = UtilityHelper::getTimeValFromSeconds(m_buttonBlinkTimePeriods[0].duration);

  this->runAction(CCSequence::create(CCDelayTime::create(delay)
                                   , CCCallFuncO::create(this, callfuncO_selector(ExactLengthChallengeScene::startButtonBlinkCallback), m_buttonBlinkTimePeriods[0].button), NULL));
  this->runAction(CCSequence::create(CCDelayTime::create(delay + m_buttonBlinkTimePeriods[0].duration)
                                   , CCCallFuncO::create(this, callfuncO_selector(ExactLengthChallengeScene::endButtonBlinkCallback), m_buttonBlinkTimePeriods[0].button), NULL));
  
  for (int i = 1; i < m_totalEnabledButtons; ++i)
  {
    do
    {
      m_buttonBlinkTimePeriods[i].startTime = UtilityHelper::addSeconds(m_buttonBlinkTimePeriods[i - 1].endTime, getRandom(this->m_minNextSignalDeltaFromLastEndTime, this->m_maxNextSignalDeltaFromLastEndTime));
   }
    while (UtilityHelper::isLessThan(m_buttonBlinkTimePeriods[i].startTime, m_buttonBlinkTimePeriods[i - 1].startTime));
    
    m_buttonBlinkTimePeriods[i].endTime = UtilityHelper::addSeconds(m_buttonBlinkTimePeriods[i].startTime, m_buttonBlinkTimePeriods[i].duration);
   
    this->runAction(CCSequence::create(CCDelayTime::create(delay + UtilityHelper::getSeconds(m_buttonBlinkTimePeriods[i].startTime))
                                    , CCCallFuncO::create(this, callfuncO_selector(ExactLengthChallengeScene::startButtonBlinkCallback), m_buttonBlinkTimePeriods[i].button), NULL));
    this->runAction(CCSequence::create(CCDelayTime::create(delay + UtilityHelper::getSeconds(UtilityHelper::addSeconds(m_buttonBlinkTimePeriods[i].startTime, m_buttonBlinkTimePeriods[i].duration)))
                                    , CCCallFuncO::create(this, callfuncO_selector(ExactLengthChallengeScene::endButtonBlinkCallback), m_buttonBlinkTimePeriods[i].button), NULL));
 
  }
}

void ExactLengthChallengeScene::startButtonBlinkCallback(CCObject* o)
{
  for (int i = 0; i < m_totalEnabledButtons; ++i)
  {
    if (m_buttonBlinkTimePeriods[i].button == o)
    {
      m_buttonBlinkTimePeriods[i].button->playAnimation(PRESSING); 
      
      if (m_pGameContext->getIsSoundOn())
        m_buttonBlinkTimePeriods[i].button->playSound(false);
      break;
    }
  }
}
void ExactLengthChallengeScene::endButtonBlinkCallback(CCObject* o)
{ 
  if (this->m_sceneState == RUNNING_END_OF_GAME_ANIMATION)
    return;

  int totalReleasingButtons = 0;
  for (int i = 0; i < m_totalEnabledButtons; ++i)
  {
    if (m_buttonBlinkTimePeriods[i].button == o)
    {
      m_buttonBlinkTimePeriods[i].hasEnded = true;
      m_buttonBlinkTimePeriods[i].button->fadeOutSound(.16f);
      m_buttonBlinkTimePeriods[i].button->playAnimation(RELEASING);
    }
    if (m_buttonBlinkTimePeriods[i].hasEnded)
      totalReleasingButtons++;
  }
  if (totalReleasingButtons == m_totalEnabledButtons)
  {    
    this->m_sceneState = AWAITING_INPUT;
  }
}

void ExactLengthChallengeScene::buttonTouchEndedCallback(CCObject* pSender)
{
  int index = m_userPressedTimePeriods.size();
  ButtonBlinkTimePeriod buttonBlinkTimePeriod;
  buttonBlinkTimePeriod.button = (GameButton*)pSender;

  if (buttonBlinkTimePeriod.button != m_buttonBlinkTimePeriods[index].button)
  {
    onWrongButton((GameButton*)pSender, m_buttonBlinkTimePeriods[index].button);
    return;
  }

  buttonBlinkTimePeriod.startTime = buttonBlinkTimePeriod.button->getLastTouchStartedTime();  
  buttonBlinkTimePeriod.endTime = buttonBlinkTimePeriod.button->getLastTouchEndedTime();
  buttonBlinkTimePeriod.duration = buttonBlinkTimePeriod.button->getLastTouchDuration();
      
  m_userPressedTimePeriods.push_back(buttonBlinkTimePeriod);

  ButtonBlinkTimePeriodComparer comparer;
  std::sort(m_userPressedTimePeriods.begin(), m_userPressedTimePeriods.end(), comparer);  
  cc_timeval startTime = m_userPressedTimePeriods[0].startTime;
  
  m_userPressedTimePeriods[index].startOffset = UtilityHelper::getSeconds(
    UtilityHelper::substract(
      m_buttonBlinkTimePeriods[index].startTime
      , UtilityHelper::substract( m_userPressedTimePeriods[index].startTime, startTime )
    )
  );
  m_userPressedTimePeriods[index].durationOffset = m_buttonBlinkTimePeriods[index].duration - m_userPressedTimePeriods[index].duration;
  
  float durationCorrectPercentage = fabs(m_userPressedTimePeriods[index].durationOffset) / (m_buttonBlinkTimePeriods[index].duration == .0f ? 1.0f : m_buttonBlinkTimePeriods[index].duration);
  float buttonStartTime = UtilityHelper::getSeconds(m_buttonBlinkTimePeriods[index].startTime);
  m_userPressedTimePeriods[index].correctPercentage = 1 - (   fabs(m_userPressedTimePeriods[index].startOffset) / (buttonStartTime == .0f ? 1.0f : buttonStartTime)
                                                            + durationCorrectPercentage );
  durationCorrectPercentage = 1 - durationCorrectPercentage;

  this->m_gameScore.totalPoints += m_userPressedTimePeriods[index].correctPercentage * 100 * m_challengePointScoreDefinition.correctButtonScore;
  m_gameScore.totalPoints = (int)m_gameScore.totalPoints - (int)m_gameScore.totalPoints % 10;
  m_topBar->setScore((long)this->m_gameScore.totalPoints);
  m_pGameContext->setGameScore( m_gameScore );
  
  char str[128];
  //sprintf(str, "Timing: +%.3f s\nDuration: +%.3f s", fabs(m_userPressedTimePeriods[index].startOffset) 
  //                             , fabs(m_userPressedTimePeriods[index].durationOffset));
  sprintf(str, "+%.3f s", fabs(m_userPressedTimePeriods[index].durationOffset));
 
  int colorShade;  
  if (durationCorrectPercentage > .95f) { colorShade = 1; }
  else if (durationCorrectPercentage > .9f) { colorShade = 2; }
  else if (durationCorrectPercentage > .85f) { colorShade = 3; }
  else if (durationCorrectPercentage > .75f) { colorShade = 4; }
  else { colorShade = 5; }

  this->playConsoleLabelAnimation(str, 1.4f, 1.1f, .0f, colorShade);

  if (index + 1 == m_totalEnabledButtons)
  {
    this->m_sceneState = RUNNING_END_OF_GAME_ANIMATION;
    
    this->m_gameScore.averageButtonBlinkDurationOffset = 0;
    this->m_gameScore.averageButtonBlinkStartOffset = 0;
    this->m_gameScore.averageButtonBlinkPercentage = 0;
    for (int i = 0; i < m_totalEnabledButtons; ++i)
    {
      this->m_gameScore.averageButtonBlinkPercentage += m_userPressedTimePeriods[i].correctPercentage;
      this->m_gameScore.averageButtonBlinkStartOffset += fabs(m_userPressedTimePeriods[i].startOffset);
      this->m_gameScore.averageButtonBlinkDurationOffset += fabs(m_userPressedTimePeriods[i].durationOffset);
    }
    this->m_gameScore.averageButtonBlinkPercentage = this->m_gameScore.averageButtonBlinkPercentage / m_totalEnabledButtons;
    this->m_gameScore.averageButtonBlinkDurationOffset = this->m_gameScore.averageButtonBlinkDurationOffset / m_totalEnabledButtons;
    this->m_gameScore.averageButtonBlinkStartOffset = this->m_gameScore.averageButtonBlinkStartOffset / m_totalEnabledButtons;
    
    // TODO (Roman): scoring and popup
    this->m_gameScore.coinsEarned = round( this->m_gameScore.averageButtonBlinkPercentage * 10 * m_challengePointScoreDefinition.coinsEarnedMultiplier );
    this->m_pGameContext->setTotalCoins(this->m_pGameContext->getTotalCoins() + m_gameScore.coinsEarned);
          
    this->updateChallengeInfo(&this->m_challengePointScoreDefinition);
    m_pGameContext->setGameScore( m_gameScore );
    
    this->playBlinkButtonsAnimation(2, .25f, .8f);
    this->scheduleOnce(schedule_selector(ExactLengthChallengeScene::showGameScorePopupCallback), 2.0f);
  }
}

void ExactLengthChallengeScene::onWrongButton(GameButton* lastButtonPressed, GameButton* nextSequenceButton)
{  
  this->m_sceneState = RUNNING_END_OF_GAME_ANIMATION;
    
  this->m_gameScore.averageButtonBlinkDurationOffset = -1;
  this->m_gameScore.averageButtonBlinkStartOffset = -1;
  this->m_gameScore.averageButtonBlinkPercentage = 0;
  int totalUserPressedButtons = m_userPressedTimePeriods.size();

  for (int i = 0; i < m_totalEnabledButtons; ++i)
  {
    for (int j = 0; j < totalUserPressedButtons; j++)
    {
      if (m_buttonBlinkTimePeriods[i].button == m_userPressedTimePeriods[j].button)
      {
        this->m_gameScore.averageButtonBlinkPercentage += m_userPressedTimePeriods[j].correctPercentage;
        break;
      }
    }
  }
  this->m_gameScore.averageButtonBlinkPercentage = this->m_gameScore.averageButtonBlinkPercentage / m_totalEnabledButtons;
    
  this->m_gameScore.coinsEarned = round( this->m_gameScore.averageButtonBlinkPercentage * 10 * m_challengePointScoreDefinition.coinsEarnedMultiplier );
  this->m_pGameContext->setTotalCoins(this->m_pGameContext->getTotalCoins() + m_gameScore.coinsEarned);

  m_topBar->setScore((long)this->m_gameScore.totalPoints);
  m_pGameContext->setGameScore( m_gameScore );
    
  float wrongDelay = 1.6f;
  float correctBlinkDelay = 2.3f;
  this->m_eogTotalWrongButtonBlinks = 3;
  this->m_eogElaspedTime = 0;
  this->m_eogTargetTime = .8f;
  this->m_eogTargetTimeLastButton = .55f;
  this->m_eogElapsedTimeWrongButton = -wrongDelay;
  
  this->m_nextSequenceButton = nextSequenceButton;
  this->m_lastButtonPressed = lastButtonPressed;
  m_lastButtonPressed->playAnimation(PRESSED);

  this->schedule(schedule_selector(ExactLengthChallengeScene::eogGrayOutButtons), 0.021f); // framerate: 1/48
  this->schedule(schedule_selector(ExactLengthChallengeScene::eogGrayOutLastButton), 0.021f, -1, wrongDelay); // framerate: 1/48
  this->schedule(schedule_selector(ExactLengthChallengeScene::eogReleaseLastButton), 0.021f, 0, wrongDelay); // framerate: 1/48
  this->schedule(schedule_selector(ExactLengthChallengeScene::eogBlinkCorrectButton), 0.2f, -1, correctBlinkDelay); // framerate: 1/48    
}

int ExactLengthChallengeScene::updateChallengeInfo(const ChallengePointScoreDefinition* challengePointScoreDefinition)
{  
  int challengeInfo = m_pGameContext->getChallengeInfo(this->m_challengeIndex);
  this->m_gameScore.starsEarned = 0;

  if ( this->m_gameScore.averageButtonBlinkPercentage >= challengePointScoreDefinition->minimumTotalTimePercentageForThreeStars )
  {
    this->m_gameScore.starsEarned = 3;
    if (challengeInfo < 3)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 3);
  }
  else if ( this->m_gameScore.averageButtonBlinkPercentage >= challengePointScoreDefinition->minimumTotalTimePercentageForTwoStars )
  {       
    this->m_gameScore.starsEarned = 2;
    if (challengeInfo < 2)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 2);
  }
  else if ( this->m_gameScore.averageButtonBlinkPercentage >= challengePointScoreDefinition->minimumTotalTimePercentageForOneStar)
  {       
    this->m_gameScore.starsEarned = 1;
    if (challengeInfo < 1)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 1);
  }

  return this->m_gameScore.starsEarned;
}