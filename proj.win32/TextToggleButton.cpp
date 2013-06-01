#include "TextToggleButton.h"
#include "NavigationManager.h"
#include "VisibleRect.h"
#include "Types.h"
#include <cstring> 

 TextToggleButton::TextToggleButton(ccColor3B borderColorOn, ccColor3B borderColorOff, ccColor4F backgroundColorOn
    , ccColor4F backgroundColorOff, ccColor3B textColorOn, ccColor3B textColorOff
    , std::string text, ToggleState toggleState, CCSize size, float borderWidth
    , GameContext* gameContext, SEL_CallFuncO fnpToggleChangedDelegate, CCNode *pTarget)
  : m_buttonState(UNGRABBED)
  , m_gameContext(gameContext)
  , m_fnpToggleChangedDelegate(fnpToggleChangedDelegate)
  , m_isEnabled(true)
  , m_pTarget(pTarget)
  , m_isInitialized(false)
  , m_borderColorOn(borderColorOn)
  , m_borderColorOff(borderColorOff)
  , m_backgroundColorOn(backgroundColorOn)
  , m_backgroundColorOff(backgroundColorOff)
  , m_textColorOn(textColorOn)
  , m_textColorOff(textColorOff)
  , m_text(text)
  , m_toggleState(toggleState)
  , m_size(size)
  , m_borderWidth(borderWidth)
 {

 }

bool TextToggleButton::containsTouchLocation(CCTouch* touch)
{
  float posX, posY;
  this->getPosition(&posX, &posY);

  CCPoint location = touch->getLocationInView();
  location = CCDirector::sharedDirector()->convertToGL(location);

  return CCRectMake(posX - m_size.width / 2, posY - m_size.height / 2, m_size.width, m_size.height).containsPoint(location);
}

void TextToggleButton::onEnter()
{  
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

  CCNode::onEnter();
  
  if (!this->m_isInitialized)
  {  
    this->m_isInitialized = true;
    
    m_textLabel = CCLabelBMFont::create(m_text.c_str(), m_gameContext->getFontNormalPath().c_str());
    this->addChild(m_textLabel);

    refresh();
    this->m_isEnabled = this->m_toggleState == OFF;
  }
}

void TextToggleButton::onExit()
{
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->removeDelegate(this);
  CCNode::onExit();
}    

void TextToggleButton::refresh()
{
  this->m_textLabel->setString(this->m_text.c_str());

  this->m_borderOrigin.setPoint(-this->m_size.width/2,-this->m_size.height/2); 
  this->m_borderDestination.setPoint(this->m_size.width/2,this->m_size.height/2);
        
  this->m_backgroundOrigin.setPoint(-this->m_size.width/2 + this->m_borderWidth,-this->m_size.height/2 + this->m_borderWidth); 
  this->m_backgroundDestination.setPoint(this->m_size.width/2 - this->m_borderWidth,this->m_size.height/2 - this->m_borderWidth);

  switch (this->m_toggleState)
  {
  case ON:
    this->m_currentBackgroundColor = this->m_backgroundColorOn;
    this->m_currentBorderColor = this->m_borderColorOn;
    this->m_textLabel->setColor(this->m_textColorOn);
    break;
  case OFF:
    this->m_currentBackgroundColor = this->m_backgroundColorOff;
    this->m_currentBorderColor = this->m_borderColorOff;
    this->m_textLabel->setColor(this->m_textColorOff);
    break;
  }   
}

void TextToggleButton::draw()
{ 
  ccDrawSolidRect(m_backgroundOrigin, m_backgroundDestination, m_currentBackgroundColor);
  ccDrawColor4B(m_currentBorderColor.r, m_currentBorderColor.g,m_currentBorderColor.b,255);
  ccDrawRect(m_borderOrigin, m_borderDestination);
}

void TextToggleButton::setButtonState(ButtonState buttonState)
{ 
  this->m_buttonState = buttonState;
  refresh();
}

bool TextToggleButton::ccTouchBegan(CCTouch* touch, CCEvent* event)
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
void TextToggleButton::ccTouchMoved(CCTouch* touch, CCEvent* event)
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

void TextToggleButton::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
  if (containsTouchLocation(touch))
  {      
    this->setToggleState(this->m_toggleState == ON ? OFF : ON);

    if(m_pTarget != 0 && m_fnpToggleChangedDelegate != 0)
      (m_pTarget->*m_fnpToggleChangedDelegate)(this);
  }

  setButtonState(UNGRABBED);
}

void TextToggleButton::setToggleState(ToggleState toggleState) 
{ 
  this->m_toggleState = toggleState;
  refresh();

  this->m_isEnabled = this->m_toggleState == OFF;
}
