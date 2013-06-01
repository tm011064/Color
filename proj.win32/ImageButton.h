#ifndef __IMAGEBUTTON_H__
#define __IMAGEBUTTON_H__

#include "cocos2d.h"
#include "BaseSprite.h"
#include "GameConstants.h"
#include "Types.h"
#include "GameContext.h"

class ImageButton : public BaseSprite
{
private:
  ButtonState m_buttonState;
  bool m_isEnabled;
  void setButtonState(ButtonState buttonState);

  GameContext* m_gameContext;

public:
  ~ImageButton() { }

  static ImageButton* create(CCNode *pTarget, SEL_CallFuncO touchEndedDelegate
    , SEL_CallFuncO preLoadDelegate, GameContext* gameContext
    , std::string pList, std::string textureFileName
    , int alphaMapStillFrameIndex // set to -1 if no alpha map is needed
    , int idleFrameIndex
    , int pressingFrames[], int totalPressingFrames
    , int releasingFrames[], int totalReleasingFrames
    , int pressedFrame
    , int disabledFrame
    , int touchPriority);

  ButtonState getButtonState() { return this->m_buttonState; }
    
  virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
  virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
  virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

  virtual bool containsTouchLocation(CCTouch* touch);

  bool getIsEnabled() { return m_isEnabled; }
  void setIsEnabled(bool isEnabled);

protected:
  ImageButton(CCNode *pTarget, SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate
              , GameContext* gameContext)   
    : BaseSprite(pTarget, touchEndedDelegate, preLoadDelegate)
    , m_buttonState(UNGRABBED)
    , m_gameContext(gameContext)
    , m_isEnabled(true)
  {

  }

};

#endif  // __IMAGEBUTTON_H__