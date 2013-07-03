#ifndef __HIGHSCORE_SCENE_H__
#define __HIGHSCORE_SCENE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"
#include "BaseScene.h"

class HighscoreScene : public BaseScene
{
private:

  bool m_isLayoutInitialized;
  float m_padding;

  
  CCPoint m_panelRectLeftBottom;
  CCPoint m_panelRectRightTop;

  CCPoint m_panelRectInnerLeftBottom;
  CCPoint m_panelRectInnerRightTop;
  
  CCPoint m_visibleRectLeftBottom;
  CCPoint m_visibleRectRightTop;
  
  CCPoint m_panelRectLeftTop;
  CCPoint m_panelRectRightBottom;

  CCPoint m_separatorTopRight;
  CCPoint m_separatorBottomRight;

  float m_textIndentLeft;
  float m_textIndentRight;
  
  ccColor4F m_bgLight, m_bgDark;
  ccColor4F m_separatorColor;

public:
  HighscoreScene(GameContext* gameContext)   
    : BaseScene(gameContext)
    , m_isLayoutInitialized(false)
  {

  }

  virtual void onEnter();
  virtual void draw();
  virtual void onBackKeyPressed();
  virtual void showMenuCallback(CCObject* pSender);
};

#endif  // __HIGHSCORE_SCENE_H__