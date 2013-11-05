#include "WildcardPopupButtonPanel.h"

WildcardPopupButtonPanel* WildcardPopupButtonPanel::create(GameContext* gameContext
    , CCSize size
    , std::vector<WildcardButtonDefinition> wildcardButtonDefinitions)
{
  WildcardPopupButtonPanel* wildcardPopupButtonPanel = new WildcardPopupButtonPanel(gameContext
    , size, wildcardButtonDefinitions);

  wildcardPopupButtonPanel->autorelease();
  
  return wildcardPopupButtonPanel;
}

void WildcardPopupButtonPanel::onEnter()
{
  CCNode::onEnter();

  if (!this->m_isLayoutInitialized)
  {    
    this->m_isLayoutInitialized = true;

    CCSize wildCardButtonSize = CCSizeMake(round( m_size.width )
                                           , round( m_pGameContext->getFontHeightNormal() * this->m_pGameContext->getFontScale() * 2 + m_pGameContext->getDefaultPadding()*4));
    
    // TODO (Roman): do all the font scaling...

    ccColor4F fillColor = WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_OFF; //{ .0f, .0f, .0f, 1.0f };
    ccColor4F borderColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_scoreInfoRect.borderColor = borderColor;
    m_scoreInfoRect.fillColor = fillColor;

    m_scoreInfoLeftLabel = CCLabelBMFont::create("", m_pGameContext->getFontNormalPath().c_str());
    m_scoreInfoLeftLabel->setScale(this->m_pGameContext->getFontScale());
    this->addChild(m_scoreInfoLeftLabel);
    
    m_scoreInfoRightLabel = CCLabelBMFont::create("", m_pGameContext->getFontNormalPath().c_str());
    m_scoreInfoRightLabel->setScale(this->m_pGameContext->getFontScale());
    this->addChild(m_scoreInfoRightLabel);

    m_headerLabel = CCLabelBMFont::create("", m_pGameContext->getFontNormalPath().c_str());
    m_headerLabel->setScale(this->m_pGameContext->getFontScale());
    this->addChild(m_headerLabel);
    
    std::vector<WildcardButtonDefinition>::iterator it;
    WildcardButton* wildcardButton;
    for(it=this->m_wildcardButtonDefinitions.begin();it!=m_wildcardButtonDefinitions.end();++it)
    {
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
      this->addChild(wildcardButton);
      this->m_wildcardButtons.push_back(wildcardButton);
    }
  }
}

CCSize WildcardPopupButtonPanel::updateLayout(bool showHeader, std::string headerText
    , bool showScoreInfo, std::string scoreInfoLeft, std::string scoreInfoRight )
{
  float verticalSpacingLarge = m_pGameContext->getFontHeightLarge()*this->m_pGameContext->getFontScale() + m_pGameContext->getDefaultPadding()*3;
  float buttonMargin = m_pGameContext->getDefaultPadding()*4;
  float posY = 0;
    
  CCSize wildCardButtonSize = CCSizeMake(round( m_size.width )
                                         , round( m_pGameContext->getFontHeightNormal() *this->m_pGameContext->getFontScale()* 2 + m_pGameContext->getDefaultPadding()*4));
  
  this->m_showScoreInfo = showScoreInfo;
  if ( showScoreInfo )
  {
    this->m_scoreInfoRect.rightTop = ccp( m_size.width/2, posY );
    posY -= round( m_pGameContext->getFontHeightNormal()/2*this->m_pGameContext->getFontScale() + m_pGameContext->getDefaultPadding() );
    m_scoreInfoLeftLabel->setString(scoreInfoLeft.c_str());
    m_scoreInfoLeftLabel->setPosition(-m_size.width/2 + m_scoreInfoLeftLabel->getContentSize().width/2*this->m_pGameContext->getFontScale() + m_pGameContext->getDefaultPadding()*4, posY);
    m_scoreInfoRightLabel->setString(scoreInfoRight.c_str());
    m_scoreInfoRightLabel->setPosition(m_size.width/2 - m_scoreInfoRightLabel->getContentSize().width/2*this->m_pGameContext->getFontScale() - m_pGameContext->getDefaultPadding()*4, posY);
    posY -= round( m_pGameContext->getFontHeightNormal()/2*this->m_pGameContext->getFontScale() + m_pGameContext->getDefaultPadding() );
    this->m_scoreInfoRect.leftBottom = ccp( -m_size.width/2, posY );
  }

  this->m_showHeader = showHeader;
  if ( showHeader )
  {
    if ( showScoreInfo )
      posY -= round( buttonMargin*2 );

    posY -= round( m_pGameContext->getFontHeightNormal()/2*this->m_pGameContext->getFontScale() );
    m_headerLabel->setString(headerText.c_str());
    m_headerLabel->setPosition(0, posY);
    posY -= round( m_pGameContext->getFontHeightNormal()/2*this->m_pGameContext->getFontScale() );
  }

  if ( showScoreInfo || showHeader )
  {
    posY -= round( buttonMargin*2 );
  }
  
  std::vector<WildcardButton*>::iterator it;
  posY += round( (buttonMargin + wildCardButtonSize.height/2) );
  for(it=this->m_wildcardButtons.begin();it!=m_wildcardButtons.end();++it)
  {
    posY -= round( (buttonMargin + wildCardButtonSize.height) );
    (*it)->setPosition(0, posY);
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

  this->m_scoreInfoRect.leftBottom.y += posY;
  this->m_scoreInfoRect.rightTop.y += posY;

  return this->getContentSize();
}

void WildcardPopupButtonPanel::show()
{ 
  BaseNode::show();

  m_scoreInfoLeftLabel->setVisible( m_showScoreInfo );
  m_scoreInfoRightLabel->setVisible( m_showScoreInfo );
  m_headerLabel->setVisible( m_showHeader );
}

void WildcardPopupButtonPanel::draw()
{ 
  if ( m_showScoreInfo )
  {    
    ccDrawSolidRect(m_scoreInfoRect.leftBottom, m_scoreInfoRect.rightTop, m_scoreInfoRect.borderColor);
    ccDrawSolidRect( ccp( m_scoreInfoRect.leftBottom.x + 1, m_scoreInfoRect.leftBottom.y + 1 )
      , ccp( m_scoreInfoRect.rightTop.x - 1, m_scoreInfoRect.rightTop.y - 1 )
      , m_scoreInfoRect.fillColor);
  }
}
