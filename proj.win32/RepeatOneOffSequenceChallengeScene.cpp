#include "RepeatOneOffSequenceChallengeScene.h"
#include "LayoutController.h"
#include <cstdlib>

using namespace cocos2d;

RepeatOneOffSequenceChallengeScene* RepeatOneOffSequenceChallengeScene::create(GameContext* gameContext, int challengeIndex
  , int totalButtons, ChallengePointScoreDefinition challengePointScoreDefinition, int levelToReach)
{
  RepeatOneOffSequenceChallengeScene* scene = new RepeatOneOffSequenceChallengeScene(gameContext, challengeIndex, totalButtons, REPEAT_ONE_OFF, challengePointScoreDefinition, levelToReach);
  scene->init();

  return scene;
}

void RepeatOneOffSequenceChallengeScene::onLoadLayout()
{  
  switch (this->m_totalButtons)
  {
  case 2:
    this->m_buttons = LayoutController::createTwoButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( RepeatOneOffSequenceChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( RepeatOneOffSequenceChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( RepeatOneOffSequenceChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_BEGAN, DRUMS);      
    break;

  case 3:
        
    this->m_buttons = LayoutController::createThreeButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( RepeatOneOffSequenceChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( RepeatOneOffSequenceChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( RepeatOneOffSequenceChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_BEGAN, DRUMS);      
    break;

  case 4:
    this->m_buttons = LayoutController::createFourButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( RepeatOneOffSequenceChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( RepeatOneOffSequenceChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( RepeatOneOffSequenceChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_BEGAN, DRUMS);      
    break;
  }       

  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    this->addChild((GameButton*)o);
  }  

  // TODO (Roman): text
  m_descriptionPopup->setText("Repeat the button sequence\nas quickly as you can!");
}

void RepeatOneOffSequenceChallengeScene::onLayoutLoaded()
{  
  this->m_loadingScreen->setVisible(false);  
  this->m_loadingScreenText->setVisible(false);  
}

void RepeatOneOffSequenceChallengeScene::startNewGame()
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

  GameButton* button = NULL;
  std::srand(time(NULL));
  for (int i = 0; i < this->m_levelToReach; ++i)
  {
    GameButton* button = (GameButton*)m_buttons->objectAtIndex(rand() % m_totalButtons);
    while (!button->getIsEnabled())
    {
      button = NULL;
      button = (GameButton*)m_buttons->objectAtIndex(rand() % m_totalButtons);
    }
    m_buttonSequence.push_back(button);
    button = NULL;
  }

  runSequenceAnimation(false, 0, -1);
}

void RepeatOneOffSequenceChallengeScene::runSequenceAnimation(bool doAddButton, int startIndex, int endIndex)
{
  this->m_sceneState = RUNNING_SEQUENCE_ANIMATION;

  this->unschedule(schedule_selector(RepeatOneOffSequenceChallengeScene::update));
  
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
  
  this->schedule(schedule_selector(RepeatOneOffSequenceChallengeScene::update), delay);
}

void RepeatOneOffSequenceChallengeScene::update(float delta)
{  
  GameButton* button = m_buttonSequence.at(m_buttonSequenceIndex);
  
  button->playAnimation(BLINK);
  m_buttonSequenceIndex++;

  if (m_buttonSequenceIndex >= this->m_lastEndIndex)
  {
    this->unschedule(schedule_selector(RepeatOneOffSequenceChallengeScene::update));
  }  
}

void RepeatOneOffSequenceChallengeScene::onSequenceBlinkCallback(GameButton* gameButton)
{
  // this method is called when the sequence animation buttons blink
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

void RepeatOneOffSequenceChallengeScene::onCorrectButtonPressed()
{
  this->m_buttonSequenceIndex++;
  this->m_lastButtonPressed->playSound();

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
  
  if (m_buttonSequenceIndex == m_levelToReach)
  {     
    this->m_sceneState = RUNNING_END_OF_GAME_ANIMATION; this->m_gameScore.coinsEarned = round( (float)m_gameScore.level * m_challengePointScoreDefinition.coinsEarnedMultiplier );
      
    this->m_pGameContext->setTotalCoins(this->m_pGameContext->getTotalCoins() + m_gameScore.coinsEarned);

    m_topBar->setScore((long)this->m_gameScore.totalPoints);
    m_pGameContext->setGameScore( m_gameScore );
      
    int levelReached = this->updateChallengeInfo(&this->m_challengePointScoreDefinition);
      
    this->playBlinkButtonsAnimation(2, .25f, .8f);
    this->scheduleOnce(schedule_selector(RepeatOneOffSequenceChallengeScene::showGameScorePopupCallback), 2.0f);
  } 
}

void RepeatOneOffSequenceChallengeScene::onIncorrectButtonPressed()
{
  this->m_sceneState = RUNNING_END_OF_GAME_ANIMATION;

  this->m_gameScore.coinsEarned = round( (float)m_gameScore.level * m_challengePointScoreDefinition.coinsEarnedMultiplier );
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
          
  m_lastButtonPressed->playAnimation(PRESSED);

  this->schedule(schedule_selector(RepeatOneOffSequenceChallengeScene::eogGrayOutButtons), 0.021f); // framerate: 1/48
  this->schedule(schedule_selector(RepeatOneOffSequenceChallengeScene::eogGrayOutLastButton), 0.021f, -1, wrongDelay); // framerate: 1/48
  this->schedule(schedule_selector(RepeatOneOffSequenceChallengeScene::eogReleaseLastButton), 0.021f, 0, wrongDelay); // framerate: 1/48
  this->schedule(schedule_selector(RepeatOneOffSequenceChallengeScene::eogBlinkCorrectButton), 0.2f, -1, correctBlinkDelay); // framerate: 1/48    
  
}
