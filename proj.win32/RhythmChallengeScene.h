#ifndef __RHYTHM_CHALLENGE_SCENE_H__
#define __RHYTHM_CHALLENGE_SCENE_H__

#include "BaseChallengeScene.h"

typedef struct 
{
  float blinkTime;
  int buttonIndex;
  GameButton* button;
  
  float absoluteUserBlinkOffset;
  cc_timeval userBlinkActualTime;
  float userBlinkRelativeTime;

  bool areUserVariablesSet;
} RhythmBlink;

typedef struct
{
  std::vector<RhythmBlink> rhythmBlinks;
  int totalBlinks;
  float averageUserOffset;
} RhythmBlinkSequence;

typedef struct
{
  std::vector<RhythmBlinkSequence> rhythmBlinkSequences;
  int totalButtons;
  int totalSequences;
  std::string name;
} RhythmBlinkSequenceDefinition;

class RhythmChallengeScene : public BaseChallengeScene
{
private:
  
  int m_currentSequenceIndex;
  RhythmBlinkSequenceDefinition m_rhythmBlinkSequenceDefinition;
  void runSequenceAnimation();
  void sequenceBlinkCallback(CCObject* pSender);
  void setAwaitingInput();

  RhythmChallengeScene(GameContext* gameContext, int challengeIndex
    , RhythmBlinkSequenceDefinition rhythmBlinkSequenceDefinition
    , ChallengeSceneType challengeSceneType, ChallengePointScoreDefinition challengePointScoreDefinition)
    : BaseChallengeScene(gameContext, challengeIndex, challengeSceneType, rhythmBlinkSequenceDefinition.totalButtons, challengePointScoreDefinition
                         , GSPTYPE_RHYTHM)
    , m_rhythmBlinkSequenceDefinition(rhythmBlinkSequenceDefinition)
    , m_currentSequenceIndex(0)
  {

  }
public:
  ~RhythmChallengeScene() { }
  
  static RhythmChallengeScene* create(GameContext* gameContext, int challengeIndex
    , RhythmBlinkSequenceDefinition rhythmBlinkSequenceDefinition
    , ChallengePointScoreDefinition challengePointScoreDefinition); 
  
  static RhythmBlinkSequenceDefinition loadRhythmBlinkSequenceDefinition(std::string filePath);

protected:  
  virtual int updateChallengeInfo(const ChallengePointScoreDefinition* challengePointScoreDefinition);
  
  virtual void onLoadLayout();
  virtual void onLayoutLoaded();
  virtual void startNewGame();

  virtual void onIncorrectButtonPressed();

  virtual void buttonTouchEndedCallback(CCObject* pSender);
};

#endif  // __RHYTHM_CHALLENGE_SCENE_H__