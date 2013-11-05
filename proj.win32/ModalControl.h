#ifndef __MODALLAYER_SCENE_H__
#define __MODALLAYER_SCENE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"

using namespace cocos2d;

class ModalControl : public BaseNode, public cocos2d::CCTargetedTouchDelegate
{  
protected:  
  bool m_isLayoutInitialized;

  CCPoint m_dialogRectLeftBottom;
  CCPoint m_dialogRectRightTop;
  
  CCPoint m_visibleRectLeftBottom;
  CCPoint m_visibleRectRightTop;
  
  CCPoint m_separatorTopRight;
  CCPoint m_separatorBottomRight;
  
  float m_borderThickness, m_textIndentRight, m_textIndentLeft, m_padding;

  ccColor4F m_bgLight, m_bgDark;
  ccColor4F m_separatorColor;

  ccColor4F m_backgroundColor;
  ccColor4F m_dialogColor;
  ccColor4F m_dialogBorderColor;

public:
  ModalControl() 
  : m_isLayoutInitialized(false)
  { }
  ~ModalControl() 
  { 
  
  }
  
  virtual void onEnter();
  virtual void onExit();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
};
#endif  // __MODALLAYER_SCENE_H__