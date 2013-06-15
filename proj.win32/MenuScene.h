#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"
#include "BaseScene.h"

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

  ImageButton* m_storyModeNextPage;
  ImageButton* m_storyModePreviousPage;
  std::vector<ImageButton*> m_challengeButtons;

  int m_storyModePageIndex;
  void resetChallengeButtons(bool isVisible, bool areNavigationButtonsVisible);
  void resetHomeButtons(bool isVisible);
  void resetArcadeButtons(bool isVisible);

  bool m_isInitialized;
  void showView(MenuViewType menuViewType);

public:
  MenuScene(GameContext* gameContext)   
    : BaseScene(gameContext)
    , m_menuViewType(HOME)
    , m_isInitialized(false)
    , m_storyModePageIndex(0)
    , m_storyModeNextPage(NULL)
    , m_storyModePreviousPage(NULL)
    , m_homeStoryMode(NULL)
    , m_homeArcade(NULL)
    , m_homeOptions(NULL)
    , m_homeHighscore(NULL)
    , m_arcadeEasy(NULL)
    , m_arcadeNormal(NULL)
    , m_arcadeHard(NULL)
  {

  }

  virtual void onEnter();
  virtual void onBackKeyPressed();

  virtual void showStoryModeMenu(CCObject* pSender);
  virtual void showArcadeMenu(CCObject* pSender);
  virtual void showOptions(CCObject* pSender);
  virtual void showHighscore(CCObject* pSender);

  virtual void startArcadeNormalGameCallback(CCObject* pSender);
  virtual void startArcadeEasyGameCallback(CCObject* pSender);
  virtual void startArcadeHardGameCallback(CCObject* pSender);
  
  virtual void startChallenge(CCObject* pSender);
  virtual void nextStoryModePage(CCObject* pSender);
  virtual void previousStoryModePage(CCObject* pSender);
};

#endif  // __MENU_SCENE_H__