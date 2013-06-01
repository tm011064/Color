#include "ArcadeClassicGameScene.h"
#include "LayoutController.h"

using namespace cocos2d;

ArcadeClassicGameScene::ArcadeClassicGameScene(GameContext* gameContext)   
  : ArcadeGameScene(gameContext, ARCADE_CLASSIC_GAME_SCENE, 4)
{ 
  m_challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_FOUR_BUTTONS;
  m_challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_FOUR_BUTTONS_MAX_TIME_BONUS;
  m_challengePointScoreDefinition.clickTimeThreshold = FOUR_BUTTON_CLICK_TIME_THRESHOLD;
  m_challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_FOUR_BUTTONS_LEVEL_BONUS;
  m_challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_FOUR_BUTTONS_MAX_LEVEL_TIME_BONUS;
}
void ArcadeClassicGameScene::onLoadLayout()
{  
  this->m_buttons = LayoutController::createFourButtons(this->m_gameContext, this->m_debugDraw, this->m_anchor, this
    , callfuncO_selector( ArcadeClassicGameScene::buttonTouchEndedCallback )
    , callfuncO_selector( ArcadeClassicGameScene::buttonLoadedCallback )
    , callfuncO_selector( ArcadeClassicGameScene::buttonBlinkCallback ));         
}
void ArcadeClassicGameScene::onGameOver()
{  
  if ((int)m_gameScore.totalPoints > m_gameContext->getHighscoreNormal())
    m_gameContext->setHighscoreNormal((int)m_gameScore.totalPoints);
}