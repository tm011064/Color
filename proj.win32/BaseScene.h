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
  
  SceneState m_sceneState;
  GameContext* m_gameContext;

public:
  
  BaseScene(GameContext* gameContext)
    : m_debugDraw(0)
    , m_sceneState(UNLOADED)
  {
    this->m_gameContext = gameContext;

#if IS_DEBUG
  if (!m_debugDraw)
  {
    m_debugDraw = DebugDraw::create(); 
    this->addChild(m_debugDraw, 1000); 
  }
#endif
  }

  virtual void onBackKeyPressed() { }
  SceneState getSceneState() { return this->m_sceneState; } 

};

#endif  // __BASE_SCENE_H__