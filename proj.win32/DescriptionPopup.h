#ifndef __DESCRIPTION_POPUP_H__
#define __DESCRIPTION_POPUP_H__

#include "ModalControl.h"

using namespace cocos2d;

class DescriptionPopup : public ModalControl
{  
private:
 
  bool m_isLayoutInitialized;
    
  GameContext* m_pGameContext; 
  SEL_CallFuncO m_fnpCloseCallbackDelegate;  
  CCNode *m_pTarget;
    
  CCPoint m_descriptionBoxLeftBottom;
  CCPoint m_descriptionBoxRightTop;
  CCPoint m_scoreBoxLeftBottom;
  CCPoint m_scoreBoxRightTop;
  CCPoint m_headerBoxLeftBottom;
  CCPoint m_headerBoxRightTop;

  CCPoint m_borderLeftRightTop;
  CCPoint m_borderBottomRightTop;
  CCPoint m_borderRightLeftBottom;
  CCPoint m_borderTopLeftBottom;

  CCPoint m_lowerSeparatorRightTop;
  CCPoint m_upperSeparatorRightTop;

  TextButton* m_playButton;

  ChallengePointScoreDefinition m_challengePointScoreDefinition;

  void playCallback(CCObject* pSender);

  float m_padding;

  ccColor4F m_targetBackgroundColor;
  ccColor4F m_descriptionBackgroundColor;

protected:
  DescriptionPopup(GameContext* gameContext
    , SEL_CallFuncO closeCallbackDelegate
    , CCNode* callbackTarget, ChallengePointScoreDefinition challengePointScoreDefinition)
    : m_pGameContext(gameContext)
    , m_isLayoutInitialized(false)
    , m_fnpCloseCallbackDelegate(closeCallbackDelegate)
    , m_pTarget(callbackTarget)
    , m_playButton(NULL)
    , m_challengePointScoreDefinition(challengePointScoreDefinition)
  { 

  }

public:
  static DescriptionPopup* create(GameContext* gameContext
    , SEL_CallFuncO closeCallbackDelegate
    , CCNode* callbackTarget, ChallengePointScoreDefinition challengePointScoreDefinition);
  ~DescriptionPopup() { }

  void setEnablePlayButton(bool isEnabled);
  virtual void onEnter();
  virtual void draw();
};
#endif  // __DESCRIPTION_POPUP_H__