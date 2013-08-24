#include "OptionsScene.h"

using namespace cocos2d;

void OptionsScene::onEnter()
{
  CCScene::onEnter();

  if (!this->m_isLayoutInitialized)
  {  
    this->m_isLayoutInitialized = true;
    
    CCPoint center = VisibleRect::center();
    CCPoint rightTop = VisibleRect::rightTop();
    CCRect visibleRect = VisibleRect::getVisibleRect();
    m_visibleRectLeftBottom = VisibleRect::leftBottom();
    m_visibleRectRightTop = VisibleRect::rightTop();
    
    
    RepeatingSprite* bg = RepeatingSprite::create(
      m_pGameContext
      , m_pGameContext->getImageMap()->getTile("background")
      , HORIZONTAL
      , NORMAL
      , visibleRect.size);
    bg->setPosition(center);
    this->addChild(bg, -1);
    bg = NULL;
        
    float padding = m_pGameContext->getDefaultPadding();
    float borderThickness = m_pGameContext->getDefaultBorderThickness();

    float verticalSpacing = m_pGameContext->getFontHeightNormal() + padding;
    float verticalSpacingLarge = m_pGameContext->getFontHeightLarge() + padding*3;
            
    m_panelRectLeftTop = ccp ( 0, m_visibleRectRightTop.y * .825);
    m_panelRectLeftBottom = ccp ( 0, m_visibleRectRightTop.y * .26 );
    m_panelRectRightTop = ccp ( m_visibleRectRightTop.x, m_panelRectLeftTop.y);
    m_panelRectRightBottom = ccp ( m_visibleRectRightTop.x, m_panelRectLeftBottom.y);
    
    m_separatorTopRight = ccp ( m_visibleRectRightTop.x, m_panelRectRightTop.y + borderThickness);
    m_separatorBottomRight = ccp ( m_visibleRectRightTop.x, m_panelRectRightBottom.y - borderThickness);

    // now we have the border thickness and padding, so we can set the boundaries 
    float indentLeft = m_visibleRectLeftBottom.x + (visibleRect.size.width * .05);
    float indentRight = m_visibleRectLeftBottom.x + (visibleRect.size.width * .9);
    m_panelRectInnerLeftBottom = ccp( indentLeft + borderThickness, m_panelRectLeftBottom.y + borderThickness );
    m_panelRectInnerRightTop = ccp( indentRight - borderThickness, m_panelRectRightTop.y - borderThickness );

    this->m_textIndentLeft = m_panelRectInnerLeftBottom.x + padding * 3;
    this->m_textIndentRight = m_panelRectInnerRightTop.x - padding * 3;
        
    float posY = round( m_panelRectInnerRightTop.y + verticalSpacingLarge/2 );

    CCLabelBMFont* label = CCLabelBMFont::create("OPTIONS", m_pGameContext->getFontLargePath().c_str());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2, posY );
    this->addChild(label);

    label = CCLabelBMFont::create("off", m_pGameContext->getFontNormalPath().c_str());
    CCSize size = label->getContentSize();
    
    size.setSize(size.width + padding * 12, size.height + padding * 4); 

    label->release();

    ccColor3B toggleColorTextOn = { 0, 0, 0 };
    ccColor3B toggleColorTextOff = { 255, 255, 255 };
    ccColor4F toggleColorBorder = { 1,1,1,1};
    ccColor4F toggleColorBackgroundOn = { 1,1,1,1 };
    ccColor4F toggleColorBackgroundOff = { 0,0,0,1 };
    
    posY = round( m_panelRectInnerRightTop.y - verticalSpacing * 2 );    
    
    this->m_soundToggleButtonOff = TextToggleButton::create(toggleColorBorder, toggleColorBorder, toggleColorBackgroundOn
      , toggleColorBackgroundOff, toggleColorTextOn, toggleColorTextOff
      , "off"
      , m_pGameContext->getIsSoundOn() ? OFF : ON
      , size
      , m_pGameContext, callfuncO_selector(OptionsScene::onSoundToggleOffChanged), this);
    this->m_soundToggleButtonOff->setPosition(m_textIndentRight - size.width/2, posY);
    this->addChild(this->m_soundToggleButtonOff);

    this->m_soundToggleButtonOn = TextToggleButton::create(toggleColorBorder, toggleColorBorder, toggleColorBackgroundOn
      , toggleColorBackgroundOff, toggleColorTextOn, toggleColorTextOff
      , "on"
      , m_pGameContext->getIsSoundOn() ? ON : OFF
      , size
      , m_pGameContext, callfuncO_selector(OptionsScene::onSoundToggleOnChanged), this);
    this->m_soundToggleButtonOn->setPosition(this->m_soundToggleButtonOff->getPositionX() - padding*2 - size.width, posY);
    this->addChild(this->m_soundToggleButtonOn);
    
    label = CCLabelBMFont::create("Sound", m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_soundToggleButtonOn->getPositionX() - padding*8 - size.width/2 - label->getContentSize().width/2, posY);
    this->addChild(label);
    
    posY -= verticalSpacing * 2;    
    this->m_vibrateToggleButtonOff = TextToggleButton::create(toggleColorBorder, toggleColorBorder, toggleColorBackgroundOn
      , toggleColorBackgroundOff, toggleColorTextOn, toggleColorTextOff
      , "off"
      , m_pGameContext->getIsVibrateOn() ? OFF : ON
      , size
      , m_pGameContext, callfuncO_selector(OptionsScene::onVibrateToggleOffChanged), this);
    this->m_vibrateToggleButtonOff->setPosition(m_textIndentRight - size.width/2, posY);
    this->addChild(this->m_vibrateToggleButtonOff);

    this->m_vibrateToggleButtonOn = TextToggleButton::create(toggleColorBorder, toggleColorBorder, toggleColorBackgroundOn
      , toggleColorBackgroundOff, toggleColorTextOn, toggleColorTextOff
      , "on"
      , m_pGameContext->getIsVibrateOn() ? ON : OFF
      , size
      , m_pGameContext, callfuncO_selector(OptionsScene::onVibrateToggleOnChanged), this);
    this->m_vibrateToggleButtonOn->setPosition(this->m_vibrateToggleButtonOff->getPositionX() - padding*2 - size.width, posY);
    this->addChild(this->m_vibrateToggleButtonOn);
    
    label = CCLabelBMFont::create("Vibrate", m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_vibrateToggleButtonOn->getPositionX() - padding*8 - size.width/2 - label->getContentSize().width/2, posY);
    this->addChild(label);
        
    
    TextButton* textButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "back"
      , m_pGameContext->getDefaultButtonSize()
      , borderThickness
      , this->m_pGameContext
      , callfuncO_selector(OptionsScene::showMenuCallback)
      , this);
    textButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    size = textButton->getSize();
    textButton->setPosition(center.x, size.height/2 + padding * 4);
    this->addChild(textButton);

    m_panelRectLeftBottom = ccp ( m_panelRectLeftBottom.x, textButton->getPositionY() + size.height/2 + padding * 4 );
    m_separatorBottomRight = ccp ( m_separatorBottomRight.x, m_panelRectLeftBottom.y + borderThickness);

    m_bgLight.a = .4f; 
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

void OptionsScene::draw()
{ 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
  ccDrawSolidRect(m_panelRectLeftBottom, m_panelRectRightTop, m_bgDark);
  
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  ccDrawSolidRect(m_panelRectLeftTop, m_separatorTopRight, m_separatorColor);
  ccDrawSolidRect(m_panelRectLeftBottom, m_separatorBottomRight, m_separatorColor);
}

void OptionsScene::showMenuCallback(CCObject* pSender)
{ 
  NavigationManager::showScene(MENU_SCENE, m_pGameContext, NEW, false);
}
void OptionsScene::onBackKeyPressed()
{
  NavigationManager::showScene(MENU_SCENE, m_pGameContext, NEW, false);
}

void OptionsScene::onSoundToggleOnChanged(CCObject* pSender)
{
  this->m_soundToggleButtonOff->setToggleState(this->m_soundToggleButtonOn->getToggleState() == ON ? OFF : ON);
  this->m_pGameContext->setIsSoundOn(this->m_soundToggleButtonOn->getToggleState() == ON);
}
void OptionsScene::onSoundToggleOffChanged(CCObject* pSender)
{
  this->m_soundToggleButtonOn->setToggleState(this->m_soundToggleButtonOff->getToggleState() == ON ? OFF : ON);
  this->m_pGameContext->setIsSoundOn(this->m_soundToggleButtonOn->getToggleState() == ON);
}
void OptionsScene::onVibrateToggleOnChanged(CCObject* pSender)
{
  this->m_vibrateToggleButtonOff->setToggleState(this->m_vibrateToggleButtonOn->getToggleState() == ON ? OFF : ON);
  this->m_pGameContext->setIsVibrateOn(this->m_vibrateToggleButtonOn->getToggleState() == ON);
}
void OptionsScene::onVibrateToggleOffChanged(CCObject* pSender)
{
  this->m_vibrateToggleButtonOn->setToggleState(this->m_vibrateToggleButtonOff->getToggleState() == ON ? OFF : ON);
  this->m_pGameContext->setIsVibrateOn(this->m_vibrateToggleButtonOn->getToggleState() == ON);
}