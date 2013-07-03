#ifndef __ARCADEEASYGAMEGAME_SCENE_H__
#define __ARCADEEASYGAMEGAME_SCENE_H__

#include "ArcadeGameScene.h"

class ArcadeEasyGameScene : public ArcadeGameScene
{
public:

  ArcadeEasyGameScene(GameContext* gameContext) ;
  ~ArcadeEasyGameScene()
  {
    this->m_gameContext = NULL;
  }  
  
protected:  
  virtual void onLoadLayout(); 
  virtual void onGameOver();
};

#endif  // __ARCADEEASYGAMEGAME_SCENE_H__