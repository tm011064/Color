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
  MenuScene* menuScene;
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

  case MENU_SCENE: 
    
    menuScene = new MenuScene(gameContext, showSplashScreen);
        
    pLayer = new BaseLayer(menuScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    menuScene->addChild(pLayer);
    
    return menuScene;

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
  
  float levelToReach, totalCorrectButtons;
  ChallengePointScoreDefinition challengePointScoreDefinition;
  RhythmBlinkSequenceDefinition rhythmBlinkSequenceDefinition;

  switch (challengeIndex)
  {
  case 0:

    levelToReach = 3;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );

    challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_TWO_BUTTONS;
    challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_TWO_BUTTONS_MAX_TIME_BONUS;
    challengePointScoreDefinition.clickTimeThreshold = TWO_BUTTON_CLICK_TIME_THRESHOLD;
    challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_TWO_BUTTONS_LEVEL_BONUS;
    challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_TWO_BUTTONS_MAX_LEVEL_TIME_BONUS;
    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_TWO_BUTTONS_MULTIPLIER;

    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .4f
      + challengePointScoreDefinition.maxTimeBonus * totalCorrectButtons * .4f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .6f
      + challengePointScoreDefinition.maxTimeBonus * totalCorrectButtons * .6f;

    reachLevelChallengeScene = ReachLevelChallengeScene::create(gameContext, showSplashScreen, challengeIndex, 2, challengePointScoreDefinition
      , (int)levelToReach);
    //reachLevelChallengeScene->init();
    
    pLayer = new BaseLayer(reachLevelChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    reachLevelChallengeScene->addChild(pLayer); 

    return reachLevelChallengeScene;

  case 1:

    levelToReach = 3;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );

    challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_THREE_BUTTONS;
    challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_TIME_BONUS;
    challengePointScoreDefinition.clickTimeThreshold = THREE_BUTTON_CLICK_TIME_THRESHOLD;
    challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_LEVEL_BONUS;
    challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_LEVEL_TIME_BONUS;
    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_THREE_BUTTONS_MULTIPLIER;
        
    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .4f
      + challengePointScoreDefinition.maxTimeBonus * totalCorrectButtons * .4f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .6f
      + challengePointScoreDefinition.maxTimeBonus * totalCorrectButtons * .6f;

    reachLevelChallengeScene = ReachLevelChallengeScene::create(gameContext, showSplashScreen, challengeIndex, 3, challengePointScoreDefinition
      , (int)levelToReach);
    reachLevelChallengeScene->init();
    
    pLayer = new BaseLayer(reachLevelChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    reachLevelChallengeScene->addChild(pLayer); 

    return reachLevelChallengeScene;

  case 2:

    levelToReach = 3;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );

    challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_THREE_BUTTONS;
    challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_TIME_BONUS;
    challengePointScoreDefinition.clickTimeThreshold = THREE_BUTTON_CLICK_TIME_THRESHOLD;
    challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_LEVEL_BONUS;
    challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_LEVEL_TIME_BONUS;
    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_THREE_BUTTONS_MULTIPLIER;
    // TODO (Roman): points!
    
    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .4f
      + challengePointScoreDefinition.maxTimeBonus * totalCorrectButtons * .4f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .6f
      + challengePointScoreDefinition.maxTimeBonus * totalCorrectButtons * .6f;

    repeatOneOffSequenceChallengeScene = RepeatOneOffSequenceChallengeScene::create(gameContext, showSplashScreen, challengeIndex, 3, challengePointScoreDefinition
      , (int)levelToReach);
    repeatOneOffSequenceChallengeScene->init();
    
    pLayer = new BaseLayer(repeatOneOffSequenceChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    repeatOneOffSequenceChallengeScene->addChild(pLayer); 

    return repeatOneOffSequenceChallengeScene;
  case 3:

    levelToReach = 2;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );

    challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_FOUR_BUTTONS;
    challengePointScoreDefinition.maxTimeBonus = CORRECT_BUTTON_SCORE_FOUR_BUTTONS_MAX_TIME_BONUS;
    challengePointScoreDefinition.clickTimeThreshold = FOUR_BUTTON_CLICK_TIME_THRESHOLD;
    challengePointScoreDefinition.levelBonus = CORRECT_BUTTON_SCORE_FOUR_BUTTONS_LEVEL_BONUS;
    challengePointScoreDefinition.maxLevelTimeBonus = CORRECT_BUTTON_SCORE_FOUR_BUTTONS_MAX_LEVEL_TIME_BONUS;
    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_FOUR_BUTTONS_MULTIPLIER;
    // TODO (Roman): points!
    
    challengePointScoreDefinition.mininimumPointsForOneStar = 0;
    challengePointScoreDefinition.mininimumPointsForTwoStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .4f
      + challengePointScoreDefinition.maxTimeBonus * totalCorrectButtons * .4f;

    challengePointScoreDefinition.mininimumPointsForThreeStars = 
      challengePointScoreDefinition.levelBonus * levelToReach
      + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
      + challengePointScoreDefinition.maxLevelTimeBonus * levelToReach * .6f
      + challengePointScoreDefinition.maxTimeBonus * totalCorrectButtons * .6f;

    repeatOneOffSequenceChallengeScene = RepeatOneOffSequenceChallengeScene::create(gameContext, showSplashScreen, challengeIndex, 4, challengePointScoreDefinition
      , (int)levelToReach);
    repeatOneOffSequenceChallengeScene->init();
    
    pLayer = new BaseLayer(repeatOneOffSequenceChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    repeatOneOffSequenceChallengeScene->addChild(pLayer); 

    return repeatOneOffSequenceChallengeScene;
    
  case 4:

    levelToReach = 2;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );

    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_THREE_BUTTONS_MULTIPLIER;
    challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_THREE_BUTTONS;
    // TODO (Roman): points!
    
    challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
    challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
    challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;

    exactLengthChallengeScene = ExactLengthChallengeScene::create(gameContext, showSplashScreen, challengeIndex, 4
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

    levelToReach = 2;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );

    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_THREE_BUTTONS_MULTIPLIER;
    challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_THREE_BUTTONS;
    // TODO (Roman): points!
    
    challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
    challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
    challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;

    exactLengthChallengeScene = ExactLengthChallengeScene::create(gameContext, showSplashScreen, challengeIndex, 1
      , 6.0f, 6.0f
      , 1.0f, 1.0f
      , challengePointScoreDefinition);
    exactLengthChallengeScene->init();
    
    pLayer = new BaseLayer(exactLengthChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    exactLengthChallengeScene->addChild(pLayer); 

    return exactLengthChallengeScene;

  case 6:

    levelToReach = 2;
    totalCorrectButtons = (levelToReach / 2.0f) * ( 1.0f + levelToReach );

    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_THREE_BUTTONS_MULTIPLIER;
    challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_THREE_BUTTONS;
    // TODO (Roman): points!
    
    challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
    challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
    challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;

    exactLengthChallengeScene = ExactLengthChallengeScene::create(gameContext, showSplashScreen, challengeIndex, 3
      , 2.0f, 2.0f
      , 1.0f, 1.0f
      , challengePointScoreDefinition);
    exactLengthChallengeScene->init();
    
    pLayer = new BaseLayer(exactLengthChallengeScene, callfunc_selector( BaseScene::onBackKeyPressed ) );
    pLayer->init(); 
    pLayer->autorelease();

    exactLengthChallengeScene->addChild(pLayer); 

    return exactLengthChallengeScene;
        
  case 7:
    // TODO (Roman): this should come from resource plist lookup

    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_TWO_BUTTONS_MULTIPLIER;
    challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_TWO_BUTTONS;
    // TODO (Roman): points!
    
    challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .1f;
    challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .15f;
    challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .2f;

    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_THREE_BUTTONS_MULTIPLIER;
    rhythmBlinkSequenceDefinition = RhythmChallengeScene::loadRhythmBlinkSequenceDefinition(CCFileUtils::sharedFileUtils()->fullPathForFilename("rhythmChallenge_1.txt"));
    rhythmChallengeScene = RhythmChallengeScene::create(gameContext, showSplashScreen, challengeIndex, rhythmBlinkSequenceDefinition, challengePointScoreDefinition);

    return rhythmChallengeScene;
    
  case 8:
    // TODO (Roman): this should come from resource plist lookup

    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_FOUR_BUTTONS_MULTIPLIER;
    challengePointScoreDefinition.correctButtonScore = CORRECT_BUTTON_SCORE_FOUR_BUTTONS;
    // TODO (Roman): points!
    
    challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .1f;
    challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .15;
    challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .2f;

    challengePointScoreDefinition.coinsEarnedMultiplier = COINS_EARNED_FOUR_BUTTONS_MULTIPLIER;
    rhythmBlinkSequenceDefinition = RhythmChallengeScene::loadRhythmBlinkSequenceDefinition(CCFileUtils::sharedFileUtils()->fullPathForFilename("rhythmChallenge_2.txt"));
    rhythmChallengeScene = RhythmChallengeScene::create(gameContext, showSplashScreen, challengeIndex, rhythmBlinkSequenceDefinition, challengePointScoreDefinition);

    return rhythmChallengeScene;
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