#ifndef __ARCADE_CLASSIC_GAME_SCENE_H__
#define __ARCADE_CLASSIC_GAME_SCENE_H__

#include "ArcadeGameScene.h"

class ArcadeClassicGameScene : public ArcadeGameScene
{
public:

  ArcadeClassicGameScene(GameContext* gameContext);
  ~ArcadeClassicGameScene(){}  
  
protected:  
  virtual void onLoadLayout();
  virtual void onGameOver();
};

#endif  // __ARCADE_CLASSIC_GAME_SCENE_H__