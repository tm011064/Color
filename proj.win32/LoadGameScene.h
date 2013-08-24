#ifndef __LOAD_GAME_SCENE_H__
#define __LOAD_GAME_SCENE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"

class LoadGameScene : public cocos2d::CCScene
{
private:

  bool m_isLayoutInitialized;
  GameContext* m_pGameContext;

  void loadGame(float dt);

public:
  
  LoadGameScene(GameContext* pGameContext)
    : m_isLayoutInitialized(false)
    , m_pGameContext(pGameContext)
  { }
  ~LoadGameScene() { }

  virtual void onEnter();

};

#endif  // __LOAD_GAME_SCENE_H__