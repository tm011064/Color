#ifndef __BASECHALLENGESCENE_SCENE_H__
#define __BASECHALLENGESCENE_SCENE_H__

#include "BaseScene.h"
#include "TopBar.h"
#include "WildcardPopup.h"
#include "GameScorePopup.h"
#include "DescriptionPopup.h"

#include "stdlib.h"
#include "time.h"

class BaseChallengeScene : public BaseScene
{
private:

  ChallengeSceneType m_challengeSceneType;

  ImageButton* m_consoleButton;
  
  void newGameCallback(CCObject* pSender);
  void mainMenuCallback(CCObject* pSender); 
  
  void replaySequenceCallback(CCObject* pSender);
  void showNextSequenceItemCallback(CCObject* pSender);
  void replayFromCurrentCallback(CCObject* pSender); 

  void closeCallback(CCObject* pSender); 
  

protected:
  int m_totalButtons;
  bool m_isLayoutInitialized;
  int m_challengeIndex;

  CCLabelBMFont* m_loadingScreenText;
  RepeatingSprite* m_loadingScreen;
  CCSprite* m_consoleBackground;

  WildcardPopup* m_wildcardPopup; 
  GameScorePopup* m_gameScorePopup;
  int m_buttonSequenceIndex;

  std::vector<GameButton*> m_buttonSequence;
  GameScore m_gameScore;

  void buttonTouchEndedCallback(CCObject* pSender);
  void buttonLoadedCallback(CCObject* pSender);
  void buttonBlinkCallback(CCObject* pSender);
  void consoleButtonTouchEndedCallback(CCObject* pSender);
  
  CCArray* m_buttons;
  CCPoint m_anchor;

  TopBar* m_topBar;
  DescriptionPopup* m_descriptionPopup;
  CCLabelBMFont* m_levelDoneLabel;
  
  struct cc_timeval *m_lastButtonPressedTime;
  struct cc_timeval *m_lastLevelStartTime;

  float updateTimeVal(cc_timeval* time);
  int updateChallengeInfo(const ChallengePointScoreDefinition* challengePointScoreDefinition);
  void preLoadCallback(float dt);

public:
    
  BaseChallengeScene::BaseChallengeScene(GameContext* gameContext, int challengeIndex, ChallengeSceneType challengeSceneType, int totalButtons)   
    : BaseScene(gameContext)
    , m_isLayoutInitialized(false) 
    , m_buttons(NULL)
    , m_loadingScreen(NULL)
    , m_lastButtonPressedTime(0)
    , m_lastLevelStartTime(0)
    , m_totalButtons(totalButtons)
    , m_challengeSceneType(challengeSceneType)
    , m_consoleBackground(NULL)
    , m_topBar(NULL)
    , m_wildcardPopup(NULL)
    , m_gameScorePopup(NULL)
    , m_challengeIndex(challengeIndex)
    , m_loadingScreenText(NULL)
  { }
  ~BaseChallengeScene()
  {
    // TODO (Roman): memory management...
  }
  
  virtual void onExit();
  virtual void onEnter();
  virtual void onBackKeyPressed();
  virtual bool init();

protected:

  virtual void startNewGame() { /* can be overridden */ }

  virtual void onReplaySequenceCallback() { /* can be overridden */ }
  virtual void onShowNextSequenceItemCallback() { /* can be overridden */ }
  virtual void onReplayFromCurrentCallback() { /* can be overridden */ }
  virtual void onCorrectButtonPressed() { /* can be overridden */ }
  virtual void onIncorrectButtonPressed() { /* can be overridden */ }

  virtual void onSequenceBlinkCallback(GameButton* gameButton) { /* can be overridden */ }

  virtual void onLoadLayout() { /* can be overridden */ }
  virtual void onLayoutLoaded() { /* can be overridden */ }
  virtual void onPreLoad() { /* can be overridden */ }
};

#endif  // __BASECHALLENGESCENE_SCENE_H__