#include "ArcadeEasyGameScene.h"
#include "LayoutController.h"

using namespace cocos2d;

ArcadeEasyGameScene::ArcadeEasyGameScene(GameContext* gameContext, bool showSplashScreen)   
  : ArcadeGameScene(gameContext, ARCADE_EASY_GAME_SCENE, 4, showSplashScreen)
{ 
  m_challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_TWO_BUTTONS;
  m_challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_TWO_BUTTONS_MAX_TIME_BONUS;
  m_challengePointScoreDefinition.clickTimeThreshold = TWO_BUTTON_CLICK_TIME_THRESHOLD;
  m_challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_TWO_BUTTONS_LEVEL_BONUS;
  m_challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_TWO_BUTTONS_MAX_LEVEL_TIME_BONUS;
  m_challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_TWO_BUTTONS_MULTIPLIER;
}
void ArcadeEasyGameScene::onPostInitialize()
{  
  this->m_buttons = LayoutController::createTwoButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
    , callfuncO_selector( ArcadeEasyGameScene::buttonTouchEndedCallback )
    , callfuncO_selector( ArcadeEasyGameScene::buttonLoadedCallback )
    , callfuncO_selector( ArcadeEasyGameScene::buttonBlinkCallback )
    , FIRE_ON_TOUCH_BEGAN, DRUMS);

  this->m_totalVisibleButtons = this->m_buttons->count();
  
  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    LayoutController::addConsoleButton(m_pGameContext, this, (GameButton*)o);
  }
}
void ArcadeEasyGameScene::onGameOver()
{  
  if (m_gameScore.totalPoints > m_pGameContext->getHighscoreMemory2b())
    this->m_pGameContext->setHighscoreMemory2b(m_gameScore.totalPoints);
  if (m_gameScore.level > m_pGameContext->getHighscoreMemory2bTotal())
    this->m_pGameContext->setHighscoreMemory2bTotal(m_gameScore.level);
}