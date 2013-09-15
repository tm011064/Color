#ifndef __ARCADEEASYGAMEGAME_SCENE_H__
#define __ARCADEEASYGAMEGAME_SCENE_H__

#include "ArcadeGameScene.h"

class ArcadeEasyGameScene : public ArcadeGameScene
{
public:

  ArcadeEasyGameScene(GameContext* gameContext, bool showSplashScreen);
  ~ArcadeEasyGameScene()
  {
    this->m_pGameContext = NULL;
  }  
  
protected:  
  virtual void onPostInitialize(); 
  virtual void onGameOver();
};

#endif  // __ARCADEEASYGAMEGAME_SCENE_H__