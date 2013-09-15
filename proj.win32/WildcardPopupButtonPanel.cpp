#include "WildcardPopupButtonPanel.h"

WildcardPopupButtonPanel* WildcardPopupButtonPanel::create(GameContext* gameContext
    , CCSize size
    , std::vector<WildcardButtonDefinition> wildcardButtonDefinitions
    , std::string headerText)
{
  WildcardPopupButtonPanel* wildcardPopupButtonPanel = new WildcardPopupButtonPanel(gameContext
    , size, wildcardButtonDefinitions, headerText);

  wildcardPopupButtonPanel->autorelease();
  
  return wildcardPopupButtonPanel;
}

void WildcardPopupButtonPanel::onEnter()
{
  CCNode::onEnter();

  if (!this->m_isLayoutInitialized)
  {    
    this->m_isLayoutInitialized = true;

    this->m_padding = m_pGameContext->getDefaultPadding();
    this->m_borderThickness = m_pGameContext->getDefaultBorderThickness();

    float verticalSpacingLarge = m_pGameContext->getFontHeightLarge() + m_padding*3;
    float buttonMargin = this->m_padding*4;
    float posY = 0;
    
    CCSize wildCardButtonSize = CCSizeMake(round( m_size.width )
                                           , round( m_pGameContext->getFontHeightNormal() * 2 + m_padding*4));

    if (m_headerText.length() > 0)
    {
      CCLabelBMFont* label = CCLabelBMFont::create(m_headerText.c_str(), m_pGameContext->getFontNormalPath().c_str());
      posY = -m_pGameContext->getFontHeightNormal()/2;
      label->setPosition(0, posY );
      this->addChild(label);

      posY -= round( (m_pGameContext->getFontHeightNormal()/2 + wildCardButtonSize.height/2 + buttonMargin*2 ) );
    }

    std::vector<WildcardButtonDefinition>::iterator it;
    posY += round( (buttonMargin + wildCardButtonSize.height) );
    WildcardButton* wildcardButton;
    for(it=this->m_wildcardButtonDefinitions.begin();it!=m_wildcardButtonDefinitions.end();++it)
    {
      posY -= round( (buttonMargin + wildCardButtonSize.height) );
      wildcardButton = WildcardButton::create(
        WILDCARD_BUTTON_BORDER_COLOR_ON, WILDCARD_BUTTON_BORDER_COLOR_OFF
        , WILDCARD_BUTTON_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_BACKGROUND_COLOR_OFF
        , WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_OFF
        , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
        , it->text
        , UtilityHelper::convertToString(it->totalCoins)
        , wildCardButtonSize
        , m_pGameContext->getDefaultBorderThickness()
        , m_pGameContext
        , it->callback
        , it->callbackTarget);    
      wildcardButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
      wildcardButton->setPosition(0, posY);
      this->addChild(wildcardButton);
    }
    posY -= wildCardButtonSize.height/2;
    
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