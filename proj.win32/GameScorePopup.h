#ifndef __GAMESCORE_POPUP_H__
#define __GAMESCORE_POPUP_H__

#include "ModalControl.h"

using namespace cocos2d;

class GameScorePopup : public ModalControl
{  
private:

  GameContext* m_gameContext; 
    
  CCPoint m_separatorLineLeftBottom;
  CCPoint m_separatorLineRightTop;
    
  CCPoint m_dialogRectLeftTop;
  CCPoint m_dialogRectRightBottom;
    
  CCLabelBMFont* m_pointsLabel;
  CCLabelBMFont* m_pointsLabelDescription;
  CCLabelBMFont* m_levelBonusLabel;
  CCLabelBMFont* m_levelBonusLabelDescription;
  CCLabelBMFont* m_timeBonusLabel;
  CCLabelBMFont* m_timeBonusLabelDescription;

  CCLabelBMFont* m_totalPointsLabel;
  CCLabelBMFont* m_coinsEarnedLabel;
  
  void playAgainCallback(CCObject* pSender);
  void mainMenuCallback(CCObject* pSender);
  
  SEL_CallFuncO m_fnpPlayAgainCallbackDelegate;
  SEL_CallFuncO m_fnpMainMenuCallbackDelegate;
  
  CCNode *m_pTarget;
  
  float m_elaspeTimePoints;
  float m_elaspeTimeCoins;
  float m_targetTime;

  void updatePointsDisplay(float dt);
  void updateCoinsDisplay(float dt);

public:
  GameScorePopup(GameContext* gameContext
    , SEL_CallFuncO playAgainCallbackDelegate
    , SEL_CallFuncO mainMenuCallbackDelegate
    , CCNode* callbackTarget)
    : m_gameContext(gameContext)
    , m_fnpPlayAgainCallbackDelegate(playAgainCallbackDelegate)
    , m_fnpMainMenuCallbackDelegate(mainMenuCallbackDelegate)
    , m_pTarget(callbackTarget)
    , m_pointsLabel(NULL)
    , m_pointsLabelDescription(NULL)
    , m_levelBonusLabel(NULL)
    , m_levelBonusLabelDescription(NULL)
    , m_timeBonusLabel(NULL)
    , m_timeBonusLabelDescription(NULL)
    , m_totalPointsLabel(NULL)
    , m_coinsEarnedLabel(NULL)
  { }
  ~GameScorePopup() { }
  
  void refresh();

  virtual void onEnter();
  virtual void draw();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) { return ModalControl::ccTouchBegan(pTouch, pEvent); }

  virtual void show();
};
#endif  // __GAMESCORE_POPUP_H__