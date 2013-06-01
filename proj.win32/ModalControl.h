#ifndef __MODALLAYER_SCENE_H__
#define __MODALLAYER_SCENE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"

using namespace cocos2d;

class ModalControl : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{  
protected:  
  CCPoint m_dialogRectLeftBottom;
  CCPoint m_dialogRectRightTop;

  CCPoint m_dialogRectInnerLeftBottom;
  CCPoint m_dialogRectInnerRightTop;

  CCPoint m_visibleRectLeftBottom;
  CCPoint m_visibleRectRightTop;
  
  ccColor4F m_backgroundColor;
  ccColor4F m_dialogColor;
  ccColor4F m_dialogBorderColor;

public:
  ModalControl() { }
  ~ModalControl() { }
  
  virtual void onEnter();
  virtual void onExit();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);

  virtual void show();
  virtual void hide();
};
#endif  // __MODALLAYER_SCENE_H__