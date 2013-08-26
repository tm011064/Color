#ifndef __EXACT_LENGTH_CHALLENGE_SCENE_H__
#define __EXACT_LENGTH_CHALLENGE_SCENE_H__

#include "BaseChallengeScene.h"

typedef struct 
{
  cc_timeval startTime;
  cc_timeval endTime;
  float duration;
  GameButton* button;
  bool hasEnded;
  float startOffset;
  float durationOffset;
  float correctPercentage;
} ButtonBlinkTimePeriod;

class ExactLengthChallengeScene : public BaseChallengeScene
{
private:

  struct ButtonBlinkTimePeriodComparer 
  {
    bool operator() (const ButtonBlinkTimePeriod &a, const ButtonBlinkTimePeriod &b) const 
    {
      return UtilityHelper::isLessThan(a.startTime, b.startTime);
    }
  };

  float m_minButtonSignalLength;
  float m_maxButtonSignalLength;
  float m_minNextSignalDeltaFromLastEndTime;
  float m_maxNextSignalDeltaFromLastEndTime;
  
  std::vector<ButtonBlinkTimePeriod> m_buttonBlinkTimePeriods;
  std::vector<ButtonBlinkTimePeriod> m_userPressedTimePeriods;

  void startButtonBlinkCallback(CCObject* o);
  void endButtonBlinkCallback(CCObject* o);

  void runSequenceAnimation();
  
  float getRandom(float min, float max) { return (max - min) * ( (float)rand() / (float)RAND_MAX ) + min; } 

  void initialize();

  void onWrongButton(GameButton* lastButtonPressed, GameButton* nextSequenceButton);

  ExactLengthChallengeScene(GameContext* gameContext, bool showSplashScreen, int challengeIndex
    , int totalEnabledButtons, float minButtonSignalLength, float maxButtonSignalLength
    , float minNextSignalDeltaFromLastEndTime, float maxNextSignalDeltaFromLastEndTime
    , ChallengeSceneType challengeSceneType, ChallengePointScoreDefinition challengePointScoreDefinition)
    : BaseChallengeScene(gameContext, showSplashScreen,  challengeIndex, challengeSceneType, totalEnabledButtons, challengePointScoreDefinition
                         , GSPTYPE_TIME_INTERVALS)
    , m_minButtonSignalLength(minButtonSignalLength)
    , m_maxButtonSignalLength(maxButtonSignalLength)
    , m_minNextSignalDeltaFromLastEndTime(minNextSignalDeltaFromLastEndTime)
    , m_maxNextSignalDeltaFromLastEndTime(maxNextSignalDeltaFromLastEndTime)
  {

  }
public:
  ~ExactLengthChallengeScene() { }
  
  static ExactLengthChallengeScene* create(GameContext* gameContext, bool showSplashScreen, int challengeIndex
    , int totalEnabledButtons, float minButtonSignalLength, float maxButtonSignalLength
    , float minNextSignalDeltaFromLastEndTime, float maxNextSignalDeltaFromLastEndTime
    , ChallengePointScoreDefinition challengePointScoreDefinition); 
  
protected:  
  virtual int updateChallengeInfo(const ChallengePointScoreDefinition* challengePointScoreDefinition);

  virtual void onLoadDescriptionPopup();
  virtual void onLoadLayout();
  virtual void onLayoutLoaded();
  virtual void startNewGame();
  
  virtual void buttonTouchEndedCallback(CCObject* pSender);
};

#endif  // __EXACT_LENGTH_CHALLENGE_SCENE_H__