#include "TextButton.h"
#include "NavigationManager.h"
#include "VisibleRect.h"
#include "Types.h"
#include <cstring> 

 TextButton::TextButton(ccColor3B borderColorOn, ccColor3B borderColorOff, ccColor4F backgroundColorOn
    , ccColor4F backgroundColorOff, ccColor3B textColorOn, ccColor3B textColorOff
    , std::string text, CCSize size, float borderWidth
    , GameContext* gameContext, SEL_CallFuncO fnpChangedDelegate, CCNode *pTarget)
  : m_buttonState(UNGRABBED)
  , m_gameContext(gameContext)
  , m_fnpChangedDelegate(fnpChangedDelegate)
  , m_isEnabled(true)
  , m_pTarget(pTarget)
  , m_isLayoutInitialized(false)
  , m_borderColorOn(borderColorOn)
  , m_borderColorOff(borderColorOff)
  , m_backgroundColorOn(backgroundColorOn)
  , m_backgroundColorOff(backgroundColorOff)
  , m_textColorOn(textColorOn)
  , m_textColorOff(textColorOff)
  , m_text(text)
  , m_size(size)
  , m_borderWidth(borderWidth)
 {

 }

bool TextButton::containsTouchLocation(CCTouch* touch)
{
  CCPoint location = touch->getLocationInView();
  location = CCDirector::sharedDirector()->convertToGL(location);
  CCPoint fromOrigin = CCNode::convertToNodeSpace(location);  

  return CCRectMake(-m_size.width / 2, -m_size.height / 2, m_size.width, m_size.height).containsPoint(fromOrigin);
}

void TextButton::onEnter()
{  
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->m_touchPriority, true);

  CCNode::onEnter();
  
  if (!this->m_isLayoutInitialized)
  {  
    this->m_isLayoutInitialized = true;
    this->m_isEnabled = true;

    m_textLabel = CCLabelBMFont::create(m_text.c_str(), m_gameContext->getFontNormalPath().c_str());
    this->addChild(m_textLabel);

    refresh();
    this->setButtonState(UNGRABBED);
  }
}

void TextButton::onExit()
{
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->removeDelegate(this);
  CCNode::onExit();
}    

void TextButton::refresh()
{
  this->m_textLabel->setString(this->m_text.c_str());

  this->m_borderOrigin.setPoint(-this->m_size.width/2,-this->m_size.height/2); 
  this->m_borderDestination.setPoint(this->m_size.width/2,this->m_size.height/2);
        
  this->m_backgroundOrigin.setPoint(-this->m_size.width/2 + this->m_borderWidth,-this->m_size.height/2 + this->m_borderWidth); 
  this->m_backgroundDestination.setPoint(this->m_size.width/2 - this->m_borderWidth,this->m_size.height/2 - this->m_borderWidth);
}

void TextButton::draw()
{ 
  ccDrawSolidRect(m_backgroundOrigin, m_backgroundDestination, m_currentBackgroundColor);
  ccDrawColor4B(m_currentBorderColor.r, m_currentBorderColor.g,m_currentBorderColor.b,255);
  ccDrawRect(m_borderOrigin, m_borderDestination);
}

void TextButton::setButtonState(ButtonState buttonState)
{ 
  this->m_buttonState = buttonState;
  
  switch (this->m_buttonState)
  {
  case GRABBED:
    this->m_currentBackgroundColor = this->m_backgroundColorOn;
    this->m_currentBorderColor = this->m_borderColorOn;
    this->m_textLabel->setColor(this->m_textColorOn);
    break;
  case UNGRABBED:
    this->m_currentBackgroundColor = this->m_backgroundColorOff;
    this->m_currentBorderColor = this->m_borderColorOff;
    this->m_textLabel->setColor(this->m_textColorOff);
    break;
  }   
}

bool TextButton::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
  if (!this->isVisible() || !this->m_isEnabled)
    return false;

  if (containsTouchLocation(touch))
  {      
    setButtonState(GRABBED);
    return true;     
  }
  else
  {
    setButtonState(UNGRABBED);
  }

  return false;
}
void TextButton::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
  if (containsTouchLocation(touch))
  {      
    setButtonState(GRABBED);
  }
  else
  {
    setButtonState(UNGRABBED);
  }
}

void TextButton::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
  if (containsTouchLocation(touch))
  {      
    if(m_pTarget != 0 && m_fnpChangedDelegate != 0)
      (m_pTarget->*m_fnpChangedDelegate)(this);
  }

  setButtonState(UNGRABBED);
}
