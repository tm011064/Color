#ifndef __ARCADE_NORMAL_GAME_SCENE_H__
#define __ARCADE_NORMAL_GAME_SCENE_H__

#include "ArcadeGameScene.h"

class ArcadeNormalGameScene : public ArcadeGameScene
{
public:

  ArcadeNormalGameScene(GameContext* gameContext);
  ~ArcadeNormalGameScene()
  {
    this->m_pGameContext = NULL;
  }  
  
protected:  
  virtual void onLoadLayout();
  virtual void onGameOver();
};

#endif  // __ARCADE_NORMAL_GAME_SCENE_H__