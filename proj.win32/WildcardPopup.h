#ifndef __WILDCARD_POPUP_H__
#define __WILDCARD_POPUP_H__

#include "ModalControl.h"
#include "WildcardPopupButtonPanel.h"
#include "WildcardPopupBuyCoinsPanel.h"

using namespace cocos2d;

enum WildcardPopupPanel
{
  WILDCARD_BUTTONS,
  WILDCARD_MORE_COINS,
};

class WildcardPopup : public ModalControl
{  
private:
  
  CCPoint m_dialogRectLeftTop;
  CCPoint m_dialogRectRightBottom;

  GameContext* m_pGameContext; 

  CCLabelBMFont* m_coinsLabel;
  CCSprite* m_availableCoinsCoin;
    
  TextButton* m_moreCoinsTextButton;

  WildcardPopupButtonPanel* m_wildcardPopupButtonPanel;
  WildcardPopupBuyCoinsPanel* m_wildcardPopupBuyCoinsPanel;

  void replaySequenceCallback(CCObject* pSender);
  void showNextSequenceItemCallback(CCObject* pSender);
  void replayFromCurrentCallback(CCObject* pSender); 
  void closeCallback(CCObject* pSender); 

  void moreCoinsCallback(CCObject* pSender); 
  void wildcardPanelCallback(CCObject* pSender);

  ccColor4F m_dialogColor;

  SEL_CallFuncO m_fnpReplaySequenceCallbackDelegate;
  SEL_CallFuncO m_fnpShowNextSequenceItemCallbackDelegate;
  SEL_CallFuncO m_fnpSaveTryCallbackDelegate;
  SEL_CallFuncO m_fnpCloseCallbackDelegate;
  
  CCNode *m_pTarget;

  WildcardPopupPanel m_activeWildcardPopupPanel;
  void activatePanel(WildcardPopupPanel wildcardPopupPanel);

public:
  WildcardPopup(GameContext* gameContext
    , SEL_CallFuncO replaySequenceCallbackDelegate
    , SEL_CallFuncO showNextSequenceItemCallbackDelegate
    , SEL_CallFuncO replayFromCurrentCallbackDelegate
    , SEL_CallFuncO closeCallbackDelegate
    , CCNode* callbackTarget)
    : m_pGameContext(gameContext)
    , m_fnpReplaySequenceCallbackDelegate(replaySequenceCallbackDelegate)
    , m_fnpShowNextSequenceItemCallbackDelegate(showNextSequenceItemCallbackDelegate)
    , m_fnpSaveTryCallbackDelegate(replayFromCurrentCallbackDelegate)
    , m_fnpCloseCallbackDelegate(closeCallbackDelegate)
    , m_pTarget(callbackTarget)
    , m_coinsLabel(NULL)
    , m_availableCoinsCoin(NULL)
    , m_wildcardPopupButtonPanel(NULL)
    , m_wildcardPopupBuyCoinsPanel(NULL)
    , m_moreCoinsTextButton(NULL)
    , m_activeWildcardPopupPanel(WILDCARD_BUTTONS)
  { }
  ~WildcardPopup() 
  { 
    this->m_pGameContext = NULL;
    this->m_pTarget = NULL;
  }
  
  void refresh();
  virtual void onEnter();
  virtual void draw();
  virtual void show();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) { return ModalControl::ccTouchBegan(pTouch, pEvent); }
};
#endif  // __WILDCARD_POPUP_H__