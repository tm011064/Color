#ifndef __ARCADEHARDGAMEGAME_SCENE_H__
#define __ARCADEHARDGAMEGAME_SCENE_H__

#include "ArcadeGameScene.h"

class ArcadeHardGameScene : public ArcadeGameScene
{
public:

  ArcadeHardGameScene(GameContext* gameContext);
  ~ArcadeHardGameScene(){}
  
protected:  
  virtual void onLoadLayout();
  virtual void onGameOver();
};

#endif  // __ARCADEHARDGAMEGAME_SCENE_H__