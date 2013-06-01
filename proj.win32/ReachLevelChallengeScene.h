#ifndef __REACH_LEVEL_SCENE_H__
#define __REACH_LEVEL_SCENE_H__

#include "BaseChallengeScene.h"

class ReachLevelChallengeScene : public BaseChallengeScene
{
private:

  ChallengePointScoreDefinition m_challengePointScoreDefinition;
  int m_levelToReach;
  int m_lastStartIndex;
  int m_lastEndIndex;
    
  void runSequenceAnimation(bool doAddButton, int startIndex, int endIndex);
  void update(float delta);

  void initialize();

  ReachLevelChallengeScene(GameContext* gameContext, int challengeIndex, int totalButtons, ChallengeSceneType challengeSceneType, ChallengePointScoreDefinition challengePointScoreDefinition
    , int levelToReach)
    : BaseChallengeScene(gameContext, challengeIndex, challengeSceneType, totalButtons)
    , m_challengePointScoreDefinition(challengePointScoreDefinition)
    , m_levelToReach(levelToReach)
  {

  }
public:
  ~ReachLevelChallengeScene() { }
  
  static ReachLevelChallengeScene* create(GameContext* gameContext, int challengeIndex, int totalButtons, ChallengePointScoreDefinition challengePointScoreDefinition, int levelToReach); 

protected:  
  virtual void onLoadLayout();
  virtual void onLayoutLoaded();
  virtual void startNewGame();
  virtual void onSequenceBlinkCallback(GameButton* gameButton);

  virtual void onCorrectButtonPressed();
  virtual void onIncorrectButtonPressed();
};

#endif  // __REACH_LEVEL_SCENE_H__