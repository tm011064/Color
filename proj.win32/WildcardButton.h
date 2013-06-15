#ifndef __WILDCARDBUTTON_H__
#define __WILDCARDBUTTON_H__

#include "cocos2d.h"
#include "BaseSprite.h"
#include "GameConstants.h"
#include "Types.h"
#include "GameContext.h"

using namespace cocos2d;

class WildcardButton : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
private:
  ButtonState m_buttonState;

  void setButtonState(ButtonState buttonState);

  CCLabelBMFont* m_textLabel;
  std::string m_text;
  CCLabelBMFont* m_totalCoinsLabel;
  std::string m_totalCoinsText;

  ccColor4F m_borderColorOn;
  ccColor4F m_borderColorOff;
  
  ccColor4F m_backgroundColorOn;
  ccColor4F m_backgroundColorOff;
  
  ccColor4F m_coinBackgroundColorOn;
  ccColor4F m_coinBackgroundColorOff;

  ccColor3B m_textColorOn;
  ccColor3B m_textColorOff;
    
  CCSize m_size;

  CCNode* m_pTarget;
  bool m_isEnabled;
  bool m_isInitialized;
    
  float m_borderWidth;
  CCPoint m_borderOrigin;
  CCPoint m_borderDestination;
  
  CCPoint m_backgroundOrigin;
  CCPoint m_backgroundDestination;

  CCPoint m_coinBorderOrigin;
  CCPoint m_coinBorderDestination;
  
  CCPoint m_coinBackgroundOrigin;
  
  ccColor4F m_currentCoinBackgroundColor;
  ccColor4F m_currentBackgroundColor;
  ccColor4F m_currentBorderColor;
  
  GameContext* m_gameContext; 
  SEL_CallFuncO m_fnpChangedDelegate;
  
  int m_touchPriority;

  void refresh();

public:  
  WildcardButton(ccColor4F borderColorOn, ccColor4F borderColorOff
    , ccColor4F backgroundColorOn, ccColor4F backgroundColorOff
    , ccColor4F coinBackgroundColorOn, ccColor4F coinBackgroundColorOff
    , ccColor3B textColorOn, ccColor3B textColorOff
    , std::string text, std::string totalCoinsText, CCSize size, float borderWidth
    , GameContext* gameContext, SEL_CallFuncO m_fnpChangedDelegate, CCNode *pTarget);
  ~WildcardButton() { }
  
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
};

#endif  // __WILDCARDBUTTON_H__