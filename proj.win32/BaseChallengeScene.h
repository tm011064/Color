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
  GameScorePopupType m_gameScorePopupType;
  ImageButton* m_consoleButton;
  
  void newGameCallback(CCObject* pSender);
  void mainMenuCallback(CCObject* pSender); 
  
  void replaySequenceCallback(CCObject* pSender);
  void showNextSequenceItemCallback(CCObject* pSender);
  void replayFromCurrentCallback(CCObject* pSender); 

  void closeCallback(CCObject* pSender); 
  

protected:
  
  GameButton* m_lastButtonPressed;
  GameButton* m_nextSequenceButton;

  float m_eogElaspedTime, m_eogElapsedTimeWrongButton;
  float m_eogTargetTime, m_eogTargetTimeLastButton;
  int m_eogTotalWrongButtonBlinks;
  void eogGrayOutButtons(float dt);
  void eogBlinkCorrectButton(float dt);
  void eogGrayOutLastButton(float dt);
  void eogReleaseLastButton(float dt);
  void eogAnimationFinish(float dt);
  void eogResetButtons(float dt);

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

  virtual void buttonTouchEndedCallback(CCObject* pSender);
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

  bool m_challengeCompleted;
  ChallengePointScoreDefinition m_challengePointScoreDefinition;
  virtual int updateChallengeInfo(const ChallengePointScoreDefinition* challengePointScoreDefinition);

  void playConsoleLabelAnimation(std::string text);
  void playConsoleLabelAnimation(std::string text, float d, float maxScale, float delay);
  void playConsoleLabelAnimation(std::string text, float d, float maxScale, float delay, ccColor3B color);
  void playBlinkButtonsAnimation(int totalBlinks, float interval, float delay);
  void playHighlightButtonsAnimation(float d, float delay);

  void preLoadCallback(float dt);
  void showGameScorePopupCallback(float dt);
  void blinkButtonCallback(float dt);
  void allButtonsPressingAnimationCallback(float dt);
  void allButtonsReleaseAnimationCallback(float dt);

public:
    
  BaseChallengeScene::BaseChallengeScene(GameContext* gameContext, int challengeIndex
    , ChallengeSceneType challengeSceneType, int totalButtons, ChallengePointScoreDefinition challengePointScoreDefinition
    , GameScorePopupType gameScorePopupType)   
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
    , m_lastButtonPressed(NULL)
    , m_nextSequenceButton(NULL)
    , m_challengeCompleted(false)
    , m_challengePointScoreDefinition(challengePointScoreDefinition)
    , m_gameScorePopupType(gameScorePopupType)
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