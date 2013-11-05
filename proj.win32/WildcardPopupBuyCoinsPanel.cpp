#include "WildcardPopupBuyCoinsPanel.h"

WildcardPopupBuyCoinsPanel* WildcardPopupBuyCoinsPanel::create(GameContext* gameContext
    , CCSize size
    , SEL_CallFuncO goBackDelegate
    , CCNode* callbackTarget)
{
  WildcardPopupBuyCoinsPanel* wildcardPopupBuyCoinsPanel = new WildcardPopupBuyCoinsPanel(gameContext
    , size, goBackDelegate, callbackTarget);

  wildcardPopupBuyCoinsPanel->autorelease();

  return wildcardPopupBuyCoinsPanel;
}

void WildcardPopupBuyCoinsPanel::onEnter()
{
  CCNode::onEnter();

  if (!this->m_isLayoutInitialized)
  {    
    this->m_isLayoutInitialized = true;

    this->m_padding = m_pGameContext->getDefaultPadding();
    this->m_borderThickness = m_pGameContext->getDefaultBorderThickness();
    
    float verticalSpacing = (m_pGameContext->getFontHeightNormal() + m_padding)*this->m_pGameContext->getFontScale();
    float verticalSpacingLarge = (m_pGameContext->getFontHeightLarge() + m_padding*3)*this->m_pGameContext->getFontScale();
    
    float posY = 0;

    CCLabelBMFont* label = CCLabelBMFont::create("need more coins?\nGet them here...", m_pGameContext->getFontNormalPath().c_str());
    label->setScale(this->m_pGameContext->getFontScale());
    posY = this->m_padding + label->getContentSize().height/2*this->m_pGameContext->getFontScale();
    label->setPosition(0, posY );
    this->addChild(label);

    label = CCLabelBMFont::create("coming soon :)", m_pGameContext->getFontNormalPath().c_str());
    label->setScale(this->m_pGameContext->getFontScale());
    posY = - this->m_padding - label->getContentSize().height/2*this->m_pGameContext->getFontScale();
    label->setPosition(0, posY );
    this->addChild(label);
    
    this->setContentSize(CCSizeMake( m_size.width, -posY ));

    CCArray *pChildren = this->getChildren();
    if (pChildren && pChildren->count() > 0)
    {
      CCObject* pObject = NULL;
      posY = -posY/2;
      CCARRAY_FOREACH(pChildren, pObject)
      {
        CCNode* pNode = (CCNode*) pObject;
        pNode->setPositionY(round( pNode->getPositionY() + posY ));
      }
    } 
  }
}

void WildcardPopupBuyCoinsPanel::goBackCallback(CCObject* pSender)
{
  if(m_pTarget != 0 && this->m_fnpGoBackDelegate != 0)
    (m_pTarget->*this->m_fnpGoBackDelegate)(this);
}