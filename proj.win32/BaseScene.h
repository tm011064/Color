#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"

class BaseScene : public cocos2d::CCScene
{
protected:

#if IS_DEBUG
  DebugDraw* m_debugDraw;
#endif

  bool m_isLayoutInitialized;
  CCSprite* m_splashScreen;
  CCSprite* m_splashLogoScreen;

  SceneState m_sceneState;
  GameContext* m_pGameContext;
  bool m_showSplashScreen;

  virtual void initialize(float dt) { /* can be overridden */ }

  void hideSplashScreen();

public:
  
  BaseScene(GameContext* gameContext, bool showSplashScreen)
    : m_debugDraw(0)
    , m_sceneState(UNLOADED)
    , m_isLayoutInitialized(false)
    , m_splashScreen(NULL)
    , m_splashLogoScreen(NULL)
    , m_showSplashScreen(showSplashScreen)
  {
    this->m_pGameContext = gameContext;

#if IS_DEBUG
  if (!m_debugDraw)
  {
    m_debugDraw = DebugDraw::create(); 
    this->addChild(m_debugDraw, 1000); 
  }
#endif
  }

  ~BaseScene()
  {
    this->m_pGameContext = NULL;
  }

  virtual void onEnter();
  
  virtual void onBackKeyPressed() { }
  SceneState getSceneState() { return this->m_sceneState; } 

};

#endif  // __BASE_SCENE_H__