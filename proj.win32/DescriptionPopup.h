#ifndef __DESCRIPTION_POPUP_H__
#define __DESCRIPTION_POPUP_H__

#include "ModalControl.h"

using namespace cocos2d;

class DescriptionPopup : public ModalControl
{  
private:
 
  bool m_isLayoutInitialized;
    
  GameContext* m_pGameContext; 
  SEL_CallFuncO m_fnpCloseCallbackDelegate;  
  CCNode *m_pTarget;
    
  TextButton* m_playButton;
  std::string m_header;
  std::string m_text;
  CCSpriteFrame* m_icon;

  void playCallback(CCObject* pSender);

  float m_padding;

protected:
  DescriptionPopup(GameContext* gameContext
    , SEL_CallFuncO closeCallbackDelegate
    , CCNode* callbackTarget
    , std::string header, std::string text, CCSpriteFrame* icon
    , ccColor4F backgroundColor, ccColor4F dialogColor, ccColor4F dialogBorderColor)
    : m_pGameContext(gameContext)
    , m_isLayoutInitialized(false)
    , m_fnpCloseCallbackDelegate(closeCallbackDelegate)
    , m_pTarget(callbackTarget)
    , m_header(header)
    , m_text(text)
    , m_icon(icon)
    , m_playButton(NULL)
  { 
    m_backgroundColor = backgroundColor;
    m_dialogColor = dialogColor;
    m_dialogBorderColor = dialogBorderColor;
  }

public:
  static DescriptionPopup* create(GameContext* gameContext
    , SEL_CallFuncO closeCallbackDelegate
    , CCNode* callbackTarget
    , std::string header, std::string text, CCSpriteFrame* icon
    , ccColor4F backgroundColor, ccColor4F dialogColor, ccColor4F dialogBorderColor);
  ~DescriptionPopup() { }

  void setEnablePlayButton(bool isEnabled);
  virtual void onEnter();
  virtual void draw();
};
#endif  // __DESCRIPTION_POPUP_H__