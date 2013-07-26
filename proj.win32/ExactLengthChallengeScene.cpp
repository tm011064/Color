#include "ExactLengthChallengeScene.h"
#include "LayoutController.h"
#include <algorithm>

using namespace cocos2d;

ExactLengthChallengeScene* ExactLengthChallengeScene::create(GameContext* gameContext, int challengeIndex
  , int totalButtons, float minButtonSignalLength, float maxButtonSignalLength
  , float minNextSignalDeltaFromLastEndTime, float maxNextSignalDeltaFromLastEndTime
  , ChallengePointScoreDefinition challengePointScoreDefinition)
{
  ExactLengthChallengeScene* scene = new ExactLengthChallengeScene(gameContext, challengeIndex
    , totalButtons, minButtonSignalLength, maxButtonSignalLength
    , minNextSignalDeltaFromLastEndTime, maxNextSignalDeltaFromLastEndTime
    , EXACT_LENGTH, challengePointScoreDefinition);
  scene->init();

  return scene;
}

void ExactLengthChallengeScene::onLoadLayout()
{  
  switch (this->m_totalButtons)
  {
  case 1:
    this->m_buttons = LayoutController::createOneButton(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ExactLengthChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_ENDED);      
    break;

  case 2:
    this->m_buttons = LayoutController::createTwoButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ExactLengthChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_ENDED);      
    break;

  case 3:
        
    this->m_buttons = LayoutController::createThreeButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ExactLengthChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_ENDED);      
    break;

  case 4:
    this->m_buttons = LayoutController::createFourButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ExactLengthChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ExactLengthChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_ENDED);      
    break;
  }     

  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    this->addChild((GameButton*)o);
  }  

  // TODO (Roman): text
  m_descriptionPopup->setText("Repeat the sequence exactly\nhow you hear them!");
}

void ExactLengthChallengeScene::onLayoutLoaded()
{  
  this->m_loadingScreen->setVisible(false);  
  this->m_loadingScreenText->setVisible(false);  
}

void ExactLengthChallengeScene::startNewGame()
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
  
  runSequenceAnimation();
}

void ExactLengthChallengeScene::runSequenceAnimation()
{
  this->m_sceneState = RUNNING_SEQUENCE_ANIMATION;

  this->unschedule(schedule_selector(ExactLengthChallengeScene::update));
    
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
    for (int i = 0; i < m_totalButtons - 1; ++i)
    {
      index = (int)round( getRandom(i + 1, m_totalButtons - 1) );
      buttonBlinkTimePeriod = m_buttonBlinkTimePeriods[index];
      m_buttonBlinkTimePeriods[index] = m_buttonBlinkTimePeriods[i];
      m_buttonBlinkTimePeriods[i] = buttonBlinkTimePeriod;
    }
  }
  
  float seqLength = (float)m_buttonSequence.size();
  float delay = BLINK_SPEED_NORMAL - (BLINK_SPEED_STEP * seqLength);
  if (delay < BLINK_SPEED_THRESHOLD)
    delay = BLINK_SPEED_THRESHOLD;
  
  m_buttonBlinkTimePeriods[0].startTime = 0;
  m_buttonBlinkTimePeriods[0].endTime = m_buttonBlinkTimePeriods[0].duration;

  this->runAction(CCSequence::create(CCDelayTime::create(delay)
                                   , CCCallFuncO::create(this, callfuncO_selector(ExactLengthChallengeScene::startButtonBlinkCallback), m_buttonBlinkTimePeriods[0].button), NULL));
  this->runAction(CCSequence::create(CCDelayTime::create(delay + m_buttonBlinkTimePeriods[0].duration)
                                   , CCCallFuncO::create(this, callfuncO_selector(ExactLengthChallengeScene::endButtonBlinkCallback), m_buttonBlinkTimePeriods[0].button), NULL));
  
  for (int i = 1; i < m_totalButtons; ++i)
  {
    do
    {
      m_buttonBlinkTimePeriods[i].startTime = m_buttonBlinkTimePeriods[i - 1].endTime 
        + getRandom(this->m_minNextSignalDeltaFromLastEndTime, this->m_maxNextSignalDeltaFromLastEndTime);
    }
    while (m_buttonBlinkTimePeriods[i].startTime < m_buttonBlinkTimePeriods[i - 1].startTime);
    m_buttonBlinkTimePeriods[i].endTime = m_buttonBlinkTimePeriods[i].startTime + m_buttonBlinkTimePeriods[i].duration;
    
    this->runAction(CCSequence::create(CCDelayTime::create(delay + m_buttonBlinkTimePeriods[i].startTime)
                                     , CCCallFuncO::create(this, callfuncO_selector(ExactLengthChallengeScene::startButtonBlinkCallback), m_buttonBlinkTimePeriods[i].button), NULL));
    this->runAction(CCSequence::create(CCDelayTime::create(delay + m_buttonBlinkTimePeriods[i].startTime + m_buttonBlinkTimePeriods[i].duration)
                                     , CCCallFuncO::create(this, callfuncO_selector(ExactLengthChallengeScene::endButtonBlinkCallback), m_buttonBlinkTimePeriods[i].button), NULL));
  }
}

void ExactLengthChallengeScene::startButtonBlinkCallback(CCObject* o)
{
  for (int i = 0; i < m_totalButtons; ++i)
  {
    if (m_buttonBlinkTimePeriods[i].button == o)
    {
      m_buttonBlinkTimePeriods[i].button->playAnimation(PRESSING);
      break;
    }
  }
}
void ExactLengthChallengeScene::endButtonBlinkCallback(CCObject* o)
{  
  int totalReleasingButtons = 0;
  for (int i = 0; i < m_totalButtons; ++i)
  {
    if (m_buttonBlinkTimePeriods[i].button == o)
    {
      m_buttonBlinkTimePeriods[i].hasEnded = true;
      m_buttonBlinkTimePeriods[i].button->playAnimation(RELEASING);
    }
    if (m_buttonBlinkTimePeriods[i].hasEnded)
      totalReleasingButtons++;
  }
  if (totalReleasingButtons == m_totalButtons)
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

  buttonBlinkTimePeriod.startTime = buttonBlinkTimePeriod.button->getLastTouchStartedTime().tv_sec
                                  + buttonBlinkTimePeriod.button->getLastTouchStartedTime().tv_usec / 1000000.0f;
  
  buttonBlinkTimePeriod.endTime = buttonBlinkTimePeriod.button->getLastTouchEndedTime().tv_sec
                                + buttonBlinkTimePeriod.button->getLastTouchEndedTime().tv_usec / 1000000.0f;
  buttonBlinkTimePeriod.duration = buttonBlinkTimePeriod.button->getLastTouchDuration();
      
  m_userPressedTimePeriods.push_back(buttonBlinkTimePeriod);

  ButtonBlinkTimePeriodComparer comparer;
  std::sort(m_userPressedTimePeriods.begin(), m_userPressedTimePeriods.end(), comparer);  
  float startTime = m_userPressedTimePeriods[0].startTime;

  m_userPressedTimePeriods[index].startOffset = m_buttonBlinkTimePeriods[index].startTime - (m_userPressedTimePeriods[index].startTime - startTime);
  m_userPressedTimePeriods[index].durationOffset = m_buttonBlinkTimePeriods[index].duration - m_userPressedTimePeriods[index].duration;
  
  m_userPressedTimePeriods[index].correctPercentage = 1 - (   std::abs(m_userPressedTimePeriods[index].startOffset) / (m_buttonBlinkTimePeriods[index].startTime == .0f ? 1 : m_buttonBlinkTimePeriods[index].startTime)
                                                            + std::abs(m_userPressedTimePeriods[index].durationOffset) / (m_buttonBlinkTimePeriods[index].duration == .0f ? 1 : m_buttonBlinkTimePeriods[index].duration) );
  
  this->m_gameScore.totalPoints += m_userPressedTimePeriods[index].correctPercentage * 100 * m_challengePointScoreDefinition.correctButtonScore;
  m_gameScore.totalPoints = (int)m_gameScore.totalPoints - (int)m_gameScore.totalPoints % 10;
  m_topBar->setScore((long)this->m_gameScore.totalPoints);
  m_pGameContext->setGameScore( m_gameScore );
  
  char str[32];
  sprintf(str, "+%.3f s", /*std::abs(m_userPressedTimePeriods[index].startOffset) 
                        +*/ std::abs(m_userPressedTimePeriods[index].durationOffset));
  ccColor3B color;
  
  if (m_userPressedTimePeriods[index].correctPercentage > .95f) 
  {
    color.r = .0f;
    color.g = 255.0f;
    color.b = .0f;
  }
  else if (m_userPressedTimePeriods[index].correctPercentage > .9f)
  {
    color.r = 180.0f;
    color.g = 255.0f;
    color.b = .0f;
  }
  else if (m_userPressedTimePeriods[index].correctPercentage > .85f)
  {
    color.r = 250.0f;
    color.g = 255.0f;
    color.b = .0f;
  }
  else if (m_userPressedTimePeriods[index].correctPercentage > .75f)
  {
    color.r = 255.0f;
    color.g = 160.0f;
    color.b = .0f;
  }
  else 
  {
    color.r = 255.0f;
    color.g = 60.0f;
    color.b = .0f;
  }
  this->playConsoleLabelAnimation(str, 1.4f, 1.1f, .0f, color);

  if (index + 1 == m_totalButtons)
  {
    this->m_sceneState = RUNNING_END_OF_GAME_ANIMATION;
    
    this->m_gameScore.averageButtonBlinkDurationOffset = 0;
    this->m_gameScore.averageButtonBlinkStartOffset = 0;
    this->m_gameScore.averageButtonBlinkPercentage = 0;
    for (int i = 0; i < m_totalButtons; ++i)
    {
      this->m_gameScore.averageButtonBlinkPercentage += m_userPressedTimePeriods[i].correctPercentage;
      this->m_gameScore.averageButtonBlinkStartOffset += m_userPressedTimePeriods[i].startOffset;
      this->m_gameScore.averageButtonBlinkDurationOffset += m_userPressedTimePeriods[i].durationOffset;
    }
    this->m_gameScore.averageButtonBlinkPercentage = this->m_gameScore.averageButtonBlinkPercentage / m_totalButtons;
    this->m_gameScore.averageButtonBlinkDurationOffset = this->m_gameScore.averageButtonBlinkDurationOffset / m_totalButtons;
    this->m_gameScore.averageButtonBlinkStartOffset = this->m_gameScore.averageButtonBlinkStartOffset / m_totalButtons;
    
    // TODO (Roman): scoring and popup
    this->m_gameScore.coinsEarned = round( this->m_gameScore.averageButtonBlinkPercentage * 10 * m_challengePointScoreDefinition.coinsEarnedMultiplier );
    this->m_pGameContext->setTotalCoins(this->m_pGameContext->getTotalCoins() + m_gameScore.coinsEarned);
          
    m_pGameContext->setGameScore( m_gameScore );

    this->updateChallengeInfo(&this->m_challengePointScoreDefinition);
    
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

  for (int i = 0; i < m_totalButtons; ++i)
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
  this->m_gameScore.averageButtonBlinkPercentage = this->m_gameScore.averageButtonBlinkPercentage / m_totalButtons;
    
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
  if ( this->m_gameScore.averageButtonBlinkPercentage >= challengePointScoreDefinition->minimumTotalTimePercentageForThreeStars )
  {
    this->m_challengeCompleted = true;
    if (challengeInfo < 3)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 3);
    return 3;
  }
  else if ( this->m_gameScore.averageButtonBlinkPercentage >= challengePointScoreDefinition->minimumTotalTimePercentageForTwoStars )
  {       
    this->m_challengeCompleted = true;
    if (challengeInfo < 2)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 2);
    return 2;
  }
  else if ( this->m_gameScore.averageButtonBlinkPercentage >= challengePointScoreDefinition->minimumTotalTimePercentageForOneStar)
  {       
    this->m_challengeCompleted = true;
    if (challengeInfo < 1)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 1);
    return 1;
  }

  this->m_challengeCompleted = false;
  return 0;
}