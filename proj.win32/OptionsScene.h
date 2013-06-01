#ifndef __OPTIONS_SCENE_H__
#define __OPTIONS_SCENE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"
#include "BaseScene.h"

class OptionsScene : public BaseScene
{
private:

  bool m_isInitialized;

  TextToggleButton* m_soundToggleButtonOn;
  TextToggleButton* m_soundToggleButtonOff;
  
  TextToggleButton* m_vibrateToggleButtonOn;
  TextToggleButton* m_vibrateToggleButtonOff;
    
  void onSoundToggleOnChanged(CCObject* pSender);
  void onSoundToggleOffChanged(CCObject* pSender);
  void onVibrateToggleOnChanged(CCObject* pSender);
  void onVibrateToggleOffChanged(CCObject* pSender);

public:
  OptionsScene(GameContext* gameContext)   
    : BaseScene(gameContext)
    , m_isInitialized(false)
  {

  }

  virtual void onEnter();
  virtual void onBackKeyPressed();
  virtual void showMenuCallback(CCObject* pSender);
};

#endif  // __OPTIONS_SCENE_H__