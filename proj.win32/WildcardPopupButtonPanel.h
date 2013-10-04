#ifndef __WILDCARD_POPUP_BUTTON_PANEL_H__
#define __WILDCARD_POPUP_BUTTON_PANEL_H__

#include "GameEngineIncludes.h"

using namespace cocos2d;

typedef struct 
{
  std::string text;
  unsigned int totalCoins;
  SEL_CallFuncO callback;
  CCNode* callbackTarget;
} WildcardButtonDefinition;

class WildcardPopupButtonPanel : public BaseNode
{  
private:
  
  bool m_isLayoutInitialized;
  bool m_showScoreInfo;
  bool m_showHeader;

  CCLabelBMFont* m_headerLabel;
  CCLabelBMFont* m_scoreInfoLeftLabel;
  CCLabelBMFont* m_scoreInfoRightLabel;

  ColoredRect m_scoreInfoRect;

  GameContext* m_pGameContext; 
  CCSize m_size;

  void replaySequenceCallback(CCObject* pSender);
  void showNextSequenceItemCallback(CCObject* pSender);
  void replayFromCurrentCallback(CCObject* pSender); 

  std::vector<WildcardButton*> m_wildcardButtons;
  std::vector<WildcardButtonDefinition> m_wildcardButtonDefinitions;
  std::string m_headerText;

protected:
  
  WildcardPopupButtonPanel(GameContext* gameContext
    , CCSize size
    , std::vector<WildcardButtonDefinition> wildcardButtonDefinitions)
    : m_pGameContext(gameContext)
    , m_size(size)
    , m_isLayoutInitialized(false)
    , m_wildcardButtonDefinitions(wildcardButtonDefinitions)
    , m_headerLabel(NULL)
    , m_scoreInfoLeftLabel(NULL)
    , m_scoreInfoRightLabel(NULL)
    , m_showScoreInfo(false)
    , m_showHeader(false)
  { }

public:
  static WildcardPopupButtonPanel* create(GameContext* gameContext
    , CCSize size
    , std::vector<WildcardButtonDefinition> wildcardButtonDefinitions);

  ~WildcardPopupButtonPanel() 
  { 
    this->m_pGameContext = NULL;
  }
  
  CCSize updateLayout(bool showHeader, std::string headerText
    , bool showScoreInfo, std::string scoreInfoLeft, std::string scoreInfoRight);

  virtual void show();
  virtual void draw();

  virtual void onEnter();
};

#endif  // __WILDCARD_POPUP_BUTTON_PANEL_H__