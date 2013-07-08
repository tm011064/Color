#include "MenuButton.h"
#include "NavigationManager.h"
#include "VisibleRect.h"
#include "Types.h"
#include <cstring> 

MenuButton* MenuButton::create(CCSpriteFrame* bgNormalLeft
    , CCSpriteFrame* bgNormalMiddle
    , CCSpriteFrame* bgNormalRight
    , CCSpriteFrame* bgSelectedLeft
    , CCSpriteFrame* bgSelectedMiddle
    , CCSpriteFrame* bgSelectedRight
    , CCSpriteFrame* bgDisabledLeft
    , CCSpriteFrame* bgDisabledMiddle
    , CCSpriteFrame* bgDisabledRight
    , float normalMiddleScaleX
    , float selectedMiddleScaleX
    , float disabledMiddleScaleX
    , std::string text
    , GameContext* gameContext, SEL_CallFuncO fnpTouchEndedDelegate, CCNode *pTarget)
{
  MenuButton* menuButton = new MenuButton(text, gameContext, fnpTouchEndedDelegate, pTarget);
  menuButton->autorelease();
  
  menuButton->m_bgNormalLeft = CCSprite::createWithSpriteFrame(bgNormalLeft);
  menuButton->m_bgNormalMiddle = CCSprite::createWithSpriteFrame(bgNormalMiddle);
  menuButton->m_bgNormalRight = CCSprite::createWithSpriteFrame(bgNormalRight);
  menuButton->m_bgSelectedLeft = CCSprite::createWithSpriteFrame(bgSelectedLeft);
  menuButton->m_bgSelectedMiddle = CCSprite::createWithSpriteFrame(bgSelectedMiddle); 
  menuButton->m_bgSelectedRight = CCSprite::createWithSpriteFrame(bgSelectedRight);
  menuButton->m_bgDisabledLeft = CCSprite::createWithSpriteFrame(bgDisabledLeft);
  menuButton->m_bgDisabledMiddle = CCSprite::createWithSpriteFrame(bgDisabledMiddle); 
  menuButton->m_bgDisabledRight = CCSprite::createWithSpriteFrame(bgDisabledRight);

  menuButton->m_bgNormalLeft->setPositionX(-(normalMiddleScaleX/2) - menuButton->m_bgNormalLeft->getContentSize().width/2);
  menuButton->m_bgNormalMiddle->setScaleX(normalMiddleScaleX);
  menuButton->m_bgNormalRight->setPositionX(normalMiddleScaleX/2 + menuButton->m_bgNormalRight->getContentSize().width/2);
  
  menuButton->m_bgSelectedLeft->setPositionX(-(selectedMiddleScaleX/2) - menuButton->m_bgSelectedLeft->getContentSize().width/2);
  menuButton->m_bgSelectedMiddle->setScaleX(selectedMiddleScaleX);
  menuButton->m_bgSelectedRight->setPositionX(selectedMiddleScaleX/2 + menuButton->m_bgSelectedRight->getContentSize().width/2);

  menuButton->m_bgDisabledLeft->setPositionX(-(disabledMiddleScaleX/2) - menuButton->m_bgDisabledLeft->getContentSize().width/2);
  menuButton->m_bgDisabledMiddle->setScaleX(disabledMiddleScaleX);
  menuButton->m_bgDisabledRight->setPositionX(disabledMiddleScaleX/2 + menuButton->m_bgDisabledRight->getContentSize().width/2);

  return menuButton;
}
 MenuButton::MenuButton(std::string text
    , GameContext* gameContext, SEL_CallFuncO fnpTouchEndedDelegate, CCNode *pTarget)
  : m_buttonState(UNGRABBED)
  , m_pGameContext(gameContext)
  , m_bgNormal(NULL)
  , m_bgSelected(NULL)
  , m_bgDisabled(NULL)
  , m_fnpTouchEndedDelegate(fnpTouchEndedDelegate)
  , m_isEnabled(true)
  , m_pTarget(pTarget)
  , m_text(text)
  , m_isLayoutInitialized(false)
  , m_bgNormalLeft(NULL)
  , m_bgNormalMiddle(NULL)
  , m_bgNormalRight(NULL)
  , m_bgSelectedLeft(NULL)
  , m_bgSelectedMiddle(NULL)
  , m_bgSelectedRight(NULL)
  , m_bgDisabledLeft(NULL)
  , m_bgDisabledMiddle(NULL)
  , m_bgDisabledRight(NULL)
 {
 }

bool MenuButton::containsTouchLocation(CCTouch* touch)
{
  CCSize size;
  if (this->m_bgNormal && this->m_bgNormal->isVisible())
    size = this->m_bgNormal->getContentSize();
  else if (this->m_bgSelected && this->m_bgSelected->isVisible())
    size = this->m_bgSelected->getContentSize();
  else if (this->m_bgDisabled && this->m_bgDisabled->isVisible())
    size = this->m_bgDisabled->getContentSize();
  else if (this->m_bgNormalLeft && this->m_bgNormalLeft->isVisible())
  {// we asssume the other buttons exist as well
    float width = 0;
    CCSize tileSize;

    tileSize = this->m_bgNormalLeft->getContentSize();
    width += tileSize.width;
    tileSize = this->m_bgNormalMiddle->getContentSize();
    width += tileSize.width * this->m_bgNormalMiddle->getScaleX();
    tileSize = this->m_bgNormalRight->getContentSize();
    width += tileSize.width;

    size = CCSizeMake(width, tileSize.height);
  }
  else if (this->m_bgSelectedLeft && this->m_bgSelectedLeft->isVisible())
  {// we asssume the other buttons exist as well
    float width = 0;
    CCSize tileSize;

    tileSize = this->m_bgSelectedLeft->getContentSize();
    width += tileSize.width;
    tileSize = this->m_bgSelectedMiddle->getContentSize();
    width += tileSize.width * this->m_bgSelectedMiddle->getScaleX();
    tileSize = this->m_bgSelectedRight->getContentSize();
    width += tileSize.width;

    size = CCSizeMake(width, tileSize.height);
  }
  else if (this->m_bgDisabledLeft && this->m_bgDisabledLeft->isVisible())
  {// we asssume the other buttons exist as well
    float width = 0;
    CCSize tileSize;

    tileSize = this->m_bgDisabledLeft->getContentSize();
    width += tileSize.width;
    tileSize = this->m_bgDisabledMiddle->getContentSize();
    width += tileSize.width * this->m_bgDisabledMiddle->getScaleX();
    tileSize = this->m_bgDisabledRight->getContentSize();
    width += tileSize.width;

    size = CCSizeMake(width, tileSize.height);
  }
  else
    return false;
    
  CCPoint location = touch->getLocationInView();
  location = CCDirector::sharedDirector()->convertToGL(location);
  CCPoint fromOrigin = CCNode::convertToNodeSpace(location);  

  return CCRectMake(-size.width / 2, -size.height / 2, size.width, size.height).containsPoint(fromOrigin);
}

void MenuButton::onEnter()
{  
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

  CCNode::onEnter();
  
  if (!this->m_isLayoutInitialized)
  {  
    CCLOG("initializing MenuButton");

    /* Full Images */
    if (m_bgNormal)
      this->addChild(m_bgNormal);
    if (m_bgSelected)
      this->addChild(m_bgSelected);
    if (m_bgDisabled)
      this->addChild(m_bgDisabled);
    
    /* Tiled Images */
    if (m_bgNormalLeft)
      this->addChild(m_bgNormalLeft);
    if (m_bgNormalMiddle)
      this->addChild(m_bgNormalMiddle);
    if (m_bgNormalRight)
      this->addChild(m_bgNormalRight);
    if (m_bgSelectedLeft)
      this->addChild(m_bgSelectedLeft);
    if (m_bgSelectedMiddle)
      this->addChild(m_bgSelectedMiddle);
    if (m_bgSelectedRight)
      this->addChild(m_bgSelectedRight);
    if (m_bgDisabledLeft)
      this->addChild(m_bgDisabledLeft);
    if (m_bgDisabledMiddle)
      this->addChild(m_bgDisabledMiddle);
    if (m_bgDisabledRight)
      this->addChild(m_bgDisabledRight);

    CCSize bodySize, capsSize;

    int totalWidth = 0;
    int tagCounter = 0;

    std::string s;
    char c[256];
    strcpy(c, m_text.c_str());
    char* splitted = strtok(c, " ");
    while (splitted)
    {
      s = splitted;

      tagCounter++;

      CCLabelBMFont* body = CCLabelBMFont::create(s.substr(1, std::strlen(splitted) - 1).c_str(), m_pGameContext->getFontNormalPath().c_str());
      this->addChild(body, tagCounter, tagCounter);
    
      tagCounter++;
      CCLabelBMFont* capLetter  = CCLabelBMFont::create(s.substr(0, 1).c_str(), m_pGameContext->getFontLargePath().c_str());
      this->addChild(capLetter, tagCounter, tagCounter); 
    
      bodySize = body->getContentSize();
      capsSize = capLetter->getContentSize();

      capLetter->setPosition(totalWidth + capsSize.width/2, 0);
      body->setPosition(
        totalWidth + bodySize.width/2 + capsSize.width
        ,-(capsSize.height/2 - bodySize.height/2)/2);

      totalWidth += bodySize.width + capsSize.width + FONT_SPACE_WIDTH;
      splitted = strtok(NULL, " ");
    }

    totalWidth -= FONT_SPACE_WIDTH;
    for (int i = 1; i <= tagCounter; i++)
    {
      CCNode* node = this->getChildByTag(i);
      node->setPositionX(node->getPositionX() - totalWidth/2);  
    }

    CC_SAFE_DELETE(splitted);

    if (m_bgNormalMiddle)
      this->setContentSize(CCSizeMake( totalWidth, m_bgNormalMiddle->getContentSize().height ));
    else
      this->setContentSize(CCSizeMake( totalWidth, m_bgNormal->getContentSize().height ));

    this->refresh();

    CCLOG("finished initializing MenuButton");
    this->m_isLayoutInitialized = true;
  }
}

void MenuButton::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}    

void MenuButton::refresh()
{
  if (this->m_isEnabled)
  {
    if (this->m_bgDisabled)
      this->m_bgDisabled->setVisible(false);
    if (this->m_bgDisabledLeft)
      this->m_bgDisabledLeft->setVisible(false);
    if (this->m_bgDisabledMiddle)
      this->m_bgDisabledMiddle->setVisible(false);
    if (this->m_bgDisabledRight)
      this->m_bgDisabledRight->setVisible(false);
    
    if (this->m_buttonState == GRABBED)
    {
      if (this->m_bgNormal)
        this->m_bgNormal->setVisible(false);
      if (this->m_bgNormalLeft)
        this->m_bgNormalLeft->setVisible(false);
      if (this->m_bgNormalMiddle)
        this->m_bgNormalMiddle->setVisible(false);
      if (this->m_bgNormalRight)
        this->m_bgNormalRight->setVisible(false);
      
      if (this->m_bgSelected)
        this->m_bgSelected->setVisible(true);
      if (this->m_bgSelectedLeft)
        this->m_bgSelectedLeft->setVisible(true);
      if (this->m_bgSelectedMiddle)
        this->m_bgSelectedMiddle->setVisible(true);
      if (this->m_bgSelectedRight)
        this->m_bgSelectedRight->setVisible(true);
    }
    else
    {
      if (this->m_bgNormal)
        this->m_bgNormal->setVisible(true);
      if (this->m_bgNormalLeft)
        this->m_bgNormalLeft->setVisible(true);
      if (this->m_bgNormalMiddle)
        this->m_bgNormalMiddle->setVisible(true);
      if (this->m_bgNormalRight)
        this->m_bgNormalRight->setVisible(true);
      
      if (this->m_bgSelected)
        this->m_bgSelected->setVisible(false);
      if (this->m_bgSelectedLeft)
        this->m_bgSelectedLeft->setVisible(false);
      if (this->m_bgSelectedMiddle)
        this->m_bgSelectedMiddle->setVisible(false);
      if (this->m_bgSelectedRight)
        this->m_bgSelectedRight->setVisible(false);
    }
  }
  else
  {
    if (this->m_bgDisabled)
      this->m_bgDisabled->setVisible(true);
    if (this->m_bgDisabledLeft)
      this->m_bgDisabledLeft->setVisible(true);
    if (this->m_bgDisabledMiddle)
      this->m_bgDisabledMiddle->setVisible(true);
    if (this->m_bgDisabledRight)
      this->m_bgDisabledRight->setVisible(true);
    
    if (this->m_bgNormal)
      this->m_bgNormal->setVisible(false);
    if (this->m_bgNormalLeft)
      this->m_bgNormalLeft->setVisible(false);
    if (this->m_bgNormalMiddle)
      this->m_bgNormalMiddle->setVisible(false);
    if (this->m_bgNormalRight)
      this->m_bgNormalRight->setVisible(false);
    if (this->m_bgSelected)
      this->m_bgSelected->setVisible(false);
    if (this->m_bgSelectedLeft)
      this->m_bgSelectedLeft->setVisible(false);
    if (this->m_bgSelectedMiddle)
      this->m_bgSelectedMiddle->setVisible(false);
    if (this->m_bgSelectedRight)
      this->m_bgSelectedRight->setVisible(false);
  }
}


void MenuButton::setButtonState(ButtonState buttonState)
{ 
  this->m_buttonState = buttonState;
  refresh();
}

bool MenuButton::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
  if (!this->isVisible())
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
void MenuButton::ccTouchMoved(CCTouch* touch, CCEvent* event)
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
void MenuButton::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
  if (containsTouchLocation(touch))
  {      
    if(m_pTarget != 0 && m_fnpTouchEndedDelegate != 0)
        (m_pTarget->*m_fnpTouchEndedDelegate)(this);
  }

  setButtonState(UNGRABBED);
} 