#ifndef __OPTIONS_SCENE_H__
#define __OPTIONS_SCENE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"
#include "BaseScene.h"

class OptionsScene : public BaseScene
{
private:

  bool m_isLayoutInitialized;

  TextToggleButton* m_soundToggleButtonOn;
  TextToggleButton* m_soundToggleButtonOff;
  
  TextToggleButton* m_vibrateToggleButtonOn;
  TextToggleButton* m_vibrateToggleButtonOff;
    
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

  void onSoundToggleOnChanged(CCObject* pSender);
  void onSoundToggleOffChanged(CCObject* pSender);
  void onVibrateToggleOnChanged(CCObject* pSender);
  void onVibrateToggleOffChanged(CCObject* pSender);
  
  ccColor4F m_bgLight, m_bgDark;
  ccColor4F m_separatorColor;

public:
  OptionsScene(GameContext* gameContext)   
    : BaseScene(gameContext)
    , m_isLayoutInitialized(false)
  {

  }
  ~OptionsScene()
  {
  }
  virtual void onEnter();
  virtual void draw();
  virtual void onBackKeyPressed();
  virtual void showMenuCallback(CCObject* pSender);
};

#endif  // __OPTIONS_SCENE_H__