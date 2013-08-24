#ifndef __GAMESCORE_POPUP_H__
#define __GAMESCORE_POPUP_H__

#include "ModalControl.h"
#include "GameScorePointsPanel.h"
#include "GameScoreTimePanel.h"

using namespace cocos2d;

enum GameScorePopupType
{
  GSPTYPE_POINTS = 0,
  GSPTYPE_TIME_INTERVALS = 1,
  GSPTYPE_RHYTHM = 2,
};

enum GameScorePopupMode
{
  GSPMODE_CHALLENGE = 0,
  GSPMODE_ARCADE = 1,
};

class GameScorePopup : public ModalControl
{  
private:

  GameScorePopupType m_gameScorePopupType;
  GameScorePopupMode m_gameScorePopupMode;
  GameContext* m_pGameContext; 
    
  CCLabelBMFont* m_headerTextLabel;

  CCPoint m_separatorLineLeftBottom;
  CCPoint m_separatorLineRightTop;
    
  CCPoint m_dialogRectLeftTop;
  CCPoint m_dialogRectRightBottom;

  BaseNode* m_gameScorePanel;

  CCSprite* m_goldStar1;
  CCSprite* m_goldStar2;
  CCSprite* m_goldStar3;
  CCSprite* m_blackStar1;
  CCSprite* m_blackStar2;
  CCSprite* m_blackStar3;

  TextButton* m_retryButton;
  TextButton* m_replayButton;
  TextButton* m_nextButton;

  void playAgainCallback(CCObject* pSender);
  void mainMenuCallback(CCObject* pSender);
  void nextChallengeCallback(CCObject* pSender);
  
  SEL_CallFuncO m_fnpPlayAgainCallbackDelegate;
  SEL_CallFuncO m_fnpMainMenuCallbackDelegate;
  SEL_CallFuncO m_fnpNextChallengeCallbackDelegate;
  
  CCNode *m_pTarget;
  
  float m_elaspeTimePoints;
  float m_elaspeTimeCoins;
  float m_targetTime;

  std::string m_headerText;

  void updatePointsDisplay(float dt);
  void updateCoinsDisplay(float dt);

public:
  static GameScorePopup* create(GameContext* gameContext, std::string headerText
    , SEL_CallFuncO playAgainCallbackDelegate
    , SEL_CallFuncO mainMenuCallbackDelegate
    , SEL_CallFuncO nextChallengeCallbackDelegate
    , CCNode* callbackTarget, GameScorePopupType gameScorePopupType
    , GameScorePopupMode gameScorePopupMode);
  ~GameScorePopup() { }
  
  virtual void onEnter();
  virtual void draw();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) { return ModalControl::ccTouchBegan(pTouch, pEvent); }

  virtual void show();

protected:  
  GameScorePopup(GameContext* gameContext, std::string headerText
    , SEL_CallFuncO playAgainCallbackDelegate
    , SEL_CallFuncO mainMenuCallbackDelegate
    , SEL_CallFuncO nextChallengeCallbackDelegate
    , CCNode* callbackTarget, GameScorePopupType gameScorePopupType
    , GameScorePopupMode gameScorePopupMode)
    : m_pGameContext(gameContext)
    , m_fnpPlayAgainCallbackDelegate(playAgainCallbackDelegate)
    , m_fnpMainMenuCallbackDelegate(mainMenuCallbackDelegate)
    , m_fnpNextChallengeCallbackDelegate(nextChallengeCallbackDelegate)
    , m_pTarget(callbackTarget)
    , m_gameScorePanel(NULL)
    , m_headerText(headerText)
    , m_headerTextLabel(NULL)
    , m_gameScorePopupType(gameScorePopupType)
    , m_gameScorePopupMode(gameScorePopupMode)
    , m_retryButton(NULL)
    , m_nextButton(NULL)
    , m_replayButton(NULL)
    , m_goldStar1(NULL)
    , m_goldStar2(NULL)
    , m_goldStar3(NULL)
    , m_blackStar1(NULL)
    , m_blackStar2(NULL)
    , m_blackStar3(NULL)
  { }
};
#endif  // __GAMESCORE_POPUP_H__