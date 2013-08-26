#include "DescriptionPopup.h"

DescriptionPopup* DescriptionPopup::create(GameContext* gameContext
    , SEL_CallFuncO closeCallbackDelegate
    , CCNode* callbackTarget
    , std::string header, std::string text, CCSpriteFrame* icon
    , ccColor4F backgroundColor, ccColor4F dialogColor, ccColor4F dialogBorderColor)
{
  DescriptionPopup* descriptionPopup = new DescriptionPopup(gameContext, closeCallbackDelegate
    , callbackTarget, header, text, icon, backgroundColor, dialogColor, dialogBorderColor);

  descriptionPopup->autorelease();

  return descriptionPopup;
}

void DescriptionPopup::onEnter()
{
  ModalControl::onEnter();

  if (!this->m_isLayoutInitialized)
  {
    CCPoint center = VisibleRect::center();
    CCRect visibleRect = VisibleRect::getVisibleRect();
    
    m_dialogRectLeftBottom.setPoint(
      visibleRect.size.width * .126f
      , visibleRect.size.height * .158f);
    m_dialogRectRightTop.setPoint(
      visibleRect.size.width - (visibleRect.size.width * .126f)
      , visibleRect.size.height - (visibleRect.size.height * .112f));

    m_dialogRectInnerLeftBottom.setPoint(
      m_dialogRectLeftBottom.x + this->m_pGameContext->getDefaultBorderThickness()
      , m_dialogRectLeftBottom.y + this->m_pGameContext->getDefaultBorderThickness());
    m_dialogRectInnerRightTop.setPoint(
      m_dialogRectRightTop.x - this->m_pGameContext->getDefaultBorderThickness()
      , m_dialogRectRightTop.y - this->m_pGameContext->getDefaultBorderThickness());
    
    float innerRectWidth = m_dialogRectInnerRightTop.x - m_dialogRectInnerLeftBottom.x;
    float padding = m_pGameContext->getDefaultPadding() * 8.0f;

    CCLabelBMFont* header = CCLabelBMFont::create(m_header.c_str(), m_pGameContext->getFontLargePath().c_str());
    CCSize size = header->getContentSize();
    header->setPosition(ccpRounded(
      m_dialogRectInnerLeftBottom.x + innerRectWidth * GOLDEN_RATIO_NEGATIVE_PERCENTAGE 
        + size.width/2 + m_pGameContext->getDefaultPadding()
      , m_dialogRectRightTop.y - size.height/2 - padding));
    this->addChild(header);

    CCSprite* sprite = CCSprite::createWithSpriteFrame(m_icon);
    size = sprite->getContentSize();
    sprite->setPosition(ccpRounded(
      m_dialogRectInnerLeftBottom.x + innerRectWidth * GOLDEN_RATIO_NEGATIVE_PERCENTAGE 
        - size.width/2 - m_pGameContext->getDefaultPadding()
      , header->getPositionY()));
    this->addChild(sprite);
        
    m_playButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
    , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
    , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
    , "play"
    , m_pGameContext->getDefaultButtonSize()
    , this->m_pGameContext->getDefaultBorderThickness()
    , this->m_pGameContext
    , callfuncO_selector(DescriptionPopup::playCallback)
    , this);
    m_playButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);    
    m_playButton->setPosition(center.x, m_dialogRectInnerLeftBottom.y + padding + m_playButton->getSize().height/2);
    m_playButton->setVisible(false);
    this->addChild(m_playButton);

    float innerTopY = header->getPositionY() - header->getContentSize().height/2;
    float innerBottomY = m_playButton->getPositionY() + m_playButton->getSize().height/2;
            
    CCLabelBMFont* body = CCLabelBMFont::create(m_text.c_str(), m_pGameContext->getFontNormalPath().c_str());
    body->setPosition(ccpRounded(
      m_dialogRectInnerLeftBottom.x + padding + body->getContentSize().width/2
      , innerTopY - (innerTopY - innerBottomY)/2
      ));
    this->addChild(body);

    m_visibleRectLeftBottom = VisibleRect::leftBottom();
    m_visibleRectRightTop = VisibleRect::rightTop();
  }
}

void DescriptionPopup::setEnablePlayButton(bool isEnabled)
{
  if (this->m_playButton)
  {
    this->m_playButton->setVisible(isEnabled);
  }
}

void DescriptionPopup::draw()
{  
  ccDrawSolidRect(m_visibleRectLeftBottom, m_visibleRectRightTop, m_backgroundColor);
  ccDrawSolidRect(m_dialogRectLeftBottom, m_dialogRectRightTop, m_dialogBorderColor);
  ccDrawSolidRect(m_dialogRectInnerLeftBottom, m_dialogRectInnerRightTop, m_dialogColor);
}

void DescriptionPopup::playCallback(CCObject* pSender)
{
  if(m_pTarget != 0 && this->m_fnpCloseCallbackDelegate != 0)
      (m_pTarget->*this->m_fnpCloseCallbackDelegate)(this);
}