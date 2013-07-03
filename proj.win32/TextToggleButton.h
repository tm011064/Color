#ifndef __TEXTTOGGLEBUTTON_H__
#define __TEXTTOGGLEBUTTON_H__

#include "cocos2d.h"
#include "BaseSprite.h"
#include "GameConstants.h"
#include "Types.h"
#include "GameContext.h"

using namespace cocos2d;


enum ToggleState
{
  ON = 0,
  OFF = 1,
};


class TextToggleButton : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
private:
  ButtonState m_buttonState;
  ToggleState m_toggleState;

  void setButtonState(ButtonState buttonState);

  CCLabelBMFont* m_textLabel;
  std::string m_text;

  ccColor4F m_borderColorOn;
  ccColor4F m_borderColorOff;
  
  ccColor4F m_backgroundColorOn;
  ccColor4F m_backgroundColorOff;

  ccColor3B m_textColorOn;
  ccColor3B m_textColorOff;
    
  CCSize m_size;

  CCNode* m_pTarget;
  bool m_isEnabled;
  bool m_isLayoutInitialized;

  CCPoint m_borderOrigin;
  CCPoint m_borderDestination;
  CCPoint m_backgroundOrigin;
  CCPoint m_backgroundDestination;
  ccColor4F m_currentBackgroundColor;
  ccColor4F m_currentBorderColor;
  
  GameContext* m_gameContext; 
  SEL_CallFuncO m_fnpToggleChangedDelegate;

  void refresh();

public:  
  TextToggleButton(ccColor4F borderColorOn, ccColor4F borderColorOff, ccColor4F backgroundColorOn
    , ccColor4F backgroundColorOff, ccColor3B textColorOn, ccColor3B textColorOff
    , std::string text, ToggleState toggleState, CCSize size
    , GameContext* gameContext, SEL_CallFuncO m_fnpToggleChangedDelegate, CCNode *pTarget);
  ~TextToggleButton() 
  { 
    this->m_gameContext = NULL;
    this->m_pTarget = NULL;
  }
  
  void setEnabled(bool isEnabled) { this->m_isEnabled = isEnabled; }

  ToggleState getToggleState() { return this->m_toggleState; }
  void setToggleState(ToggleState toggleState);
    
  virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
  virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
  virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
  
  virtual void onEnter();
  virtual void onExit();
  virtual void draw();

  virtual bool containsTouchLocation(CCTouch* touch);

};

#endif  // __TEXTTOGGLEBUTTON_H__