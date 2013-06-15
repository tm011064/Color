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
                
    this->m_padding = m_gameContext->getDefaultPadding();
    this->m_borderThickness = m_gameContext->getDefaultBorderThickness();

    float verticalSpacing = m_gameContext->getFontHeightNormal() + m_padding;
    float verticalSpacingLarge = m_gameContext->getFontHeightLarge() + m_padding*3;
            
    m_dialogRectLeftTop = ccp ( 0, m_visibleRectRightTop.y * .825);
    m_dialogRectLeftBottom = ccp ( 0, m_visibleRectRightTop.y * .26 );
    m_dialogRectRightTop = ccp ( m_visibleRectRightTop.x, m_dialogRectLeftTop.y);
    m_dialogRectRightBottom = ccp ( m_visibleRectRightTop.x, m_dialogRectLeftBottom.y);
    
    m_separatorTopRight = ccp ( m_visibleRectRightTop.x, m_dialogRectRightTop.y + m_borderThickness);
    m_separatorBottomRight = ccp ( m_visibleRectRightTop.x, m_dialogRectRightBottom.y - m_borderThickness);

    // now we have the border thickness and padding, so we can set the boundaries 
    float indentLeft = m_visibleRectLeftBottom.x + (visibleRect.size.width * .1);
    float indentRight = m_visibleRectLeftBottom.x + (visibleRect.size.width * .9);
    m_dialogRectInnerLeftBottom = ccp( indentLeft + this->m_borderThickness, m_dialogRectLeftBottom.y + this->m_borderThickness );
    m_dialogRectInnerRightTop = ccp( indentRight - this->m_borderThickness, m_dialogRectRightTop.y - this->m_borderThickness );

    this->m_textIndentLeft = m_dialogRectInnerLeftBottom.x + m_padding * 3;
    this->m_textIndentRight = m_dialogRectInnerRightTop.x - m_padding * 3;

    float posY = round( m_dialogRectInnerRightTop.y + verticalSpacing/2 + m_padding*2 );
    CCLabelBMFont* label = CCLabelBMFont::create("coins available", m_gameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2, posY );
    this->addChild(label);
       
    m_coinsLabel = CCLabelBMFont::create("NA", m_gameContext->getFontNormalPath().c_str());
    m_coinsLabel->setPosition(ccp(this->m_textIndentRight - m_coinsLabel->getContentSize().width/2, posY));
    this->addChild(m_coinsLabel);
    
    m_availableCoinsCoin = CCSprite::createWithSpriteFrame(m_gameContext->getImageMap()->getTile(11));
    m_availableCoinsCoin->setPosition(ccpRounded(m_coinsLabel->getPositionX() - m_coinsLabel->getContentSize().width/2 - m_padding, posY));
    this->addChild(m_availableCoinsCoin);

    posY = round( m_dialogRectInnerRightTop.y - (verticalSpacingLarge/2 + verticalSpacing/2 + this->m_padding) );
    label = CCLabelBMFont::create("use coins to buy cheats", m_gameContext->getFontNormalPath().c_str());
    label->setPosition(center.x, posY );
    this->addChild(label);

    CCSize wildCardButtonSize = CCSizeMake(round( m_textIndentRight - m_textIndentLeft)
                                           , round( m_gameContext->getFontHeightNormal() * 2 + m_padding*4));
    posY -= round( (verticalSpacingLarge/2 + verticalSpacing/2 + this->m_padding + wildCardButtonSize.height/2) );
    
    WildcardButton* wildcardButton = new WildcardButton(
      WILDCARD_BUTTON_BORDER_COLOR_ON, WILDCARD_BUTTON_BORDER_COLOR_OFF
      , WILDCARD_BUTTON_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_BACKGROUND_COLOR_OFF
      , WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "REPLAY\nSEQUENCE"
      , "25"
      , wildCardButtonSize
      , m_gameContext->getDefaultBorderThickness()
      , m_gameContext
      , callfuncO_selector(WildcardPopup::replaySequenceCallback)
      , this);
    wildcardButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    wildcardButton->setPosition(center.x, posY);
    this->addChild(wildcardButton);

    posY -= round( (this->m_padding*4 + wildCardButtonSize.height) );
    wildcardButton = new WildcardButton(
      WILDCARD_BUTTON_BORDER_COLOR_ON, WILDCARD_BUTTON_BORDER_COLOR_OFF
      , WILDCARD_BUTTON_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_BACKGROUND_COLOR_OFF
      , WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "SHOW NEXT"
      , "50"
      , wildCardButtonSize
      , m_gameContext->getDefaultBorderThickness()
      , m_gameContext
      , callfuncO_selector(WildcardPopup::showNextSequenceItemCallback)
      , this);
    wildcardButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    wildcardButton->setPosition(center.x, posY);
    this->addChild(wildcardButton);

    posY -= round( (this->m_padding*4 + wildCardButtonSize.height) );
    wildcardButton = new WildcardButton(
      WILDCARD_BUTTON_BORDER_COLOR_ON, WILDCARD_BUTTON_BORDER_COLOR_OFF
      , WILDCARD_BUTTON_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_BACKGROUND_COLOR_OFF
      , WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_ON, WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "REPLAY\nREMAINING"
      , "100"
      , wildCardButtonSize
      , m_gameContext->getDefaultBorderThickness()
      , m_gameContext
      , callfuncO_selector(WildcardPopup::replayFromCurrentCallback)
      , this);
    wildcardButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    wildcardButton->setPosition(center.x, posY);
    this->addChild(wildcardButton);
        
    posY -= round( (verticalSpacingLarge/2 + verticalSpacing/2 + this->m_padding + wildCardButtonSize.height/2) );

    TextButton* textButton = new TextButton(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "back"
      , m_gameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_gameContext
      , callfuncO_selector(WildcardPopup::closeCallback)
      , this);
    textButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    textButton->setPosition(this->m_textIndentLeft + textButton->getSize().width/2, posY);
    this->addChild(textButton);
    
    textButton = new TextButton(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "+ coins"
      , m_gameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_gameContext
      , callfuncO_selector(WildcardPopup::closeCallback)
      , this);
    textButton->setEnabled(false);
    textButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    textButton->setPosition(this->m_textIndentRight - textButton->getSize().width/2, posY);
    this->addChild(textButton);
    
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

void WildcardPopup::refresh()
{
  char str[10];
  sprintf(str, "%i", m_gameContext->getTotalCoins());
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
  int totalCoins = this->m_gameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_REPLAY_SEQUENCE)
  {
    totalCoins -= COINS_COST_REPLAY_SEQUENCE;
    this->m_gameContext->setTotalCoins(totalCoins);

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
  int totalCoins = this->m_gameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_SHOW_NEXT_ITEM)
  {
    totalCoins -= COINS_COST_SHOW_NEXT_ITEM;
    this->m_gameContext->setTotalCoins(totalCoins);
    
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
  int totalCoins = this->m_gameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_SAVE_TRY)
  {
    totalCoins -= COINS_COST_SAVE_TRY;
    this->m_gameContext->setTotalCoins(totalCoins);
    
    char str[10];
    sprintf(str, "%i", totalCoins);
    m_coinsLabel->setString(str);

    // callback
    if(m_pTarget != 0 && this->m_fnpSaveTryCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpSaveTryCallbackDelegate)(this);
  }
}

void WildcardPopup::closeCallback(CCObject* pSender)
{
  // callback
  if(m_pTarget != 0 && this->m_fnpCloseCallbackDelegate != 0)
      (m_pTarget->*this->m_fnpCloseCallbackDelegate)(this);
}