#include "ArcadeEasyGameScene.h"
#include "LayoutController.h"

using namespace cocos2d;

ArcadeEasyGameScene::ArcadeEasyGameScene(GameContext* gameContext)   
  : ArcadeGameScene(gameContext, ARCADE_EASY_GAME_SCENE, 4)
{ 
  m_challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_THREE_BUTTONS;
  m_challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_TIME_BONUS;
  m_challengePointScoreDefinition.clickTimeThreshold = THREE_BUTTON_CLICK_TIME_THRESHOLD;
  m_challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_LEVEL_BONUS;
  m_challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_LEVEL_TIME_BONUS;
}
void ArcadeEasyGameScene::onLoadLayout()
{  
  this->m_buttons = LayoutController::createThreeButtons(this->m_gameContext, this->m_debugDraw, this->m_anchor, this
    , callfuncO_selector( ArcadeEasyGameScene::buttonTouchEndedCallback )
    , callfuncO_selector( ArcadeEasyGameScene::buttonLoadedCallback )
    , callfuncO_selector( ArcadeEasyGameScene::buttonBlinkCallback ));         
}
void ArcadeEasyGameScene::onGameOver()
{  
  if ((int)m_gameScore.totalPoints > m_gameContext->getHighscoreEasy())
    m_gameContext->setHighscoreEasy((int)m_gameScore.totalPoints);
}