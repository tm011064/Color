#ifndef __NAVIGATION_MANAGER_H__
#define __NAVIGATION_MANAGER_H__

#include "cocos2d.h"
#include "GameConstants.h"
#include "Types.h"
#include "GameContext.h"
//#include "RhythmChallengeScene.h"

class NavigationManager
{
private:

  static cocos2d::CCScene* resetGameContextScene(SceneType sceneType, GameContext* gameContext);
  static cocos2d::CCScene* resetGameContextChallengeScene(int challengeIndex, GameContext* gameContext);

public:

  NavigationManager() { }
  ~NavigationManager() { }
  
  static void showScene(SceneType sceneType, GameContext* gameContext, SceneRenderMode sceneRenderMode);
  static void showChallengeScene(GameContext* gameContext, int challengeIndex, SceneRenderMode sceneRenderMode);

  static std::string getPath(GameContext* gameContext, std::string fileName);

};

#endif  // __NAVIGATION_MANAGER_H__