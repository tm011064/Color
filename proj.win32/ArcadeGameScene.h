#ifndef __ARCADEGAME_SCENE_H__
#define __ARCADEGAME_SCENE_H__

#include "cocos2d.h"
#include "BaseScene.h"
#include "TopBar.h"
#include "WildcardPopup.h"
#include "GameScorePopup.h"

#include "stdlib.h"
#include "time.h"

class ArcadeGameScene : public BaseScene
{
private:
  
  std::vector<GameButton*> m_buttonSequence;
  
  GameButton* m_lastButtonPressed;
  GameButton* m_nextSequenceButton;

  void update(float delta);
  void runSequenceAnimation(bool doAddButton, int startIndex, int endIndex);
  void runSequenceAnimationTimerCallback(float dt);

  int m_buttonSequenceIndex;
    
  float updateTimeVal(cc_timeval* time);
  SceneType m_sceneType;

  WildcardPopup* m_wildcardPopup; 
  GameScorePopup* m_gameScorePopup; 
  
  ImageButton* m_consoleButton;
  CCLabelBMFont* m_levelDoneLabel;

  int m_lastStartIndex;
  int m_lastEndIndex;
  
  void newGameCallback(CCObject* pSender);
  void mainMenuCallback(CCObject* pSender); 

  float m_eogElaspedTime, m_eogElapsedTimeWrongButton;
  float m_eogTargetTime, m_eogTargetTimeLastButton;
  int m_eogTotalWrongButtonBlinks;
  void eogGrayOutButtons(float dt);
  void eogBlinkCorrectButton(float dt);
  void eogGrayOutLastButton(float dt);
  void eogReleaseLastButton(float dt);
  void eogAnimationFinish(float dt);
  void eogResetButtons(float dt);
  
  void replaySequenceCallback(CCObject* pSender);
  void showNextSequenceItemCallback(CCObject* pSender);
  void replayFromCurrentCallback(CCObject* pSender); 
  void closeCallback(CCObject* pSender); 

  void startNewGame();
  void preLoadCallback(float dt);


protected:
  
  unsigned int m_totalVisibleButtons;
  int m_totalEnabledButtons;
  bool m_isLayoutInitialized;
  float m_buttonScale;

  CCSprite* m_consoleBackground;
  
  CCArray *m_buttons;
  CCPoint m_anchor;

  TopBar* m_topBar;
  GameScore m_gameScore;
  ChallengePointScoreDefinition m_challengePointScoreDefinition;
  
  struct cc_timeval *m_lastButtonPressedTime;
  struct cc_timeval *m_lastLevelStartTime;

  virtual void initialize(float dt);

public:
  
  ArcadeGameScene(GameContext* gameContext, SceneType sceneType, int totalEnabledButtons, bool showSplashScreen)   
    : BaseScene(gameContext, showSplashScreen)
    , m_isLayoutInitialized(false) 
    , m_buttonScale(.0f)
    , m_buttons(NULL)
    , m_lastButtonPressedTime(0)
    , m_lastLevelStartTime(0)
    , m_totalEnabledButtons(totalEnabledButtons)
    , m_sceneType(sceneType)
    , m_consoleBackground(NULL)
    , m_topBar(NULL)
    , m_wildcardPopup(NULL)
    , m_gameScorePopup(NULL)
    , m_lastButtonPressed(NULL)
    , m_nextSequenceButton(NULL)
  { }

  ~ArcadeGameScene() { }
  
  virtual void onExit();
  virtual void onBackKeyPressed();
  virtual bool init();

protected:
  virtual void buttonTouchEndedCallback(CCObject* pSender);
  virtual void buttonLoadedCallback(CCObject* pSender);
  virtual void buttonBlinkCallback(CCObject* pSender);
  virtual void consoleButtonTouchEndedCallback(CCObject* pSender);  

  virtual void onGameOver() { /* can be overridden */ }
  virtual void onLoadLayout() { /* can be overridden */ }
  virtual void onPreLoad() { /* can be overridden */ }
};

#endif  // __ARCADEGAME_SCENE_H__