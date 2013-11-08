#include "ArcadeNormalGameScene.h"
#include "LayoutController.h"

using namespace cocos2d;

ArcadeNormalGameScene::ArcadeNormalGameScene(GameContext* gameContext, bool showSplashScreen)   
  : ArcadeGameScene(gameContext, ARCADE_NORMAL_GAME_SCENE, 4, showSplashScreen)
{ 
  m_challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_THREE_BUTTONS;
  m_challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_TIME_BONUS;
  m_challengePointScoreDefinition.clickTimeThreshold = THREE_BUTTON_CLICK_TIME_THRESHOLD;
  m_challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_LEVEL_BONUS;
  m_challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_LEVEL_TIME_BONUS;
  m_challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_THREE_BUTTONS_MULTIPLIER;
}
void ArcadeNormalGameScene::onPostInitialize()
{  
  this->m_buttons = LayoutController::createThreeButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
    , callfuncO_selector( ArcadeNormalGameScene::buttonTouchEndedCallback )
    , callfuncO_selector( ArcadeNormalGameScene::buttonLoadedCallback )
    , callfuncO_selector( ArcadeNormalGameScene::buttonBlinkCallback )
    , FIRE_ON_TOUCH_BEGAN, DRUMS);   
  
  this->m_totalVisibleButtons = this->m_buttons->count();

  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    LayoutController::addConsoleButton(m_pGameContext, this, (GameButton*)o);
  }      
}
void ArcadeNormalGameScene::onGameOver()
{  
  if (m_gameScore.totalPoints > m_pGameContext->getHighscoreMemory3b())
    this->m_pGameContext->setHighscoreMemory3b(m_gameScore.totalPoints);
  if (m_gameScore.level > m_pGameContext->getHighscoreMemory3bTotal())
    this->m_pGameContext->setHighscoreMemory3bTotal(m_gameScore.level);
}