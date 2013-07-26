#include "ArcadeHardGameScene.h"
#include "LayoutController.h"

using namespace cocos2d;

ArcadeHardGameScene::ArcadeHardGameScene(GameContext* gameContext)   
  : ArcadeGameScene(gameContext, ARCADE_HARD_GAME_SCENE, 4)
{ 
  m_challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_FOUR_BUTTONS;
  m_challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_FOUR_BUTTONS_MAX_TIME_BONUS;
  m_challengePointScoreDefinition.clickTimeThreshold = FOUR_BUTTON_CLICK_TIME_THRESHOLD;
  m_challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_FOUR_BUTTONS_LEVEL_BONUS;
  m_challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_FOUR_BUTTONS_MAX_LEVEL_TIME_BONUS;
  m_challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_FOUR_BUTTONS_MULTIPLIER;
}
void ArcadeHardGameScene::onLoadLayout()
{  
  this->m_buttons = LayoutController::createFourButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
    , callfuncO_selector( ArcadeHardGameScene::buttonTouchEndedCallback )
    , callfuncO_selector( ArcadeHardGameScene::buttonLoadedCallback )
    , callfuncO_selector( ArcadeHardGameScene::buttonBlinkCallback )
    , FIRE_ON_TOUCH_BEGAN);   
  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    this->addChild((GameButton*)o);
  }      
}
void ArcadeHardGameScene::onGameOver()
{  
  if ((int)m_gameScore.totalPoints > m_pGameContext->getHighscoreHard())
    m_pGameContext->setHighscoreHard((int)m_gameScore.totalPoints);
}