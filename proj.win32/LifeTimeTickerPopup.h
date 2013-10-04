#ifndef __LIFE_TIME_TICKER_POPUP_H__
#define __LIFE_TIME_TICKER_POPUP_H__

#include "ModalControl.h"

using namespace cocos2d;

class LifeTimeTickerPopup : public ModalControl
{  
private:

  GameContext* m_pGameContext; 
  CCNode *m_pTarget;

  CCPoint m_separatorLineLeftBottom;
  CCPoint m_separatorLineRightTop;
    
  CCPoint m_dialogRectLeftTop;
  CCPoint m_dialogRectRightBottom;

  CCLabelBMFont* m_totalLifeLabel;
  CCLabelBMFont* m_deltaNextLifeIncreaseLabel_M1;
  CCLabelBMFont* m_deltaNextLifeIncreaseLabel_M2;
  CCLabelBMFont* m_deltaNextLifeIncreaseLabel_Separator;
  CCLabelBMFont* m_deltaNextLifeIncreaseLabel_S1;
  CCLabelBMFont* m_deltaNextLifeIncreaseLabel_S2;
  
  TextButton* m_playButton;
  TextButton* m_getLifesButton;

  void updateLifeDisplay(float dt);

  void playCallback(CCObject* sender);
  void getLifesCallback(CCObject* sender);

  SEL_CallFuncO m_fnpPlayCallbackDelegate;

public:
  static LifeTimeTickerPopup* create(GameContext* gameContext, CCNode* callbackTarget
    , SEL_CallFuncO playCallbackDelegate);
  ~LifeTimeTickerPopup() { }
  
  virtual void onEnter();
  virtual void draw();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) { return ModalControl::ccTouchBegan(pTouch, pEvent); }

  virtual void show();
  virtual void hide();

protected:  
  LifeTimeTickerPopup(GameContext* gameContext, CCNode* callbackTarget
    , SEL_CallFuncO playCallbackDelegate)
    : m_pGameContext(gameContext)    
    , m_pTarget(callbackTarget)
    , m_totalLifeLabel(NULL)
    , m_deltaNextLifeIncreaseLabel_M1(NULL)
    , m_deltaNextLifeIncreaseLabel_M2(NULL)
    , m_deltaNextLifeIncreaseLabel_Separator(NULL)
    , m_deltaNextLifeIncreaseLabel_S1(NULL)
    , m_deltaNextLifeIncreaseLabel_S2(NULL)
    , m_playButton(NULL)
    , m_getLifesButton(NULL)
    , m_fnpPlayCallbackDelegate(playCallbackDelegate)
  { }
};
#endif  // __LIFE_TIME_TICKER_POPUP_H__