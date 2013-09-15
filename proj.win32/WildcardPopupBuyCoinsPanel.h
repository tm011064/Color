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

  GameContext* m_pGameContext; 
  CCSize m_size;

  void goBackCallback(CCObject* pSender); 

  SEL_CallFuncO m_fnpGoBackDelegate;
  
  CCNode *m_pTarget;
  
protected:  

  WildcardPopupBuyCoinsPanel(GameContext* gameContext
    , CCSize size
    , SEL_CallFuncO goBackDelegate
    , CCNode* callbackTarget)
    : m_pGameContext(gameContext)
    , m_fnpGoBackDelegate(goBackDelegate)
    , m_pTarget(callbackTarget)
    , m_size(size)
    , m_isLayoutInitialized(false)
  { }

public:
  static WildcardPopupBuyCoinsPanel* create(GameContext* gameContext
    , CCSize size
    , SEL_CallFuncO goBackDelegate
    , CCNode* callbackTarget);

  ~WildcardPopupBuyCoinsPanel() 
  { 
    this->m_pGameContext = NULL;
    this->m_pTarget = NULL;
  }
  
  virtual void onEnter();
};

#endif  // __WILDCARD_POPUP_BUY_COINS_PANEL_H__