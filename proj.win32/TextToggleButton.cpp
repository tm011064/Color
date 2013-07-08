#include "TextToggleButton.h"
#include "NavigationManager.h"
#include "VisibleRect.h"
#include "Types.h"
#include <cstring> 

 TextToggleButton* TextToggleButton::create(ccColor4F borderColorOn, ccColor4F borderColorOff, ccColor4F backgroundColorOn
    , ccColor4F backgroundColorOff, ccColor3B textColorOn, ccColor3B textColorOff
    , std::string text, ToggleState toggleState, CCSize size
    , GameContext* gameContext, SEL_CallFuncO fnpToggleChangedDelegate, CCNode *pTarget)
 {
   TextToggleButton* textToggleButton = new TextToggleButton(borderColorOn, borderColorOff, backgroundColorOn
    , backgroundColorOff, textColorOn, textColorOff
    , text, toggleState, size, gameContext, fnpToggleChangedDelegate, pTarget);
   textToggleButton->autorelease();
   return textToggleButton;
 }

bool TextToggleButton::containsTouchLocation(CCTouch* touch)
{
  CCPoint location = touch->getLocationInView();
  location = CCDirector::sharedDirector()->convertToGL(location);
  CCPoint fromOrigin = CCNode::convertToNodeSpace(location);  

  return CCRectMake(-m_size.width / 2, -m_size.height / 2, m_size.width, m_size.height).containsPoint(fromOrigin);
}

void TextToggleButton::onEnter()
{  
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

  CCNode::onEnter();
  
  if (!this->m_isLayoutInitialized)
  {  
    this->m_isLayoutInitialized = true;
    
    m_textLabel = CCLabelBMFont::create(m_text.c_str(), m_pGameContext->getFontNormalPath().c_str());
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
  
  this->m_borderOrigin.setPoint(round(-this->m_size.width/2),round(-this->m_size.height/2)); 
  this->m_borderDestination.setPoint(round(this->m_size.width/2),round(this->m_size.height/2));
        
  this->m_backgroundOrigin.setPoint(round(this->m_borderOrigin.x + this->m_pGameContext->getDefaultBorderThickness()),round(this->m_borderOrigin.y + this->m_pGameContext->getDefaultBorderThickness())); 
  this->m_backgroundDestination.setPoint(round(this->m_borderDestination.x - this->m_pGameContext->getDefaultBorderThickness()),round(this->m_borderDestination.y - this->m_pGameContext->getDefaultBorderThickness()));

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
  ccDrawSolidRect(m_borderOrigin, m_borderDestination, m_currentBorderColor);
  ccDrawSolidRect(m_backgroundOrigin, m_backgroundDestination, m_currentBackgroundColor);
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
