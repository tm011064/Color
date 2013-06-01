#ifndef __MENUBUTTON_H__
#define __MENUBUTTON_H__

#include "cocos2d.h"
#include "BaseSprite.h"
#include "GameConstants.h"
#include "Types.h"
#include "GameContext.h"

using namespace cocos2d;

class MenuButton : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
private:
  ButtonState m_buttonState;

  void setButtonState(ButtonState buttonState);

  CCSprite* m_bgNormalLeft;
  CCSprite* m_bgNormalMiddle;
  CCSprite* m_bgNormalRight;
  CCSprite* m_bgSelectedLeft;
  CCSprite* m_bgSelectedMiddle;
  CCSprite* m_bgSelectedRight;
  CCSprite* m_bgDisabledLeft;
  CCSprite* m_bgDisabledMiddle;
  CCSprite* m_bgDisabledRight;

  CCSprite* m_bgNormal;
  CCSprite* m_bgSelected;
  CCSprite* m_bgDisabled;

  CCNode* m_pTarget;
  const char* m_text;
  bool m_isEnabled;
  bool m_isInitialized;

  GameContext* m_gameContext; 
  SEL_CallFuncO m_fnpTouchEndedDelegate;

  void refresh();

public:  
  MenuButton(CCSpriteFrame* bgNormal, CCSpriteFrame* bgSelected, CCSpriteFrame* bgDisabled
    , const char* text
    , GameContext* gameContext, SEL_CallFuncO fnpTouchEndedDelegate, CCNode *pTarget);
  MenuButton(CCSpriteFrame* bgNormalLeft
    , CCSpriteFrame* bgNormalMiddle
    , CCSpriteFrame* bgNormalRight
    , CCSpriteFrame* bgSelectedLeft
    , CCSpriteFrame* bgSelectedMiddle
    , CCSpriteFrame* bgSelectedRight
    , CCSpriteFrame* bgDisabledLeft
    , CCSpriteFrame* bgDisabledMiddle
    , CCSpriteFrame* bgDisabledRight
    , float normalMiddleScaleX
    , float selectedMiddleScaleX
    , float disabledMiddleScaleX
    , const char* text
    , GameContext* gameContext, SEL_CallFuncO fnpTouchEndedDelegate, CCNode *pTarget);
  ~MenuButton()
  {

  }
  
  void setEnabled(bool isEnabled) { this->m_isEnabled = isEnabled; }
    
  virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
  virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
  virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
  
  virtual void onEnter();
  virtual void onExit();

  virtual bool containsTouchLocation(CCTouch* touch);

};

#endif  // __MENUBUTTON_H__