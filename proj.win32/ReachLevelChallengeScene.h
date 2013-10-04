#ifndef __REACH_LEVEL_SCENE_H__
#define __REACH_LEVEL_SCENE_H__

#include "BaseChallengeScene.h"

class ReachLevelChallengeScene : public BaseChallengeScene
{
private:

  int m_levelToReach;
  int m_lastStartIndex;
  int m_lastEndIndex;
    
  float m_currentLevelPoints;

  void runSequenceAnimation(bool doAddButton, int startIndex, int endIndex);
  void runSequenceAnimationTimerCallback(float dt);
  void update(float delta);

  void initialize();

  void replaySequenceCallback(CCObject* pSender);
  void replaySequenceRemainingCallback(CCObject* pSender);

  ReachLevelChallengeScene(GameContext* gameContext, bool showSplashScreen, int challengeIndex, int totalEnabledButtons, ChallengeSceneType challengeSceneType, ChallengePointScoreDefinition challengePointScoreDefinition
    , int levelToReach)
    : BaseChallengeScene(gameContext, showSplashScreen,  challengeIndex, challengeSceneType, totalEnabledButtons, challengePointScoreDefinition
                         , GSPTYPE_POINTS)
    , m_levelToReach(levelToReach)
  {

  }
public:
  ~ReachLevelChallengeScene() { }
  
  static ReachLevelChallengeScene* create(GameContext* gameContext, bool showSplashScreen, int challengeIndex, int totalEnabledButtons, ChallengePointScoreDefinition challengePointScoreDefinition, int levelToReach); 

protected:  
  virtual void onPreInitialize();
  virtual void onLoadDescriptionPopup();
  virtual void onPostInitialize();
  
  virtual void startNewGame();
  virtual void onSequenceBlinkCallback(GameButton* gameButton);

  virtual void onCorrectButtonPressed();
  virtual void onIncorrectButtonPressed();
};

#endif  // __REACH_LEVEL_SCENE_H__