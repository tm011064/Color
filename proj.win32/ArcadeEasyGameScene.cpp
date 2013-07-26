#include "ArcadeEasyGameScene.h"
#include "LayoutController.h"

using namespace cocos2d;

ArcadeEasyGameScene::ArcadeEasyGameScene(GameContext* gameContext)   
  : ArcadeGameScene(gameContext, ARCADE_EASY_GAME_SCENE, 4)
{ 
  m_challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_TWO_BUTTONS;
  m_challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_TWO_BUTTONS_MAX_TIME_BONUS;
  m_challengePointScoreDefinition.clickTimeThreshold = TWO_BUTTON_CLICK_TIME_THRESHOLD;
  m_challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_TWO_BUTTONS_LEVEL_BONUS;
  m_challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_TWO_BUTTONS_MAX_LEVEL_TIME_BONUS;
  m_challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_TWO_BUTTONS_MULTIPLIER;
}
void ArcadeEasyGameScene::onLoadLayout()
{  
  this->m_buttons = LayoutController::createTwoButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
    , callfuncO_selector( ArcadeEasyGameScene::buttonTouchEndedCallback )
    , callfuncO_selector( ArcadeEasyGameScene::buttonLoadedCallback )
    , callfuncO_selector( ArcadeEasyGameScene::buttonBlinkCallback )
    , FIRE_ON_TOUCH_BEGAN);
  
  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    this->addChild((GameButton*)o);
  }
}
void ArcadeEasyGameScene::onGameOver()
{  
  if ((int)m_gameScore.totalPoints > m_pGameContext->getHighscoreEasy())
    m_pGameContext->setHighscoreEasy((int)m_gameScore.totalPoints);
}