#ifndef __BUTTON4_H__
#define __BUTTON4_H__

#include "cocos2d.h"
#include "BaseSprite.h"
#include "GameConstants.h"
#include "Types.h"
#include "GameContext.h"
#include "SimpleAudioEngine.h"

enum GameButtonTouchMode
{
  FIRE_ON_TOUCH_BEGAN = 0,
  FIRE_ON_TOUCH_ENDED = 1
};
enum GameButtonSoundMode
{
  DRUMS = 0,
  OSCIL = 1
};

class GameButton : public BaseSprite
{
private:
  
  bool m_isEnabled;
  GameButtonTouchMode m_gameButtonTouchMode;
  
  GameContext* m_pGameContext;
  std::string m_soundPath;
  ccColor3B m_originalColor;
  
  struct cc_timeval m_touchStartedTime;
  struct cc_timeval m_touchEndedTime;
  float m_lastTouchDuration;
  unsigned int m_lastSoundId;

public:
  ~GameButton() {}
    
  cc_timeval getLastTouchStartedTime() { return this->m_touchStartedTime; }
  cc_timeval getLastTouchEndedTime() { return this->m_touchEndedTime; }
  float getLastTouchDuration() { return this->m_lastTouchDuration; }
  
  int getIsEnabled() { return this->m_isEnabled; }
  void setIsEnabled(bool isEnabled) { this->m_isEnabled = isEnabled; }

  static GameButton* createQuarterButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , std::string soundPath, GameButtonTouchMode gameButtonTouchMode
    , GameContext* gameContext);
    
  unsigned int playSound(){ return playSound(false); }  
  unsigned int playSound(bool doLoop);
  void stopSound()
  {
    if (m_lastSoundId > 0)
      CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(m_lastSoundId);
  }
  void fadeOutSound(float fadeTime);
  void reduceVolumeCallback(float dt);

  ccColor3B getOriginalColor() { return m_originalColor; }
  void setOriginalColor(ccColor3B color) { this->m_originalColor = color; }

  virtual void playAnimation(int animationIndex);
  virtual void playAnimation(int animationIndex, bool suppressSound);

  virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
  virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
  virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

  virtual bool containsTouchLocation(CCTouch* touch);

protected:  
  GameButton(CCNode *pTarget, SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, GameContext* gameContext
    , std::string soundPath, GameButtonTouchMode gameButtonTouchMode)   
    : BaseSprite(pTarget, touchEndedDelegate, preLoadDelegate)
    , m_pGameContext(gameContext)
    , m_soundPath(soundPath)
    , m_isEnabled(true)
    , m_gameButtonTouchMode(gameButtonTouchMode)
    , m_lastTouchDuration(-1)
    , m_lastSoundId(0)
  { }
};

#endif  // __BUTTON4_H__