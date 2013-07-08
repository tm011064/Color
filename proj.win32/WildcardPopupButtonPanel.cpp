#include "WildcardPopupButtonPanel.h"

void WildcardPopupButtonPanel::onEnter()
{
  CCNode::onEnter();

  if (!this->m_isLayoutInitialized)
  {    
    this->m_isLayoutInitialized = true;

    this->m_padding = m_pGameContext->getDefaultPadding();
    this->m_borderThickness = m_pGameContext->getDefaultBorderThickness();

    float verticalSpacing = m_pGameContext->getFontHeightNormal() + m_padding;
    float verticalSpacingLarge = m_pGameContext->getFontHeightLarge() + m_padding*3;

    float posY = 0;
    CCLabelBMFont* label = CCLabelBMFont::create("use coins to buy cheats", m_pGameContext->getFontNormalPath().c_str());
    posY = -label->getContentSize().height/2;
    label->setPosition(0, posY );
    this->addChild(label);

    CCSize wildCardButtonSize = CCSizeMake(round( m_size.width )
                                           , round( m_pGameContext->getFontHeightNormal() * 2 + m_padding*4));
    posY -= round( (verticalSpacingLarge/2 + verticalSpacing/2 + this->m_padding + wildCardButtonSize.height/2) );
    
    std::stringstream ss;
    ss << COINS_COST_REPLAY_SEQUENCE;
    
    WildcardButton* wildcardButton = WildcardButton::create(
      WILDCARD_BUTTON_BORDER_COLOR_ON, WILDCARD_BUTTON_BORDER_COLOR_OFF
      , WILDCARD_BUTTON_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_BACKGROUND_COLOR_OFF
      , WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "REPLAY\nSEQUENCE"
      , ss.str()
      , wildCardButtonSize
      , m_borderThickness
      , m_pGameContext
      , callfuncO_selector(WildcardPopupButtonPanel::replaySequenceCallback)
      , this);    
    wildcardButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    wildcardButton->setPosition(0, posY);
    this->addChild(wildcardButton);
    
    ss.str(std::string());
    ss << COINS_COST_SHOW_NEXT_ITEM;

    posY -= round( (this->m_padding*4 + wildCardButtonSize.height) );
    wildcardButton = WildcardButton::create(
      WILDCARD_BUTTON_BORDER_COLOR_ON, WILDCARD_BUTTON_BORDER_COLOR_OFF
      , WILDCARD_BUTTON_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_BACKGROUND_COLOR_OFF
      , WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "SHOW NEXT"
      , ss.str()
      , wildCardButtonSize
      , m_pGameContext->getDefaultBorderThickness()
      , m_pGameContext
      , callfuncO_selector(WildcardPopupButtonPanel::showNextSequenceItemCallback)
      , this);    
    wildcardButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    wildcardButton->setPosition(0, posY);
    this->addChild(wildcardButton);
    
    ss.str(std::string());
    ss << COINS_COST_SHOW_REMAINING;
    posY -= round( (this->m_padding*4 + wildCardButtonSize.height) );
    wildcardButton = WildcardButton::create(
      WILDCARD_BUTTON_BORDER_COLOR_ON, WILDCARD_BUTTON_BORDER_COLOR_OFF
      , WILDCARD_BUTTON_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_BACKGROUND_COLOR_OFF
      , WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "REPLAY\nREMAINING"
      , ss.str()
      , wildCardButtonSize
      , m_pGameContext->getDefaultBorderThickness()
      , m_pGameContext
      , callfuncO_selector(WildcardPopupButtonPanel::replayFromCurrentCallback)
      , this);    
    wildcardButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    wildcardButton->setPosition(0, posY);
    this->addChild(wildcardButton);
        
    this->setContentSize(CCSizeMake( m_size.width, -posY ));

    CCArray *pChildren = this->getChildren();
    if (pChildren && pChildren->count() > 0)
    {
      CCObject* pObject = NULL;
      posY = -posY/2;
      CCNode* pNode;
      CCARRAY_FOREACH(pChildren, pObject)
      {
        pNode = (CCNode*) pObject;
        pNode->setPositionY(round( pNode->getPositionY() + posY ));
      }
    } 
  }
}

void WildcardPopupButtonPanel::replaySequenceCallback(CCObject* pSender)
{
  int totalCoins = this->m_pGameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_REPLAY_SEQUENCE)
  {
    // callback
    if(m_pTarget != 0 && this->m_fnpReplaySequenceCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpReplaySequenceCallbackDelegate)(this);
  }
  else
  {
    // callback
    if(m_pTarget != 0 && this->m_fnpMoreCoinsCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpMoreCoinsCallbackDelegate)(this);
  }
}
void WildcardPopupButtonPanel::showNextSequenceItemCallback(CCObject* pSender)
{
  int totalCoins = this->m_pGameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_SHOW_NEXT_ITEM)
  {
    // callback
    if(m_pTarget != 0 && this->m_fnpShowNextSequenceItemCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpShowNextSequenceItemCallbackDelegate)(this);
  }
  else
  {
    // callback
    if(m_pTarget != 0 && this->m_fnpMoreCoinsCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpMoreCoinsCallbackDelegate)(this);
  }
}
void WildcardPopupButtonPanel::replayFromCurrentCallback(CCObject* pSender)
{
  int totalCoins = this->m_pGameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_SHOW_REMAINING)
  {
    // callback
    if(m_pTarget != 0 && this->m_fnpSaveTryCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpSaveTryCallbackDelegate)(this);
  }
  else
  {
    // callback
    if(m_pTarget != 0 && this->m_fnpMoreCoinsCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpMoreCoinsCallbackDelegate)(this);
  }
}