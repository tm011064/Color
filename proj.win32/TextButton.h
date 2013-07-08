#ifndef __TEXTBUTTON_H__
#define __TEXTBUTTON_H__

#include "cocos2d.h"
#include "BaseSprite.h"
#include "GameConstants.h"
#include "Types.h"
#include "GameContext.h"

using namespace cocos2d;

class TextButton : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
private:
  ButtonState m_buttonState;

  void setButtonState(ButtonState buttonState);

  CCLabelBMFont* m_textLabel;
  std::string m_text;

  ccColor3B m_borderColorOn;
  ccColor3B m_borderColorOff;
  
  ccColor4F m_backgroundColorOn;
  ccColor4F m_backgroundColorOff;

  ccColor3B m_textColorOn;
  ccColor3B m_textColorOff;
    
  CCSize m_size;

  CCNode* m_pTarget;
  bool m_isEnabled;
  bool m_isLayoutInitialized;
    
  float m_borderWidth;
  CCPoint m_borderOrigin;
  CCPoint m_borderDestination;
  CCPoint m_backgroundOrigin;
  CCPoint m_backgroundDestination;
  ccColor4F m_currentBackgroundColor;
  ccColor3B m_currentBorderColor;
  
  GameContext* m_pGameContext; 
  SEL_CallFuncO m_fnpChangedDelegate;
  
  int m_touchPriority;

  void refresh();

public:  
  static TextButton* create(ccColor3B borderColorOn, ccColor3B borderColorOff, ccColor4F backgroundColorOn
    , ccColor4F backgroundColorOff, ccColor3B textColorOn, ccColor3B textColorOff
    , std::string text, CCSize size, float borderWidth
    , GameContext* gameContext, SEL_CallFuncO m_fnpChangedDelegate, CCNode *pTarget);
  ~TextButton() 
  { 
    this->m_pGameContext = NULL;
    this->m_pTarget = NULL;
  }
  
  void setEnabled(bool isEnabled) { this->m_isEnabled = isEnabled; }
  CCSize getSize() { return this->m_size; }    

  virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
  virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
  virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
  
  virtual void onEnter();
  virtual void onExit();
  virtual void draw();

  virtual bool containsTouchLocation(CCTouch* touch);
  
  int getTouchPriority() { return this->m_touchPriority; }
  void setTouchPriority(int priority) { this->m_touchPriority = priority; }

protected:  
 TextButton(ccColor3B borderColorOn, ccColor3B borderColorOff, ccColor4F backgroundColorOn
    , ccColor4F backgroundColorOff, ccColor3B textColorOn, ccColor3B textColorOff
    , std::string text, CCSize size, float borderWidth
    , GameContext* gameContext, SEL_CallFuncO fnpChangedDelegate, CCNode *pTarget)
  : m_buttonState(UNGRABBED)
  , m_pGameContext(gameContext)
  , m_fnpChangedDelegate(fnpChangedDelegate)
  , m_isEnabled(true)
  , m_pTarget(pTarget)
  , m_isLayoutInitialized(false)
  , m_borderColorOn(borderColorOn)
  , m_borderColorOff(borderColorOff)
  , m_backgroundColorOn(backgroundColorOn)
  , m_backgroundColorOff(backgroundColorOff)
  , m_textColorOn(textColorOn)
  , m_textColorOff(textColorOff)
  , m_text(text)
  , m_size(size)
  , m_borderWidth(borderWidth)
 {

 }

};

#endif  // __TEXTBUTTON_H__