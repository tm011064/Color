#ifndef __HIGHSCORE_SCENE_H__
#define __HIGHSCORE_SCENE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"
#include "BaseScene.h"

class HighscoreScene : public BaseScene
{
private:

  bool m_isInitialized;
  float m_padding;

public:
  HighscoreScene(GameContext* gameContext)   
    : BaseScene(gameContext)
    , m_isInitialized(false)
  {

  }

  virtual void onEnter();
  virtual void onBackKeyPressed();
  virtual void showMenuCallback(CCObject* pSender);
};

#endif  // __HIGHSCORE_SCENE_H__