#ifndef __REPEAT_ONE_OFF_SCENE_H__
#define __REPEAT_ONE_OFF_SCENE_H__

#include "BaseChallengeScene.h"

class RepeatOneOffSequenceChallengeScene : public BaseChallengeScene
{
private:

  int m_levelToReach;
  int m_lastStartIndex;
  int m_lastEndIndex;
    
  void runSequenceAnimation(bool doAddButton, int startIndex, int endIndex);
  void update(float delta);

  void initialize();

  RepeatOneOffSequenceChallengeScene(GameContext* gameContext, int challengeIndex, int totalButtons, ChallengeSceneType challengeSceneType, ChallengePointScoreDefinition challengePointScoreDefinition
    , int levelToReach)
    : BaseChallengeScene(gameContext, challengeIndex, challengeSceneType, totalButtons, challengePointScoreDefinition
                         , GSPTYPE_POINTS)
    , m_levelToReach(levelToReach)
  {

  }
public:
  ~RepeatOneOffSequenceChallengeScene() { }
  
  static RepeatOneOffSequenceChallengeScene* create(GameContext* gameContext, int challengeIndex, int totalButtons, ChallengePointScoreDefinition challengePointScoreDefinition, int levelToReach); 

protected:  
  virtual void onLoadLayout();
  virtual void onLayoutLoaded();
  virtual void startNewGame();
  virtual void onSequenceBlinkCallback(GameButton* gameButton);

  virtual void onCorrectButtonPressed();
  virtual void onIncorrectButtonPressed();
};

#endif  // __REPEAT_ONE_OFF_SCENE_H__