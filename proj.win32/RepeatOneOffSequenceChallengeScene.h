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

  void replaySequenceCallback(CCObject* pSender);
  void replaySequenceRemainingCallback(CCObject* pSender);

  RepeatOneOffSequenceChallengeScene(GameContext* gameContext, bool showSplashScreen, int challengeIndex, int totalEnabledButtons, ChallengeSceneType challengeSceneType, ChallengePointScoreDefinition challengePointScoreDefinition
    , int levelToReach)
    : BaseChallengeScene(gameContext, showSplashScreen,  challengeIndex, challengeSceneType, totalEnabledButtons, challengePointScoreDefinition
                         , GSPTYPE_POINTS)
    , m_levelToReach(levelToReach)
  {

  }
public:
  ~RepeatOneOffSequenceChallengeScene() { }
  
  static RepeatOneOffSequenceChallengeScene* create(GameContext* gameContext, bool showSplashScreen, int challengeIndex, int totalEnabledButtons, ChallengePointScoreDefinition challengePointScoreDefinition, int levelToReach); 

protected:  
  virtual void onPreInitialize();
  virtual void onLoadDescriptionPopup();
  virtual void onPostInitialize();
  
  virtual void startNewGame();
  virtual void onSequenceBlinkCallback(GameButton* gameButton);

  virtual void onCorrectButtonPressed();
  virtual void onIncorrectButtonPressed();
};

#endif  // __REPEAT_ONE_OFF_SCENE_H__