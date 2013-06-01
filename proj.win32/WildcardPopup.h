#ifndef __WILDCARD_POPUP_H__
#define __WILDCARD_POPUP_H__

#include "ModalControl.h"

using namespace cocos2d;

class WildcardPopup : public ModalControl
{  
private:

  float m_padding;
  GameContext* m_gameContext; 
  bool m_isLayoutInitialized;
  CCLabelBMFont* m_coinsLabel;
    
  void replaySequenceCallback(CCObject* pSender);
  void showNextSequenceItemCallback(CCObject* pSender);
  void replayFromCurrentCallback(CCObject* pSender); 
  void closeCallback(CCObject* pSender); 

  ccColor4F m_dialogColor;

  SEL_CallFuncO m_fnpReplaySequenceCallbackDelegate;
  SEL_CallFuncO m_fnpShowNextSequenceItemCallbackDelegate;
  SEL_CallFuncO m_fnpSaveTryCallbackDelegate;
  SEL_CallFuncO m_fnpCloseCallbackDelegate;
  
  CCNode *m_pTarget;

public:
  WildcardPopup(GameContext* gameContext
    , SEL_CallFuncO replaySequenceCallbackDelegate
    , SEL_CallFuncO showNextSequenceItemCallbackDelegate
    , SEL_CallFuncO replayFromCurrentCallbackDelegate
    , SEL_CallFuncO closeCallbackDelegate
    , CCNode* callbackTarget)
    : m_gameContext(gameContext)
    , m_isLayoutInitialized(false)
    , m_fnpReplaySequenceCallbackDelegate(replaySequenceCallbackDelegate)
    , m_fnpShowNextSequenceItemCallbackDelegate(showNextSequenceItemCallbackDelegate)
    , m_fnpSaveTryCallbackDelegate(replayFromCurrentCallbackDelegate)
    , m_fnpCloseCallbackDelegate(closeCallbackDelegate)
    , m_pTarget(callbackTarget)
  { }
  ~WildcardPopup() { }
  
  void refresh();
  virtual void onEnter();
  virtual void draw();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) { return ModalControl::ccTouchBegan(pTouch, pEvent); }
};
#endif  // __WILDCARD_POPUP_H__