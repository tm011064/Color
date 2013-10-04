#include "NavigationManager.h"
#include "GameConstants.h"
#include "BaseLayer.h"
#include "MenuScene.h"
#include "ArcadeNormalGameScene.h"
#include "ArcadeEasyGameScene.h"
#include "ArcadeHardGameScene.h"
#include "ReachLevelChallengeScene.h"
#include "RepeatOneOffSequenceChallengeScene.h"
#include "ExactLengthChallengeScene.h"
#include "OptionsScene.h"
#include "HighscoreScene.h"
#include "RhythmChallengeScene.h"
#include "LoadGameScene.h"

using namespace cocos2d;

std::string NavigationManager::getPath(GameContext* gameContext, std::string fileName)
{
  std::string s;
  s.append(gameContext->getResourceDefinition().directory);
  s.append("/");
  s.append(fileName);
  return s;
}

CCScene* NavigationManager::resetGameContextScene(SceneType sceneType, GameContext* gameContext, bool showSplashScreen)
{  
  BaseLayer* pLayer;
  ArcadeNormalGameScene* normalGameScene;
  ArcadeEasyGameScene* arcadeEasyGameScene;
  ArcadeHardGameScene* arcadeHardGameScene;
  OptionsScene* optionsScene;
  HighscoreScene* highscoreScene;
  LoadGameScene* loadGameScene;
    
  switch (sceneType)
  {
  case LOAD_GAME_SCENE: 
    
    loadGameScene = new LoadGameScene(gameContext);
        
    pLayer = new BaseLayer(loadGameScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    loadGameScene->addChild(pLayer);
    
    return loadGameScene;

  case ARCADE_NORMAL_GAME_SCENE: 
    
    normalGameScene = new ArcadeNormalGameScene(gameContext, showSplashScreen);
    normalGameScene->init();
    
    pLayer = new BaseLayer(normalGameScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    normalGameScene->addChild(pLayer); 
    return normalGameScene;

  case ARCADE_EASY_GAME_SCENE: 

    arcadeEasyGameScene = new ArcadeEasyGameScene(gameContext, showSplashScreen);
    arcadeEasyGameScene->init();
    
    pLayer = new BaseLayer(arcadeEasyGameScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    arcadeEasyGameScene->addChild(pLayer); 
    
    return arcadeEasyGameScene;
    
  case ARCADE_HARD_GAME_SCENE: 

    arcadeHardGameScene = new ArcadeHardGameScene(gameContext, showSplashScreen);
    arcadeHardGameScene->init();
    
    pLayer = new BaseLayer(arcadeHardGameScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    arcadeHardGameScene->addChild(pLayer); 
    return arcadeHardGameScene;
    
  case OPTIONS_SCENE: 
    
    optionsScene = new OptionsScene(gameContext, showSplashScreen);
        
    pLayer = new BaseLayer(optionsScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    optionsScene->addChild(pLayer);
    
    return optionsScene;

  case HIGHSCORE_SCENE: 
    
    highscoreScene = new HighscoreScene(gameContext, showSplashScreen);
        
    pLayer = new BaseLayer(highscoreScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    highscoreScene->addChild(pLayer);
    
    return highscoreScene;
  }

  return NULL;
}

CCScene* NavigationManager::resetGameContextChallengeScene(int challengeIndex, GameContext* gameContext, bool showSplashScreen)
{    
  BaseLayer* pLayer;
  ReachLevelChallengeScene* reachLevelChallengeScene;
  RepeatOneOffSequenceChallengeScene* repeatOneOffSequenceChallengeScene;
  ExactLengthChallengeScene* exactLengthChallengeScene;
  RhythmChallengeScene* rhythmChallengeScene;
  
  // TODO (Roman): whenever we load a new scene, the sprite frame cache must be reinitialized
  // this could be written in a better way, so the cache is at the scene level, not game context level maybe???
  gameContext->getSpriteFrameCache()->init();  
  
  float levelToReach, totalCorrectButtons, totalButtons;
  ChallengePointScoreDefinition challengePointScoreDefinition;
  RhythmBlinkSequenceDefinition rhythmBlinkSequenceDefinition;

  switch (challengeIndex)
  {
  case 0:

    levelToReach = 1;
    totalButtons = 2;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );

    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);

    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .7f
      + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - levelToReach ) * .7f; // minus level to reach cause the first click gains no bonus

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .9f
      + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - levelToReach ) * .9f;

    reachLevelChallengeScene = ReachLevelChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons, challengePointScoreDefinition
      , (int)levelToReach);
    
    pLayer = new BaseLayer(reachLevelChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    reachLevelChallengeScene->addChild(pLayer); 

    return reachLevelChallengeScene;

  case 1:
    
    levelToReach = 9;
    totalButtons = 3;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );
    
    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);
        
    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .7f
      + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - levelToReach ) * .7f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .9f
      + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - levelToReach ) * .9f;

    reachLevelChallengeScene = ReachLevelChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons, challengePointScoreDefinition
      , (int)levelToReach);
    
    pLayer = new BaseLayer(reachLevelChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    reachLevelChallengeScene->addChild(pLayer); 

    return reachLevelChallengeScene;

  case 2:

    levelToReach = 2;
    totalButtons = 3;
    
    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);
    
    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.correctButtonScore * levelToReach
      + challengePointScoreDefinition.maxTimeBonus * (levelToReach - 1) * .72f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.correctButtonScore * levelToReach
      + challengePointScoreDefinition.maxTimeBonus * (levelToReach - 1) * .85f;

    repeatOneOffSequenceChallengeScene = RepeatOneOffSequenceChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons, challengePointScoreDefinition
      , (int)levelToReach);
        
    pLayer = new BaseLayer(repeatOneOffSequenceChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    repeatOneOffSequenceChallengeScene->addChild(pLayer); 

    return repeatOneOffSequenceChallengeScene;
  case 3:

    levelToReach = 12;
    totalButtons = 4;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );
    
    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);
    
    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.correctButtonScore * levelToReach
      + challengePointScoreDefinition.maxTimeBonus * (levelToReach - 1) * .72f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.correctButtonScore * levelToReach
      + challengePointScoreDefinition.maxTimeBonus * (levelToReach - 1) * .85f;

    repeatOneOffSequenceChallengeScene = RepeatOneOffSequenceChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons, challengePointScoreDefinition
      , (int)levelToReach);
    
    pLayer = new BaseLayer(repeatOneOffSequenceChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    repeatOneOffSequenceChallengeScene->addChild(pLayer); 

    return repeatOneOffSequenceChallengeScene;
    
  case 4:
    
    totalButtons = 1;
    
    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);
    
    challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
    challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
    challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;

    exactLengthChallengeScene = ExactLengthChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons
      , 1.2f, 1.2f
      , 1.0f, 1.0f
      , challengePointScoreDefinition);
    exactLengthChallengeScene->init();
    
    pLayer = new BaseLayer(exactLengthChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    exactLengthChallengeScene->addChild(pLayer); 

    return exactLengthChallengeScene;

  case 5:
    
    totalButtons = 3;
    
    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);
    
    challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
    challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
    challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;

    exactLengthChallengeScene = ExactLengthChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons
      , 1.2f, 2.4f
      , 1.0f, 1.0f
      , challengePointScoreDefinition);
    exactLengthChallengeScene->init();
    
    pLayer = new BaseLayer(exactLengthChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    exactLengthChallengeScene->addChild(pLayer); 

    return exactLengthChallengeScene;

  case 6:
        
    totalButtons = 4;    
    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);
    
    challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
    challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
    challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;

    exactLengthChallengeScene = ExactLengthChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons
      , 1.0f, 2.0f
      , .6f, 1.0f
      , challengePointScoreDefinition);
    exactLengthChallengeScene->init();
    
    pLayer = new BaseLayer(exactLengthChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    exactLengthChallengeScene->addChild(pLayer); 

    return exactLengthChallengeScene;
        
  case 7:

    rhythmBlinkSequenceDefinition = RhythmChallengeScene::loadRhythmBlinkSequenceDefinition(CCFileUtils::sharedFileUtils()->fullPathForFilename("rhythmChallenge_1.txt"));

    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(rhythmBlinkSequenceDefinition.totalButtons);
    
    challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
    challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
    challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;

    rhythmChallengeScene = RhythmChallengeScene::create(gameContext, showSplashScreen, challengeIndex, rhythmBlinkSequenceDefinition, challengePointScoreDefinition);
    rhythmChallengeScene->init();
    
    pLayer = new BaseLayer(rhythmChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    rhythmChallengeScene->addChild(pLayer); 

    return rhythmChallengeScene;
    
  case 8:

    rhythmBlinkSequenceDefinition = RhythmChallengeScene::loadRhythmBlinkSequenceDefinition(CCFileUtils::sharedFileUtils()->fullPathForFilename("rhythmChallenge_2.txt"));

    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(rhythmBlinkSequenceDefinition.totalButtons);
    
    challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
    challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
    challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;
        
    rhythmChallengeScene = RhythmChallengeScene::create(gameContext, showSplashScreen, challengeIndex, rhythmBlinkSequenceDefinition, challengePointScoreDefinition);
    rhythmChallengeScene->init();
    
    pLayer = new BaseLayer(rhythmChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    rhythmChallengeScene->addChild(pLayer); 

    return rhythmChallengeScene;

  case 9:
    
    levelToReach = 25;
    totalButtons = 2;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );
    
    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);
        
    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .7f
      + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - levelToReach ) * .7f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .9f
      + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - levelToReach ) * .9f;

    reachLevelChallengeScene = ReachLevelChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons, challengePointScoreDefinition
      , (int)levelToReach);
    
    pLayer = new BaseLayer(reachLevelChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    reachLevelChallengeScene->addChild(pLayer); 

    return reachLevelChallengeScene;

  case 10:
    
    levelToReach = 20;
    totalButtons = 3;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );
    
    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);
        
    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .7f
      + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - levelToReach ) * .7f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .9f
      + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - levelToReach ) * .9f;

    reachLevelChallengeScene = ReachLevelChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons, challengePointScoreDefinition
      , (int)levelToReach);
    
    pLayer = new BaseLayer(reachLevelChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    reachLevelChallengeScene->addChild(pLayer); 

    return reachLevelChallengeScene;

  case 11:
    
    levelToReach = 20;
    totalButtons = 4;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );
    
    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);
        
    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .7f
      + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - levelToReach ) * .7f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .9f
      + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - levelToReach ) * .9f;

    reachLevelChallengeScene = ReachLevelChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons, challengePointScoreDefinition
      , (int)levelToReach);
    
    pLayer = new BaseLayer(reachLevelChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    reachLevelChallengeScene->addChild(pLayer); 

    return reachLevelChallengeScene;

  case 12:

    levelToReach = 15;
    totalButtons = 2;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );
    
    challengePointScoreDefinition = gameContext->getChallengePointScoreDefinition(totalButtons);
    
    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.correctButtonScore * levelToReach
      + challengePointScoreDefinition.maxTimeBonus * (levelToReach - 1) * .72f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.correctButtonScore * levelToReach
      + challengePointScoreDefinition.maxTimeBonus * (levelToReach - 1) * .85f;

    repeatOneOffSequenceChallengeScene = RepeatOneOffSequenceChallengeScene::create(gameContext, showSplashScreen, challengeIndex, totalButtons, challengePointScoreDefinition
      , (int)levelToReach);
    
    pLayer = new BaseLayer(repeatOneOffSequenceChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    repeatOneOffSequenceChallengeScene->addChild(pLayer); 

    return repeatOneOffSequenceChallengeScene;
  }

  return NULL;
}

void NavigationManager::showChallengeScene(GameContext* gameContext, int challengeIndex, SceneRenderMode sceneRenderMode, bool showSplashScreen)
{  
  CCScene* scene;
  CCDirector::sharedDirector()->purgeCachedData();

  switch(sceneRenderMode)
  {
  case NEW:
    scene = resetGameContextChallengeScene(challengeIndex, gameContext, showSplashScreen);
    CCDirector::sharedDirector()->replaceScene(scene);
    scene->release();
    break;   
  }
}

void NavigationManager::showMainMenu(GameContext* gameContext, SceneRenderMode sceneRenderMode, bool showSplashScreen
  , MenuViewType startScreen)
{
  MenuScene* menuScene = new MenuScene(gameContext, showSplashScreen, startScreen);
        
  BaseLayer* pLayer = new BaseLayer(menuScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
  pLayer->init(); 
  pLayer->autorelease();

  menuScene->addChild(pLayer);
    
  CCDirector::sharedDirector()->purgeCachedData();  
  switch(sceneRenderMode)
  {
  case FIRST_RUN: CCDirector::sharedDirector()->runWithScene(menuScene); break;
  case NEW: CCDirector::sharedDirector()->replaceScene(menuScene); break;   
  }
  menuScene->release();
}


void NavigationManager::showScene(SceneType sceneType, GameContext* gameContext, SceneRenderMode sceneRenderMode, bool showSplashScreen)
{    
  CCScene* scene;
  CCDirector::sharedDirector()->purgeCachedData();
  
  switch(sceneRenderMode)
  {
  case FIRST_RUN:  
    scene = resetGameContextScene(sceneType, gameContext, showSplashScreen);
    CCDirector::sharedDirector()->runWithScene(scene);
    scene->release();
    break;

  case NEW:      
    scene = resetGameContextScene(sceneType, gameContext, showSplashScreen);
    CCDirector::sharedDirector()->replaceScene(scene);
    scene->release();
    break;
      
  case PUSH:
    scene = resetGameContextScene(sceneType, gameContext, showSplashScreen);
    CCDirector::sharedDirector()->pushScene(scene);
    scene->release();
    break;
      
  case POP:
    CCDirector::sharedDirector()->popScene(); // TODO (Roman): does that clear???
    break;    
  }
}