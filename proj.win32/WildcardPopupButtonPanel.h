#ifndef __WILDCARD_POPUP_BUTTON_PANEL_H__
#define __WILDCARD_POPUP_BUTTON_PANEL_H__

#include "GameEngineIncludes.h"

using namespace cocos2d;

class WildcardPopupButtonPanel : public BaseNode
{  
private:
  
  bool m_isLayoutInitialized;
  float m_padding;
  float m_borderThickness;

  GameContext* m_pGameContext; 
  CCSize m_size;

  void replaySequenceCallback(CCObject* pSender);
  void showNextSequenceItemCallback(CCObject* pSender);
  void replayFromCurrentCallback(CCObject* pSender); 

  SEL_CallFuncO m_fnpReplaySequenceCallbackDelegate;
  SEL_CallFuncO m_fnpShowNextSequenceItemCallbackDelegate;
  SEL_CallFuncO m_fnpSaveTryCallbackDelegate;
  SEL_CallFuncO m_fnpMoreCoinsCallbackDelegate;
  
  CCNode *m_pTarget;

public:
  WildcardPopupButtonPanel(GameContext* gameContext
    , CCSize size
    , SEL_CallFuncO replaySequenceCallbackDelegate
    , SEL_CallFuncO showNextSequenceItemCallbackDelegate
    , SEL_CallFuncO replayFromCurrentCallbackDelegate
    , SEL_CallFuncO moreCoinsCallbackDelegate
    , CCNode* callbackTarget)
    : m_pGameContext(gameContext)
    , m_fnpReplaySequenceCallbackDelegate(replaySequenceCallbackDelegate)
    , m_fnpShowNextSequenceItemCallbackDelegate(showNextSequenceItemCallbackDelegate)
    , m_fnpSaveTryCallbackDelegate(replayFromCurrentCallbackDelegate)
    , m_fnpMoreCoinsCallbackDelegate(moreCoinsCallbackDelegate)
    , m_pTarget(callbackTarget)
    , m_size(size)
    , m_isLayoutInitialized(false)
  { }
  ~WildcardPopupButtonPanel() 
  { 
    this->m_pGameContext = NULL;
    this->m_pTarget = NULL;
  }
  
  virtual void onEnter();
};

#endif  // __WILDCARD_POPUP_BUTTON_PANEL_H__