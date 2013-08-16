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

class GameScorePopup : public ModalControl
{  
private:

  GameScorePopupType m_gameScorePopupType;

  GameContext* m_pGameContext; 
    
  CCLabelBMFont* m_headerTextLabel;

  CCPoint m_separatorLineLeftBottom;
  CCPoint m_separatorLineRightTop;
    
  CCPoint m_dialogRectLeftTop;
  CCPoint m_dialogRectRightBottom;

  BaseNode* m_gameScorePanel;

  void playAgainCallback(CCObject* pSender);
  void mainMenuCallback(CCObject* pSender);
  
  SEL_CallFuncO m_fnpPlayAgainCallbackDelegate;
  SEL_CallFuncO m_fnpMainMenuCallbackDelegate;
  
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
    , CCNode* callbackTarget, GameScorePopupType gameScorePopupType);
  ~GameScorePopup() { }
  
  void setHeaderText(std::string text);

  virtual void onEnter();
  virtual void draw();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) { return ModalControl::ccTouchBegan(pTouch, pEvent); }

  virtual void show();

protected:  
  GameScorePopup(GameContext* gameContext, std::string headerText
    , SEL_CallFuncO playAgainCallbackDelegate
    , SEL_CallFuncO mainMenuCallbackDelegate
    , CCNode* callbackTarget, GameScorePopupType gameScorePopupType)
    : m_pGameContext(gameContext)
    , m_fnpPlayAgainCallbackDelegate(playAgainCallbackDelegate)
    , m_fnpMainMenuCallbackDelegate(mainMenuCallbackDelegate)
    , m_pTarget(callbackTarget)
    , m_gameScorePanel(NULL)
    , m_headerText(headerText)
    , m_headerTextLabel(NULL)
    , m_gameScorePopupType(gameScorePopupType)
  { }
};
#endif  // __GAMESCORE_POPUP_H__