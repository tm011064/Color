#include "WildcardPopupBuyCoinsPanel.h"

void WildcardPopupBuyCoinsPanel::onEnter()
{
  CCNode::onEnter();

  if (!this->m_isLayoutInitialized)
  {    
    this->m_isLayoutInitialized = true;

    this->m_padding = m_gameContext->getDefaultPadding();
    this->m_borderThickness = m_gameContext->getDefaultBorderThickness();

    float verticalSpacing = m_gameContext->getFontHeightNormal() + m_padding;
    float verticalSpacingLarge = m_gameContext->getFontHeightLarge() + m_padding*3;

    float posY = 0;

    CCLabelBMFont* label = CCLabelBMFont::create("need more coins? get them here...", m_gameContext->getFontNormalPath().c_str());
    posY = this->m_padding + label->getContentSize().height/2;
    label->setPosition(0, posY );
    this->addChild(label);

    label = CCLabelBMFont::create("coming soon :)", m_gameContext->getFontNormalPath().c_str());
    posY = - this->m_padding - label->getContentSize().height/2;
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