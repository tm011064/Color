#include "ArcadeNormalGameScene.h"
#include "LayoutController.h"

using namespace cocos2d;

ArcadeNormalGameScene::ArcadeNormalGameScene(GameContext* gameContext)   
  : ArcadeGameScene(gameContext, ARCADE_NORMAL_GAME_SCENE, 4)
{ 
  m_challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_THREE_BUTTONS;
  m_challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_TIME_BONUS;
  m_challengePointScoreDefinition.clickTimeThreshold = THREE_BUTTON_CLICK_TIME_THRESHOLD;
  m_challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_LEVEL_BONUS;
  m_challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_LEVEL_TIME_BONUS;
  m_challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_THREE_BUTTONS_MULTIPLIER;
}
void ArcadeNormalGameScene::onLoadLayout()
{  
  this->m_buttons = LayoutController::createThreeButtons(this->m_gameContext, this->m_debugDraw, this->m_anchor, this
    , callfuncO_selector( ArcadeNormalGameScene::buttonTouchEndedCallback )
    , callfuncO_selector( ArcadeNormalGameScene::buttonLoadedCallback )
    , callfuncO_selector( ArcadeNormalGameScene::buttonBlinkCallback ));         
}
void ArcadeNormalGameScene::onGameOver()
{  
  if ((int)m_gameScore.totalPoints > m_gameContext->getHighscoreNormal())
    m_gameContext->setHighscoreNormal((int)m_gameScore.totalPoints);
}