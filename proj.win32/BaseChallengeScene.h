#ifndef __BASECHALLENGESCENE_SCENE_H__
#define __BASECHALLENGESCENE_SCENE_H__

#include "BaseScene.h"
#include "TopBar.h"
#include "WildcardPopup.h"
#include "GameScorePopup.h"
#include "DescriptionPopup.h"
#include "LifeTimeTickerPopup.h"

#include "stdlib.h"
#include "time.h"

class BaseChallengeScene : public BaseScene
{
private:

  ChallengeSceneType m_challengeSceneType;
  GameScorePopupType m_gameScorePopupType;

#if SHOWCONSOLEBUTTON
  ImageButton* m_consoleButton;
#endif

  void mainMenuCallback(CCObject* pSender); 
  void nextChallengeCallback(CCObject* pSender); 

  void closeCallback(CCObject* pSender); 
  
protected:
  
  GameButton* m_lastButtonPressed;
  GameButton* m_nextSequenceButton;

  std::vector<WildcardButtonDefinition> m_wildcardButtonDefinitions;

  std::string m_wildcardScoreInfoLeft;
  std::string m_wildcardScoreInfoRight;
  bool m_showWildcardScoreInfo;
  bool m_hasUserStartedGame;

  float m_eogElaspedTime, m_eogElapsedTimeWrongButton;
  float m_eogTargetTime, m_eogTargetTimeLastButton;
  int m_eogTotalWrongButtonBlinks;
  void eogGrayOutButtons(float dt);
  void eogBlinkCorrectButton(float dt);
  void eogGrayOutLastButton(float dt);
  void eogReleaseLastButton(float dt);
  void eogAnimationFinish(float dt);
  void eogResetButtons(float dt);

  int m_totalEnabledButtons;
  unsigned int m_totalVisibleButtons;

  bool m_isLayoutInitialized;
  int m_challengeIndex;

  CCSprite* m_consoleBackground;

  WildcardPopup* m_wildcardPopup; 
  GameScorePopup* m_gameScorePopup;
  LifeTimeTickerPopup* m_lifeTimeTickerPopup;
  int m_buttonSequenceIndex;

  std::vector<GameButton*> m_buttonSequence;
  GameScore m_gameScore;

  void newGameCallback(CCObject* pSender);

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
  struct cc_timeval *m_firstUserSequencePressedTime;

  float updateTimeVal(cc_timeval* time);

  ChallengePointScoreDefinition m_challengePointScoreDefinition;
  virtual int updateChallengeInfo(const ChallengePointScoreDefinition* challengePointScoreDefinition);

  virtual void initialize(float dt);
  
  void playConsoleLabelAnimation(std::string text, int colorShade);
  void playConsoleLabelAnimation(std::string text, float d, float maxScale, float delay, int colorShade);
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
    
  BaseChallengeScene(GameContext* gameContext, bool showSplashScreen, int challengeIndex
    , ChallengeSceneType challengeSceneType, int totalEnabledButtons, ChallengePointScoreDefinition challengePointScoreDefinition
    , GameScorePopupType gameScorePopupType)   
    : BaseScene(gameContext, showSplashScreen)
    , m_isLayoutInitialized(false) 
    , m_buttons(NULL)
    , m_lastButtonPressedTime(0)
    , m_firstUserSequencePressedTime(0)
    , m_totalEnabledButtons(totalEnabledButtons)
    , m_challengeSceneType(challengeSceneType)
    , m_consoleBackground(NULL)
    , m_topBar(NULL)
    , m_wildcardPopup(NULL)
    , m_gameScorePopup(NULL)
    , m_challengeIndex(challengeIndex)
    , m_lastButtonPressed(NULL)
    , m_nextSequenceButton(NULL)
    , m_challengePointScoreDefinition(challengePointScoreDefinition)
    , m_gameScorePopupType(gameScorePopupType)
    , m_lifeTimeTickerPopup(NULL)
    , m_showWildcardScoreInfo(false)
    , m_wildcardScoreInfoLeft("")
    , m_wildcardScoreInfoRight("")
    , m_hasUserStartedGame(false)
  { }
  ~BaseChallengeScene()
  {
    // TODO (Roman): memory management...
  }
  
  virtual void onEnter();
  virtual void onExit();
  virtual void onBackKeyPressed();
  virtual bool init();

protected:

  virtual void onLoadDescriptionPopup() { /* can be overridden */ }
  virtual void startNewGame() { /* can be overridden */ }

  virtual void onCorrectButtonPressed() { /* can be overridden */ }
  virtual void onIncorrectButtonPressed() { /* can be overridden */ }

  virtual void onSequenceBlinkCallback(GameButton* gameButton) { /* can be overridden */ }
  
  virtual void onPreInitialize() { /* can be overridden */ }
  virtual void onPostInitialize() { /* can be overridden */ }
};

#endif  // __BASECHALLENGESCENE_SCENE_H__