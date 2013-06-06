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

  bool m_bIsFirstDraw;  
  
  std::vector<GameButton*> m_buttonSequence;
  
  GameButton* m_lastButtonPressed;
  GameButton* m_nextSequenceButton;

  void update(float delta);
  void runSequenceAnimation(bool doAddButton, int startIndex, int endIndex);

  int m_buttonSequenceIndex;
    
  float updateTimeVal(cc_timeval* time);
  SceneType m_sceneType;

  WildcardPopup* m_wildcardPopup; 
  GameScorePopup* m_gameScorePopup; 
  
  ImageButton* m_consoleButton;

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

protected:
  int m_totalButtons;
  bool m_isInitialized;
  bool m_isLayoutInitialized;
  float m_buttonScale;

  CCSprite* m_loadingScreen;
  CCSprite* m_backgroundNormal;
  CCSprite* m_consoleBackground;
  
  CCArray *m_buttons;
  CCPoint m_anchor;

  TopBar* m_topBar;
  GameScore m_gameScore;
  ChallengePointScoreDefinition m_challengePointScoreDefinition;
  
  struct cc_timeval *m_lastButtonPressedTime;
  struct cc_timeval *m_lastLevelStartTime;

public:

  ArcadeGameScene(GameContext* gameContext, SceneType sceneType, int totalButtons);
  ~ArcadeGameScene();
  
  virtual void onEnter();
  virtual void draw();
  virtual void onBackKeyPressed();

protected:
  virtual void buttonTouchEndedCallback(CCObject* pSender);
  virtual void buttonLoadedCallback(CCObject* pSender);
  virtual void buttonBlinkCallback(CCObject* pSender);
  virtual void consoleButtonTouchEndedCallback(CCObject* pSender);  

  virtual void onGameOver() { /* can be overridden */ }
  virtual void onLoadLayout() { /* can be overridden */ }
};

#endif  // __ARCADEGAME_SCENE_H__