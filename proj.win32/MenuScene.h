#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"
#include "BaseScene.h"
#include "ChallengeButtonPanel.h"

enum MenuViewType
{
  HOME = 0,
  ARCADE = 1,
  STORY_MODE = 2,
  OPTIONS = 3,
  HIGHSCORE = 4,
};

class MenuScene : public BaseScene
{
private:
  MenuViewType m_menuViewType;

  MenuButton* m_homeStoryMode;
  MenuButton* m_homeArcade;
  MenuButton* m_homeOptions;
  MenuButton* m_homeHighscore;
  MenuButton* m_arcadeEasy;
  MenuButton* m_arcadeNormal;
  MenuButton* m_arcadeHard;
  TextButton* m_arcadeBack;

  CCSprite* m_header;

  ChallengeButtonPanel* m_challengeButtonPanel; 

  void resetHomeButtons(bool isVisible);
  void resetArcadeButtons(bool isVisible);

  bool m_isLayoutInitialized;
  void showView(MenuViewType menuViewType);

  void CalculateButtonLayoutCoordinates(float topY, float buttonHeight, float targetedSpacingToButtonHeightRatio, float availableHeight
    , int totalButtons, float& startPosY, float& spacing);

protected:
  virtual void initialize(float dt);
  
public:
  MenuScene(GameContext* gameContext, bool showSplashScreen)   
    : BaseScene(gameContext, showSplashScreen)
    , m_menuViewType(HOME)
    , m_isLayoutInitialized(false)
    , m_challengeButtonPanel(NULL)
    , m_homeStoryMode(NULL)
    , m_homeArcade(NULL)
    , m_homeOptions(NULL)
    , m_homeHighscore(NULL)
    , m_arcadeEasy(NULL)
    , m_arcadeNormal(NULL)
    , m_arcadeHard(NULL)
    , m_arcadeBack(NULL)
    , m_header(NULL)
  {

  }
  ~MenuScene(){}

  virtual void onBackKeyPressed();

  virtual void showBaseMenu(CCObject* pSender);
  virtual void showStoryModeMenu(CCObject* pSender);
  virtual void showArcadeMenu(CCObject* pSender);
  virtual void showOptions(CCObject* pSender);
  virtual void showHighscore(CCObject* pSender);

  virtual void startArcadeNormalGameCallback(CCObject* pSender);
  virtual void startArcadeEasyGameCallback(CCObject* pSender);
  virtual void startArcadeHardGameCallback(CCObject* pSender);
};

#endif  // __MENU_SCENE_H__