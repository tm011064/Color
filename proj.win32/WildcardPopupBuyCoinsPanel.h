#ifndef __WILDCARD_POPUP_BUY_COINS_PANEL_H__
#define __WILDCARD_POPUP_BUY_COINS_PANEL_H__

#include "GameEngineIncludes.h"

using namespace cocos2d;

class WildcardPopupBuyCoinsPanel : public BaseNode
{  
private:
  
  bool m_isLayoutInitialized;
  float m_padding;
  float m_borderThickness;

  GameContext* m_gameContext; 
  CCSize m_size;

  void goBackCallback(CCObject* pSender); 

  SEL_CallFuncO m_fnpGoBackDelegate;
  
  CCNode *m_pTarget;

public:
  WildcardPopupBuyCoinsPanel(GameContext* gameContext
    , CCSize size
    , SEL_CallFuncO goBackDelegate
    , CCNode* callbackTarget)
    : m_gameContext(gameContext)
    , m_fnpGoBackDelegate(goBackDelegate)
    , m_pTarget(callbackTarget)
    , m_size(size)
    , m_isLayoutInitialized(false)
  { }
  ~WildcardPopupBuyCoinsPanel() { }
  
  virtual void onEnter();
};

#endif  // __WILDCARD_POPUP_BUY_COINS_PANEL_H__