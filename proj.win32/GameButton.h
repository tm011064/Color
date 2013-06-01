#ifndef __BUTTON4_H__
#define __BUTTON4_H__

#include "cocos2d.h"
#include "BaseSprite.h"
#include "GameConstants.h"
#include "Types.h"
#include "GameContext.h"

class GameButton : public BaseSprite
{
private:
  ButtonState m_buttonState;

  void setButtonState(ButtonState buttonState);

  GameContext* m_gameContext;
  std::string m_soundPath;

public:
  GameButton(CCNode *pTarget, SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, GameContext* gameContext
    , std::string soundPath)   
    : BaseSprite(pTarget, touchEndedDelegate, preLoadDelegate)
    , m_buttonState(UNGRABBED)
    , m_gameContext(gameContext)
    , m_soundPath(soundPath)
  {

  }
  ~GameButton()
  {

  }
  
  static GameButton* createQuarterButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate, std::string soundPath, GameContext* gameContext);
  static GameButton* createThirdButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate, std::string soundPath, GameContext* gameContext);
  static GameButton* createFifthButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate, std::string soundPath, GameContext* gameContext);
    
  virtual void playAnimation(int animationIndex);

  virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
  virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
  virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

  virtual bool containsTouchLocation(CCTouch* touch);
};

#endif  // __BUTTON4_H__