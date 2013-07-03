#ifndef _BASESPRITE_H
#define _BASESPRITE_H

#include "cocos2d.h"
#include "Types.h"
#include "GameConstants.h"
#include "DebugDraw.h"
#include "GameContext.h"
#include <queue>

using namespace cocos2d;

class BaseSprite : public cocos2d::CCSprite, public cocos2d::CCTargetedTouchDelegate
{
  std::vector<CCSpriteFrame*>* m_animationFrames;
  
  int m_totalFrames;

  //Indexing variable.
  int m_currentIndex, m_incrementValue;

  //Loopoing variable.
  int m_runningLoop;// , m_totalLoops;
    
  //Frame Rate.
  float m_frameRate;
    
  bool m_isLoaded;
  
  //Frame Rate Calculation variable.
  float m_elaspeTime;
    
  //Animation mode variable.
  bool m_needToRunReverseAnimation, m_animationMode, m_isPlistLoaded;
  bool m_isAnimationRunning;
  bool m_needToDeleteItself;
  //Local funciton.
  float calculateFrameRate(int number_frames){return 1.0f / number_frames;}
  void increaseCurrentIndex();
    
  void removeObjectItself();
        
  std::map<int, AnimationDefinition> m_animationDefinitions;  
  AnimationDefinition *m_currentAnimationDefinition;

  virtual void update(float dt);
  void loadUpdate(float delta);
  
  bool containsPoint();

  /* Alpha Map */
  bool **m_alphaMap;
  unsigned int m_alphaMapCols;
  unsigned int m_alphaMapRows;
  int m_alphaMapStillFrameIndex;
  int m_touchPriority;

public:
  //
  BaseSprite(CCNode *pTarget, SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate);
  ~BaseSprite();

  virtual void onEnter();
  virtual void onExit();
  virtual bool containsTouchLocation(CCTouch* touch);
     
  bool getIsLoaded() { return this->m_isLoaded; }

  int getTouchPriority() { return this->m_touchPriority; }
  void setTouchPriority(int priority) { this->m_touchPriority = priority; }

  //Add Frames to run Animation.
  void setAnimationFrames(std::vector<CCSpriteFrame*>* frames);
  void setAnimationFrames(std::vector<CCSpriteFrame*>* frames, int displayTextureIndex);
 
  //Sets Frame Rate for running Animation
  void setFrameRate(int framesPerSecond){m_frameRate = calculateFrameRate(framesPerSecond);}
  void setFrameRate(float frameRate){ m_frameRate = frameRate;}

  //Controller for Animation.
  void pauseAnimation(){pauseSchedulerAndActions(); }
  void resumeAnimation(){resumeSchedulerAndActions(); }
  void stopAnimation();
    
  virtual void playAnimation(int animationIndex);
  
  void registerStillFrame(int animationIndex, int plistIndex, SEL_CallFuncO fnpSelectorDelegate, bool needToDeleteItself);
  void registerAnimation(int animationIndex, int plistStartIndex, int plistEndIndex, int totalLoops
    , SEL_CallFuncO fnpSelectorDelegate, int framesPerSecond, bool needToRunReverseAnimation, bool needToDeleteItself);
  void registerAnimation(int animationIndex, int indexes[], int totalIndexes, int totalLoops
    , SEL_CallFuncO fnpSelectorDelegate, int framesPerSecond, bool needToRunReverseAnimation, bool needToDeleteItself);

  void load();

  bool getIsAnimationRunning() { return m_isAnimationRunning; } 

  Circle getVisibleBoundingCircle();
  Circle getBoundingCircle();
  
  CCRect getVisibleBoundingBox();
  CCRect getBoundingBox();
  
  CCSize getSpriteFrameSize(int index);

  /* Alpha Map */
  bool hasAlphaMap() { return m_alphaMap != 0; }
  void refreshAlphaMap(CCSize originalSize, ResolutionPolicy resolutionPolicy);
  void setAlphaMapStillFrameIndex(int frameIndex) { this->m_alphaMapStillFrameIndex = frameIndex; }

protected:

#if IS_DEBUG
  DebugDraw* m_debugDraw;
#endif
  
  /* Alpha Map */
  bool isTransparent(int x, int y);

  void setDisplayFrameAtIndex(int index);

  //Callback funciton pointer.
  SEL_CallFuncO m_fnpPreLoadDelegate;    
  SEL_CallFuncO m_fnpTouchEndedDelegate;

  CCNode *m_pTarget;
};

#endif