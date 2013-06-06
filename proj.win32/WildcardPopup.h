#ifndef __WILDCARD_POPUP_H__
#define __WILDCARD_POPUP_H__

#include "ModalControl.h"

using namespace cocos2d;

class WildcardPopup : public ModalControl
{  
private:
  
  CCPoint m_dialogRectLeftTop;
  CCPoint m_dialogRectRightBottom;

  GameContext* m_gameContext; 

  CCLabelBMFont* m_coinsLabel;
  
  CCLabelBMFont* m_replaySequence;
  CCLabelBMFont* m_showNext;
  CCLabelBMFont* m_replayFromCurrent;

  TextButton* m_replaySequenceButton;
  TextButton* m_showNextButton;
  TextButton* m_replayFromCurrentButton;
      
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
    , m_fnpReplaySequenceCallbackDelegate(replaySequenceCallbackDelegate)
    , m_fnpShowNextSequenceItemCallbackDelegate(showNextSequenceItemCallbackDelegate)
    , m_fnpSaveTryCallbackDelegate(replayFromCurrentCallbackDelegate)
    , m_fnpCloseCallbackDelegate(closeCallbackDelegate)
    , m_pTarget(callbackTarget)
    , m_replaySequence(NULL)
    , m_showNext(NULL)
    , m_replayFromCurrent(NULL)
    , m_replaySequenceButton(NULL)
    , m_showNextButton(NULL)
    , m_replayFromCurrentButton(NULL)
  { }
  ~WildcardPopup() { }
  
  void refresh();
  virtual void onEnter();
  virtual void draw();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) { return ModalControl::ccTouchBegan(pTouch, pEvent); }
};
#endif  // __WILDCARD_POPUP_H__