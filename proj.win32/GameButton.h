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
  
  bool m_isEnabled;
  
  GameContext* m_pGameContext;
  std::string m_soundPath;
  ccColor3B m_originalColor;

public:
  GameButton(CCNode *pTarget, SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, GameContext* gameContext
    , std::string soundPath)   
    : BaseSprite(pTarget, touchEndedDelegate, preLoadDelegate)
    , m_pGameContext(gameContext)
    , m_soundPath(soundPath)
    , m_isEnabled(true)
  {

  }
  ~GameButton()
  {

  }
  
  int getIsEnabled() { return this->m_isEnabled; }
  void setIsEnabled(bool isEnabled) { this->m_isEnabled = isEnabled; }

  static GameButton* createQuarterButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate, std::string soundPath, GameContext* gameContext);
  static GameButton* createThirdButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate, std::string soundPath, GameContext* gameContext);
  static GameButton* createFifthButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate, std::string soundPath, GameContext* gameContext);
    
  void playSound();

  ccColor3B getOriginalColor() { return m_originalColor; }
  void setOriginalColor(ccColor3B color) { this->m_originalColor = color; }

  virtual void playAnimation(int animationIndex);
  virtual void playAnimation(int animationIndex, bool suppressSound);

  virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);

  virtual bool containsTouchLocation(CCTouch* touch);
};

#endif  // __BUTTON4_H__