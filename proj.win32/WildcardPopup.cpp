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
            
    m_dialogRectLeftTop = ccp ( 0, m_visibleRectRightTop.y * .875);
    m_dialogRectLeftBottom = ccp ( 0, m_visibleRectRightTop.y * .16 );
    m_dialogRectRightTop = ccp ( m_visibleRectRightTop.x, m_dialogRectLeftTop.y);
    m_dialogRectRightBottom = ccp ( m_visibleRectRightTop.x, m_dialogRectLeftBottom.y);
    
    m_separatorTopRight = ccp ( m_visibleRectRightTop.x, m_dialogRectRightTop.y + m_borderThickness);
    m_separatorBottomRight = ccp ( m_visibleRectRightTop.x, m_dialogRectRightBottom.y - m_borderThickness);

    // now we have the border thickness and padding, so we can set the boundaries 
    float indentLeft = m_visibleRectLeftBottom.x + (visibleRect.size.width * .15);
    float indentRight = m_visibleRectLeftBottom.x + (visibleRect.size.width * .85);
    m_dialogRectInnerLeftBottom = ccp( indentLeft + this->m_borderThickness, m_dialogRectLeftBottom.y + this->m_borderThickness );
    m_dialogRectInnerRightTop = ccp( indentRight - this->m_borderThickness, m_dialogRectRightTop.y - this->m_borderThickness );

    this->m_textIndentLeft = m_dialogRectInnerLeftBottom.x + m_padding * 3;
    this->m_textIndentRight = m_dialogRectInnerRightTop.x - m_padding * 3;
    
    float posY = m_dialogRectInnerRightTop.y - verticalSpacingLarge/2;
    CCLabelBMFont* label = CCLabelBMFont::create("WILDCARDS", m_gameContext->getFontLargePath().c_str());
    label->setPosition(center.x, posY );
    this->addChild(label);

    m_coinsLabel = CCLabelBMFont::create("NA", m_gameContext->getFontNormalPath().c_str());
    m_coinsLabel->setPosition(ccp(this->m_textIndentRight - m_coinsLabel->getContentSize().width/2, posY));
    this->addChild(m_coinsLabel);
    
    posY -= (verticalSpacingLarge/2 + verticalSpacing/2 + this->m_padding);

    m_replaySequence = CCLabelBMFont::create("REPLAY SEQUENCE", m_gameContext->getFontNormalPath().c_str());
    m_replaySequence->setPosition(this->m_textIndentLeft + m_replaySequence->getContentSize().width/2, posY);
    this->addChild(m_replaySequence);
    m_replaySequenceButton = new TextButton(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "50c"
      , m_gameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_gameContext
      , callfuncO_selector(WildcardPopup::replaySequenceCallback)
      , this);
    m_replaySequenceButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    m_replaySequenceButton->setPosition(this->m_textIndentRight - m_replaySequenceButton->getSize().width/2, posY);
    this->addChild(m_replaySequenceButton);

    posY -= verticalSpacing;
    m_showNext = CCLabelBMFont::create("SHOW NEXT", m_gameContext->getFontNormalPath().c_str());
    m_showNext->setPosition(this->m_textIndentLeft + m_showNext->getContentSize().width/2, posY);
    this->addChild(m_showNext);
    m_showNextButton = new TextButton(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "100c"
      , m_gameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_gameContext
      , callfuncO_selector(WildcardPopup::showNextSequenceItemCallback)
      , this);
    m_showNextButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    m_showNextButton->setPosition(this->m_textIndentRight - m_showNextButton->getSize().width/2, posY);
    this->addChild(m_showNextButton);
        
    posY -= verticalSpacing;
    m_replayFromCurrent = CCLabelBMFont::create("REPLAY REMAINING", m_gameContext->getFontNormalPath().c_str());
    m_replayFromCurrent->setPosition(this->m_textIndentLeft + m_replayFromCurrent->getContentSize().width/2, posY);
    this->addChild(m_replayFromCurrent);
    m_replayFromCurrentButton = new TextButton(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "150c"
      , m_gameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_gameContext
      , callfuncO_selector(WildcardPopup::replayFromCurrentCallback)
      , this);
    m_replayFromCurrentButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    m_replayFromCurrentButton->setPosition(this->m_textIndentRight - m_replayFromCurrentButton->getSize().width/2, posY);
    this->addChild(m_replayFromCurrentButton);
    
        
    m_backgroundColor.a = .7f;
    m_backgroundColor.r = 0;
    m_backgroundColor.g = 0;
    m_backgroundColor.b = 0;
    m_dialogColor.a = 1;
    m_dialogColor.r = .1;
    m_dialogColor.g = .1;
    m_dialogColor.b = .1;
    m_dialogBorderColor.a = 1; 
    m_dialogBorderColor.r = 0; 
    m_dialogBorderColor.g = 0; 
    m_dialogBorderColor.b = 0; 
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
  m_coinsLabel->setPositionX(m_dialogRectRightTop.x - m_padding*2 - m_coinsLabel->getContentSize().width/2);
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