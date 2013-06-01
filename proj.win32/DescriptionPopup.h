#ifndef __DESCRIPTION_POPUP_H__
#define __DESCRIPTION_POPUP_H__

#include "ModalControl.h"

using namespace cocos2d;

class DescriptionPopup : public ModalControl
{  
private:
 
  bool m_isLayoutInitialized;
    
  GameContext* m_gameContext; 
  SEL_CallFuncO m_fnpCloseCallbackDelegate;  
  CCNode *m_pTarget;
  CCLabelBMFont* m_text;

  float m_padding;

public:
  DescriptionPopup(GameContext* gameContext
    , SEL_CallFuncO closeCallbackDelegate
    , CCNode* callbackTarget)
    : m_gameContext(gameContext)
    , m_isLayoutInitialized(false)
    , m_fnpCloseCallbackDelegate(closeCallbackDelegate)
    , m_pTarget(callbackTarget)
    , m_text(NULL)
  { }
  ~DescriptionPopup() { }
  
  void setText(std::string text);

  virtual void onEnter();
  virtual void draw();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
};
#endif  // __DESCRIPTION_POPUP_H__