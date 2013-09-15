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
  float m_padding;
  float m_borderThickness;

  GameContext* m_pGameContext; 
  CCSize m_size;

  void replaySequenceCallback(CCObject* pSender);
  void showNextSequenceItemCallback(CCObject* pSender);
  void replayFromCurrentCallback(CCObject* pSender); 

  std::vector<WildcardButtonDefinition> m_wildcardButtonDefinitions;
  std::string m_headerText;

protected:
  
  WildcardPopupButtonPanel(GameContext* gameContext
    , CCSize size
    , std::vector<WildcardButtonDefinition> wildcardButtonDefinitions
    , std::string headerText)
    : m_pGameContext(gameContext)
    , m_size(size)
    , m_isLayoutInitialized(false)
    , m_wildcardButtonDefinitions(wildcardButtonDefinitions)
    , m_headerText(headerText)
  { }

public:
  static WildcardPopupButtonPanel* create(GameContext* gameContext
    , CCSize size
    , std::vector<WildcardButtonDefinition> wildcardButtonDefinitions
    , std::string headerText);

  ~WildcardPopupButtonPanel() 
  { 
    this->m_pGameContext = NULL;
  }
  
  virtual void onEnter();
};

#endif  // __WILDCARD_POPUP_BUTTON_PANEL_H__