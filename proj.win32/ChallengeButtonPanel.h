#ifndef __CHALLENGE_BUTTON_PANEL_H__
#define __CHALLENGE_BUTTON_PANEL_H__

#include "GameEngineIncludes.h"

using namespace cocos2d;

class ChallengeButtonPanel : public BaseNode
{  
private:
  
  bool m_isLayoutInitialized;
  bool m_isLayoutReset;
  float m_padding;
  float m_borderThickness;

  CCLabelBMFont* m_totalLifeLabel;
  CCLabelBMFont* m_deltaNextLifeIncreaseLabel_M1;
  CCLabelBMFont* m_deltaNextLifeIncreaseLabel_M2;
  CCLabelBMFont* m_deltaNextLifeIncreaseLabel_Separator;
  CCLabelBMFont* m_deltaNextLifeIncreaseLabel_S1;
  CCLabelBMFont* m_deltaNextLifeIncreaseLabel_S2;

  CCLabelBMFont* m_nextLifeText_Left;
  CCLabelBMFont* m_nextLifeText_Right;

  float m_rightPosX_M1;
  float m_rightPosX_M2;
  float m_rightPosX_S1;
  float m_rightPosX_S2;
  
  CCSprite* m_heart;
  TextButton* m_storyModeNextPage;
  TextButton* m_storyModePreviousPage;
  std::vector<ChallengeButton*> m_challengeButtons;
  
  CCPoint m_rectOrigin;
  CCPoint m_rectDestination;
  CCPoint m_borderOrigin;
  CCPoint m_borderDestination;

  ccColor4F m_rectColor;
  ccColor4F m_borderColor;

  int m_storyModePageIndex;

  GameContext* m_pGameContext; 

  void goBackCallback(CCObject* pSender); 
  void resetChallengeButtons(bool isVisible);
  void updateLifeDisplay(float dt);

  SEL_CallFunc m_fnpGoBackDelegate;
  
  CCNode *m_pTarget;

public:
  static ChallengeButtonPanel* create(GameContext* gameContext
    , SEL_CallFunc goBackDelegate, CCNode* callbackTarget);
  ~ChallengeButtonPanel() 
  { 
    this->m_pGameContext = NULL;
    this->m_pTarget = NULL;
  }
  
  virtual void onEnter();
  virtual void reset();
  virtual void draw();

protected:
  ChallengeButtonPanel(GameContext* gameContext
    , SEL_CallFunc goBackDelegate
    , CCNode* callbackTarget)
    : m_pGameContext(gameContext)
    , m_fnpGoBackDelegate(goBackDelegate)
    , m_pTarget(callbackTarget)
    , m_isLayoutInitialized(false)
    , m_isLayoutReset(false)
    , m_storyModePageIndex(0)
    , m_totalLifeLabel(NULL)
    , m_deltaNextLifeIncreaseLabel_M1(NULL)
    , m_deltaNextLifeIncreaseLabel_M2(NULL)
    , m_deltaNextLifeIncreaseLabel_Separator(NULL)
    , m_deltaNextLifeIncreaseLabel_S1(NULL)
    , m_deltaNextLifeIncreaseLabel_S2(NULL)
    , m_heart(NULL)
    , m_nextLifeText_Left(NULL)
    , m_nextLifeText_Right(NULL)
  { }

  virtual void startChallenge(CCObject* pSender);
  virtual void nextStoryModePage(CCObject* pSender);
  virtual void previousStoryModePage(CCObject* pSender);
};

#endif  // __CHALLENGE_BUTTON_PANEL_H__