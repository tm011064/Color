#include "ReachLevelChallengeScene.h"
#include "LayoutController.h"
#include <cstdlib>

using namespace cocos2d;

ReachLevelChallengeScene* ReachLevelChallengeScene::create(GameContext* gameContext, int challengeIndex
  , int totalButtons, ChallengePointScoreDefinition challengePointScoreDefinition, int levelToReach)
{
  ReachLevelChallengeScene* scene = new ReachLevelChallengeScene(gameContext, challengeIndex, totalButtons, REACH_LEVEL, challengePointScoreDefinition, levelToReach);
  scene->init();

  return scene;
}

void ReachLevelChallengeScene::onLoadLayout()
{  
  switch (this->m_totalButtons)
  {
  case 3:
    this->m_buttons = LayoutController::createThreeButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ReachLevelChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ReachLevelChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ReachLevelChallengeScene::buttonBlinkCallback ));      
    break;

  case 4:
        
    this->m_buttons = LayoutController::createFourButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ReachLevelChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ReachLevelChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ReachLevelChallengeScene::buttonBlinkCallback ));      
    break;

  case 5:
    this->m_buttons = LayoutController::createFiveButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( ReachLevelChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( ReachLevelChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( ReachLevelChallengeScene::buttonBlinkCallback ));      
    break;
  }       

  // TODO (Roman): text
  m_descriptionPopup->setText("Get 10 buttons in a row right\nto clear this stage\n\nDo it as quickly as possible to\ncollect stars!");
}

void ReachLevelChallengeScene::onLayoutLoaded()
{  
  this->m_loadingScreen->setVisible(false);
}

void ReachLevelChallengeScene::startNewGame()
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

void ReachLevelChallengeScene::runSequenceAnimation(bool doAddButton, int startIndex, int endIndex)
{
  this->m_sceneState = RUNNING_SEQUENCE_ANIMATION;

  this->unschedule(schedule_selector(ReachLevelChallengeScene::update));
  
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
  
  this->schedule(schedule_selector(ReachLevelChallengeScene::update), delay);
}

void ReachLevelChallengeScene::update(float delta)
{  
  GameButton* button = m_buttonSequence.at(m_buttonSequenceIndex);
  
  button->playAnimation(BLINK);
  m_buttonSequenceIndex++;

  if (m_buttonSequenceIndex >= this->m_lastEndIndex)
  {
    this->unschedule(schedule_selector(ReachLevelChallengeScene::update));
  }  
}

void ReachLevelChallengeScene::onSequenceBlinkCallback(GameButton* gameButton)
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

void ReachLevelChallengeScene::onCorrectButtonPressed()
{
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

    if (m_buttonSequenceIndex == m_levelToReach)
    {
      m_topBar->setScore((long)this->m_gameScore.totalPoints);
      m_pGameContext->setGameScore( m_gameScore );
      
      int levelReached = this->updateChallengeInfo(&this->m_challengePointScoreDefinition);

      m_gameScorePopup->refresh();
      m_gameScorePopup->show();
    }
    else
    {
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

      this->m_pGameContext->setTotalCoins(this->m_pGameContext->getTotalCoins() + 1);           
      
      m_topBar->setLevel(m_gameScore.level + 1);      
      m_topBar->setScore((long)this->m_gameScore.totalPoints);

      runSequenceAnimation(true, 0, -1);
    }      
  }
}

void ReachLevelChallengeScene::onIncorrectButtonPressed()
{
  m_topBar->setScore((long)this->m_gameScore.totalPoints);
  m_pGameContext->setGameScore( m_gameScore );
    
  m_gameScorePopup->refresh();
  m_gameScorePopup->show();
}
