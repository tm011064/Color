#include "WildcardButton.h"
#include "NavigationManager.h"
#include "VisibleRect.h"
#include "Types.h"
#include <cstring> 

 WildcardButton* WildcardButton::create(ccColor4F borderColorOn, ccColor4F borderColorOff
    , ccColor4F backgroundColorOn, ccColor4F backgroundColorOff
    , ccColor4F coinBackgroundColorOn, ccColor4F coinBackgroundColorOff
    , ccColor3B textColorOn, ccColor3B textColorOff
    , std::string text, std::string totalCoinsText, CCSize size, float borderWidth
    , GameContext* gameContext, SEL_CallFuncO fnpChangedDelegate, CCNode *pTarget)
 {
   WildcardButton* wildcardButton = new WildcardButton(borderColorOn, borderColorOff
    , backgroundColorOn, backgroundColorOff
    , coinBackgroundColorOn, coinBackgroundColorOff
    , textColorOn, textColorOff
    , text, totalCoinsText, size, borderWidth
    , gameContext, fnpChangedDelegate, pTarget);
   wildcardButton->autorelease();
   return wildcardButton;
 }

bool WildcardButton::containsTouchLocation(CCTouch* touch)
{  
  CCPoint location = touch->getLocationInView();
  location = CCDirector::sharedDirector()->convertToGL(location);
  CCPoint fromOrigin = CCNode::convertToNodeSpace(location);  

  return CCRectMake(-m_size.width / 2, -m_size.height / 2, m_size.width, m_size.height).containsPoint(fromOrigin);
}

void WildcardButton::onEnter()
{  
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->m_touchPriority, true);

  CCNode::onEnter();
  
  if (!this->m_isLayoutInitialized)
  {  
    this->m_isLayoutInitialized = true;
    this->m_isEnabled = true;

    this->m_borderOrigin.setPoint(round(-this->m_size.width/2), round(-this->m_size.height/2)); 
    this->m_borderDestination.setPoint(round(this->m_size.width/2), round(this->m_size.height/2));
  
    float leftWidth = m_size.width * .7;
  
    this->m_backgroundOrigin.setPoint(round(this->m_borderOrigin.x + this->m_borderWidth), round(this->m_borderOrigin.y + this->m_borderWidth)); 
    this->m_backgroundDestination.setPoint(round(this->m_borderDestination.x - this->m_borderWidth), round(this->m_borderDestination.y - this->m_borderWidth));
  
    this->m_coinBorderOrigin.setPoint(round(this->m_borderOrigin.x + (m_size.width * .65)), round(this->m_backgroundOrigin.y));
    this->m_coinBorderDestination.setPoint(round(this->m_coinBorderOrigin.x + this->m_borderWidth), round(this->m_backgroundDestination.y));
  
    this->m_coinBackgroundOrigin.setPoint(round(this->m_coinBorderDestination.x + this->m_borderWidth), round(m_backgroundOrigin.y));
    
    m_textLabel = CCLabelBMFont::create(m_text.c_str(), m_pGameContext->getFontNormalPath().c_str());
    m_textLabel->setPosition(-m_size.width/2 + m_pGameContext->getDefaultPadding()*4 
                                             + m_textLabel->getContentSize().width/2, 0);
    this->addChild(m_textLabel);

    m_totalCoinsLabel = CCLabelBMFont::create(m_totalCoinsText.c_str(), m_pGameContext->getFontNormalPath().c_str());
    m_totalCoinsLabel->setPosition(ccpRounded(m_size.width/2 - m_pGameContext->getDefaultPadding()*4
                                                             - m_totalCoinsLabel->getContentSize().width/2, 0));
    this->addChild(m_totalCoinsLabel);
        
    CCSprite* coin = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("coin_small"));
    coin->setScale(this->m_pGameContext->getFontHeightNormal() / coin->getContentSize().height * 1.5);
    coin->setPosition(ccpRounded(m_coinBorderDestination.x + m_pGameContext->getDefaultPadding()*4 + coin->getContentSize().width/2, 0));
    this->addChild(coin);
    
    this->setButtonState(UNGRABBED);
  }
}

void WildcardButton::onExit()
{
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->removeDelegate(this);
  CCNode::onExit();
}    

void WildcardButton::setEnabled(bool isEnabled) 
{ 
  this->m_isEnabled = isEnabled; 
}

void WildcardButton::draw()
{ 
  ccDrawSolidRect(m_borderOrigin, m_borderDestination, m_currentBorderColor);
  ccDrawSolidRect(m_backgroundOrigin, m_backgroundDestination, m_currentBackgroundColor);
  ccDrawSolidRect(m_coinBackgroundOrigin, m_backgroundDestination, m_currentCoinBackgroundColor);  
  ccDrawSolidRect(m_coinBorderOrigin, m_coinBorderDestination, m_currentBorderColor);
}

void WildcardButton::setButtonState(ButtonState buttonState)
{ 
  this->m_buttonState = buttonState;
  
  switch (this->m_buttonState)
  {
  case GRABBED:
    this->m_currentBackgroundColor = this->m_backgroundColorOn;
    this->m_currentCoinBackgroundColor = this->m_coinBackgroundColorOn;
    this->m_currentBorderColor = this->m_borderColorOn;
    this->m_textLabel->setColor(this->m_textColorOn);
    this->m_totalCoinsLabel->setColor(this->m_textColorOn);
    break;
  case UNGRABBED:
    this->m_currentBackgroundColor = this->m_backgroundColorOff;
    this->m_currentCoinBackgroundColor = this->m_coinBackgroundColorOff;
    this->m_currentBorderColor = this->m_borderColorOff;
    this->m_textLabel->setColor(this->m_textColorOff);
    this->m_totalCoinsLabel->setColor(this->m_textColorOff);
    break;
  }
}

bool WildcardButton::ccTouchBegan(CCTouch* touch, CCEvent* event)
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
void WildcardButton::ccTouchMoved(CCTouch* touch, CCEvent* event)
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

void WildcardButton::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
  if (containsTouchLocation(touch))
  {      
    if(m_pTarget != 0 && m_fnpChangedDelegate != 0)
      (m_pTarget->*m_fnpChangedDelegate)(this);
  }

  setButtonState(UNGRABBED);
}
