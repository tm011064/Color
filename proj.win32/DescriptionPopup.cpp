#include "DescriptionPopup.h"

void DescriptionPopup::onEnter()
{
  ModalControl::onEnter();

  if (!this->m_isLayoutInitialized)
  {
    CCPoint center = VisibleRect::center();
    CCRect rect = VisibleRect::getVisibleRect();

    this->m_padding = 12;

    m_text = CCLabelBMFont::create("", m_gameContext->getFontNormalPath().c_str());
    m_text->setPosition(center);
    this->addChild(m_text);
    
    m_dialogRectLeftBottom.setPoint(0, 0);
    m_dialogRectRightTop.setPoint(rect.size.width, rect.size.height);

    m_visibleRectLeftBottom = VisibleRect::leftBottom();
    m_visibleRectRightTop = VisibleRect::rightTop();

    m_backgroundColor.a = .7f;
    m_backgroundColor.r = 0;
    m_backgroundColor.g = 0;
    m_backgroundColor.b = 0;
    m_dialogColor.a = 1;
    m_dialogColor.r = 0;
    m_dialogColor.g = 0;
    m_dialogColor.b = 0;
  }
}

void DescriptionPopup::setText(std::string text)
{
  m_text->setString(text.c_str());

  CCSize size = m_text->getContentSize();
  CCPoint position = m_text->getPosition();

  m_dialogRectLeftBottom.setPoint(position.x - size.width/2 - m_padding, position.y - size.height/2 - m_padding);
  m_dialogRectRightTop.setPoint(position.x + size.width/2 + m_padding, position.y + size.height/2 + m_padding);
}

void DescriptionPopup::draw()
{  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  ccDrawSolidRect(m_visibleRectLeftBottom, m_visibleRectRightTop, m_backgroundColor);
  ccDrawSolidRect(m_dialogRectLeftBottom, m_dialogRectRightTop, m_dialogColor);
  
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}
bool DescriptionPopup::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) 
{ 
  if (!this->m_bVisible)
    return false;

  if(m_pTarget != 0 && this->m_fnpCloseCallbackDelegate != 0)
      (m_pTarget->*this->m_fnpCloseCallbackDelegate)(this);
  return true;
}