  #include "WildcardPopup.h"

void WildcardPopup::onEnter()
{
  ModalControl::onEnter();

  if (!this->m_isLayoutInitialized)
  {    
    CCPoint center = VisibleRect::center();
        
    CCRect visibleRect = VisibleRect::getVisibleRect();
    m_visibleRectLeftBottom = VisibleRect::leftBottom();
    m_visibleRectRightTop = VisibleRect::rightTop();
                
    this->m_padding = m_pGameContext->getDefaultPadding();
    this->m_borderThickness = m_pGameContext->getDefaultBorderThickness();

    float verticalSpacing = m_pGameContext->getFontHeightNormal() + m_padding;
    float verticalSpacingLarge = m_pGameContext->getFontHeightLarge() + m_padding*3;
            
    m_dialogRectLeftTop = ccp ( 0, m_visibleRectRightTop.y * .825);
    //m_dialogRectLeftBottom = ccp ( 0, m_visibleRectRightTop.y * .26 );
    m_dialogRectRightTop = ccp ( m_visibleRectRightTop.x, m_dialogRectLeftTop.y);
    //m_dialogRectRightBottom = ccp ( m_visibleRectRightTop.x, m_dialogRectLeftBottom.y);
    
    m_separatorTopRight = ccp ( m_visibleRectRightTop.x, m_dialogRectRightTop.y + m_borderThickness);
    //m_separatorBottomRight = ccp ( m_visibleRectRightTop.x, m_dialogRectRightBottom.y - m_borderThickness);

    // now we have the border thickness and padding, so we can set the boundaries 
    float indentLeft = m_visibleRectLeftBottom.x + (visibleRect.size.width * .1);
    float indentRight = m_visibleRectLeftBottom.x + (visibleRect.size.width * .9);
    m_dialogRectInnerRightTop = ccp( indentRight - this->m_borderThickness, m_dialogRectRightTop.y - this->m_borderThickness );

    this->m_textIndentLeft = indentLeft + this->m_borderThickness + m_padding * 3;
    this->m_textIndentRight = m_dialogRectInnerRightTop.x - m_padding * 3;

    float posY = round( m_dialogRectInnerRightTop.y + verticalSpacing/2 + m_padding*2 );
    CCLabelBMFont* label = CCLabelBMFont::create("coins available", m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2, posY );
    this->addChild(label);
       
    m_coinsLabel = CCLabelBMFont::create("NA", m_pGameContext->getFontNormalPath().c_str());
    m_coinsLabel->setPosition(ccp(this->m_textIndentRight - m_coinsLabel->getContentSize().width/2, posY));
    this->addChild(m_coinsLabel);
    
    m_availableCoinsCoin = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("coin_small"));
    m_availableCoinsCoin->setScale(this->m_pGameContext->getFontHeightNormal() / m_availableCoinsCoin->getContentSize().height * 1.5);
    m_availableCoinsCoin->setPosition(ccpRounded(m_coinsLabel->getPositionX() - m_coinsLabel->getContentSize().width/2 - m_padding, posY));
    this->addChild(m_availableCoinsCoin);
    
    this->m_wildcardPopupButtonPanel = new WildcardPopupButtonPanel(
      this->m_pGameContext
      , CCSizeMake( this->m_textIndentRight - this->m_textIndentLeft, 0 )
      , callfuncO_selector(WildcardPopup::replaySequenceCallback)
      , callfuncO_selector(WildcardPopup::showNextSequenceItemCallback)
      , callfuncO_selector(WildcardPopup::replayFromCurrentCallback)
      , callfuncO_selector(WildcardPopup::moreCoinsCallback)
      , this);
    this->m_wildcardPopupButtonPanel->autorelease();
    this->addChild(this->m_wildcardPopupButtonPanel);
    this->m_wildcardPopupButtonPanel->hide();

    this->m_wildcardPopupBuyCoinsPanel = new WildcardPopupBuyCoinsPanel(
      this->m_pGameContext
      , CCSizeMake( this->m_textIndentRight - this->m_textIndentLeft, 0 )
      , callfuncO_selector(WildcardPopup::wildcardPanelCallback)
      , this);
    this->m_wildcardPopupBuyCoinsPanel->autorelease();
    this->addChild(this->m_wildcardPopupBuyCoinsPanel);
    this->m_wildcardPopupBuyCoinsPanel->hide();

    CCSize wildcardPopupButtonPanelSize = this->m_wildcardPopupButtonPanel->getContentSize();
    posY = m_dialogRectLeftTop.y - wildcardPopupButtonPanelSize.height/2 - verticalSpacing;

    this->m_wildcardPopupButtonPanel->setPosition(center.x, posY);
    this->m_wildcardPopupBuyCoinsPanel->setPosition(center.x, posY);
    
    TextButton* textButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "back"
      , m_pGameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_pGameContext
      , callfuncO_selector(WildcardPopup::closeCallback)
      , this);
    textButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    posY -= round( (verticalSpacing*2 + textButton->getSize().height/2 + wildcardPopupButtonPanelSize.height/2) );
    textButton->setPosition(this->m_textIndentLeft + textButton->getSize().width/2, posY);
    this->addChild(textButton);
    
    m_moreCoinsTextButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "+ coins"
      , m_pGameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_pGameContext
      , callfuncO_selector(WildcardPopup::moreCoinsCallback)
      , this);
    m_moreCoinsTextButton->setEnabled(false);
    m_moreCoinsTextButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    m_moreCoinsTextButton->setPosition(this->m_textIndentRight - m_moreCoinsTextButton->getSize().width/2, posY);
    this->addChild(m_moreCoinsTextButton);
        
    m_dialogRectLeftBottom = ccp ( 0, posY - m_moreCoinsTextButton->getSize().height/2 - verticalSpacing );
    m_dialogRectRightBottom = ccp ( m_visibleRectRightTop.x, m_dialogRectLeftBottom.y);
    m_separatorBottomRight = ccp ( m_visibleRectRightTop.x, m_dialogRectRightBottom.y - m_borderThickness);
    
    this->m_wildcardPopupBuyCoinsPanel->hide();
    this->m_wildcardPopupButtonPanel->show();
    this->m_moreCoinsTextButton->setVisible(true);

    m_bgLight.a = .6f; 
    m_bgLight.r = 0; 
    m_bgLight.g = 0; 
    m_bgLight.b = 0;
    m_bgDark.a = .8f; 
    m_bgDark.r = 0; 
    m_bgDark.g = 0; 
    m_bgDark.b = 0;
    m_separatorColor.a = 1; 
    m_separatorColor.r = 1; 
    m_separatorColor.g = 1; 
    m_separatorColor.b = 1; 
  }
}

void WildcardPopup::show()
{
  BaseNode::show();

  // basenode show makes everything visible, so hide the buy coin panel...
  this->m_wildcardPopupBuyCoinsPanel->hide();
  this->m_wildcardPopupButtonPanel->show();
}

void WildcardPopup::refresh()
{
  char str[10];
  sprintf(str, "%i", m_pGameContext->getTotalCoins());
  m_coinsLabel->setString(str);  
  m_coinsLabel->setPositionX(round(m_textIndentRight - m_padding*2 - m_coinsLabel->getContentSize().width/2));
  m_availableCoinsCoin->setPositionX(round(m_coinsLabel->getPositionX() - m_coinsLabel->getContentSize().width/2 
                                                                        - m_padding
                                                                        - m_availableCoinsCoin->getContentSize().width/2));
}

void WildcardPopup::draw()
{ 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  ccDrawSolidRect(m_dialogRectLeftTop, m_visibleRectRightTop, m_bgLight);
  ccDrawSolidRect(m_dialogRectLeftBottom, m_dialogRectRightTop, m_bgDark);
  ccDrawSolidRect(m_visibleRectLeftBottom, m_dialogRectRightBottom, m_bgLight);

  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  ccDrawSolidRect(m_dialogRectLeftTop, m_separatorTopRight, m_separatorColor);
  ccDrawSolidRect(m_dialogRectLeftBottom, m_separatorBottomRight, m_separatorColor);
}

void WildcardPopup::replaySequenceCallback(CCObject* pSender)
{
  int totalCoins = this->m_pGameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_REPLAY_SEQUENCE)
  {
    totalCoins -= COINS_COST_REPLAY_SEQUENCE;
    this->m_pGameContext->setTotalCoins(totalCoins);

    char str[10];
    sprintf(str, "%i", totalCoins);
    m_coinsLabel->setString(str);

    // callback
    if(m_pTarget != 0 && this->m_fnpReplaySequenceCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpReplaySequenceCallbackDelegate)(this);
  }
}
void WildcardPopup::showNextSequenceItemCallback(CCObject* pSender)
{
  int totalCoins = this->m_pGameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_SHOW_NEXT_ITEM)
  {
    totalCoins -= COINS_COST_SHOW_NEXT_ITEM;
    this->m_pGameContext->setTotalCoins(totalCoins);
    
    char str[10];
    sprintf(str, "%i", totalCoins);
    m_coinsLabel->setString(str);

    // callback
    if(m_pTarget != 0 && this->m_fnpShowNextSequenceItemCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpShowNextSequenceItemCallbackDelegate)(this);
  }
}
void WildcardPopup::replayFromCurrentCallback(CCObject* pSender)
{
  int totalCoins = this->m_pGameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_SHOW_REMAINING)
  {
    totalCoins -= COINS_COST_SHOW_REMAINING;
    this->m_pGameContext->setTotalCoins(totalCoins);
    
    char str[10];
    sprintf(str, "%i", totalCoins);
    m_coinsLabel->setString(str);

    // callback
    if(m_pTarget != 0 && this->m_fnpSaveTryCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpSaveTryCallbackDelegate)(this);
  }
}

void WildcardPopup::activatePanel(WildcardPopupPanel wildcardPopupPanel)
{
  CCActionInterval* moveLeft = CCMoveBy::create(.15f, ccp(-(VisibleRect::getVisibleRect().size.width),0));
  CCActionInterval* moveRight = CCMoveBy::create(.15f, ccp((VisibleRect::getVisibleRect().size.width),0));
  
  CCPoint center = VisibleRect::center();
  CCRect visibleRect = VisibleRect::getVisibleRect();
  float easeRate = .5f;
  float posLeft = center.x - visibleRect.size.width;
  float posRight = center.x + visibleRect.size.width;
    
  this->m_wildcardPopupBuyCoinsPanel->show();
  this->m_wildcardPopupButtonPanel->show();

  switch (wildcardPopupPanel)
  {
  case WILDCARD_BUTTONS:
    this->m_wildcardPopupBuyCoinsPanel->setPositionX(center.x);
    this->m_wildcardPopupBuyCoinsPanel->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));

    this->m_wildcardPopupButtonPanel->setPositionX(posLeft);
    this->m_wildcardPopupButtonPanel->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      
    this->m_moreCoinsTextButton->setVisible(true);
    break;

  case WILDCARD_MORE_COINS:
    this->m_wildcardPopupBuyCoinsPanel->setPositionX(posRight);
    this->m_wildcardPopupBuyCoinsPanel->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));

    this->m_wildcardPopupButtonPanel->setPositionX(center.x);
    this->m_wildcardPopupButtonPanel->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
  
    this->m_moreCoinsTextButton->setVisible(false);
    break;
  }
  
  this->m_activeWildcardPopupPanel = wildcardPopupPanel;
}

void WildcardPopup::moreCoinsCallback(CCObject* pSender)
{
  activatePanel(WILDCARD_MORE_COINS);
}
void WildcardPopup::wildcardPanelCallback(CCObject* pSender)
{    
  activatePanel(WILDCARD_BUTTONS);
}

void WildcardPopup::closeCallback(CCObject* pSender)
{
  if (this->m_activeWildcardPopupPanel == WILDCARD_MORE_COINS)
  {
    activatePanel(WILDCARD_BUTTONS);
  }
  else
  {
    // callback
    if(m_pTarget != 0 && this->m_fnpCloseCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpCloseCallbackDelegate)(this);
  }
}