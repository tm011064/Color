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

  static cocos2d::CCScene* resetGameContextScene(SceneType sceneType, GameContext* gameContext, bool showSplashScreen);
  static cocos2d::CCScene* resetGameContextChallengeScene(int challengeIndex, GameContext* gameContext, bool showSplashScreen);
  
public:

  NavigationManager() { }
  ~NavigationManager() { }
  
  static void showMainMenu(GameContext* gameContext, SceneRenderMode sceneRenderMode, bool showSplashScreen, MenuViewType startScreen);
  static void showScene(SceneType sceneType, GameContext* gameContext, SceneRenderMode sceneRenderMode, bool showSplashScreen);
  static void showChallengeScene(GameContext* gameContext, int challengeIndex, SceneRenderMode sceneRenderMode, bool showSplashScreen);

  static std::string getPath(GameContext* gameContext, std::string fileName);

};

#endif  // __NAVIGATION_MANAGER_H__