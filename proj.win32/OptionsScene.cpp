#include "OptionsScene.h"

using namespace cocos2d;

void OptionsScene::onEnter()
{
  CCScene::onEnter();

  if (!this->m_isInitialized)
  {  
    this->m_isInitialized = true;

    CCPoint center = VisibleRect::center();
    CCRect visibleRect = VisibleRect::getVisibleRect();
    
    float leftX, rightX;
    float topY, bottomY;
    
    leftX = visibleRect.size.width * .15;
    rightX = visibleRect.size.width - leftX;
    topY = visibleRect.size.height * .7;

    CCSprite* bg = CCSprite::createWithSpriteFrame(m_gameContext->getImageMap()->getTile(0));
    bg->setPosition(center);
    this->addChild(bg, 0);   

    CCLabelBMFont* label = CCLabelBMFont::create("Sound", m_gameContext->getFontNormalPath().c_str());
    label->setPosition(leftX + label->getContentSize().width/2, topY - 100);
    this->addChild(label);

    label = CCLabelBMFont::create("Off", m_gameContext->getFontNormalPath().c_str());
    CCSize size = label->getContentSize();
    
    size.setSize(size.width + this->m_gameContext->getDefaultPadding() * 12, size.width + this->m_gameContext->getDefaultPadding() * 3); 

    label->release();

    ccColor3B toggleColorTextOn = { 0, 0, 0 };
    ccColor3B toggleColorTextOff = { 255, 255, 255 };
    ccColor4F toggleColorBorder = { 1,1,1,1};
    ccColor4F toggleColorBackgroundOn = { 1,1,1,1 };
    ccColor4F toggleColorBackgroundOff = { 0,0,0,1 };

    this->m_soundToggleButtonOn = new TextToggleButton(toggleColorBorder, toggleColorBorder, toggleColorBackgroundOn
      , toggleColorBackgroundOff, toggleColorTextOn, toggleColorTextOff
      , "On"
      , m_gameContext->getIsSoundOn() ? ON : OFF
      , size
      , m_gameContext, callfuncO_selector(OptionsScene::onSoundToggleOnChanged), this);
    this->m_soundToggleButtonOn->setPosition(rightX - 120, topY - 100);
    this->addChild(this->m_soundToggleButtonOn);
    
    this->m_soundToggleButtonOff = new TextToggleButton(toggleColorBorder, toggleColorBorder, toggleColorBackgroundOn
      , toggleColorBackgroundOff, toggleColorTextOn, toggleColorTextOff
      , "Off"
      , m_gameContext->getIsSoundOn() ? OFF : ON
      , size
      , m_gameContext, callfuncO_selector(OptionsScene::onSoundToggleOffChanged), this);
    this->m_soundToggleButtonOff->setPosition(rightX - 60, topY - 100);
    this->addChild(this->m_soundToggleButtonOff);
    
    label = CCLabelBMFont::create("Vibrate", m_gameContext->getFontNormalPath().c_str());
    label->setPosition(leftX + label->getContentSize().width/2, topY - 200);
    this->addChild(label);
    
    this->m_vibrateToggleButtonOn = new TextToggleButton(toggleColorBorder, toggleColorBorder, toggleColorBackgroundOn
      , toggleColorBackgroundOff, toggleColorTextOn, toggleColorTextOff
      , "On"
      , m_gameContext->getIsVibrateOn() ? ON : OFF
      , size
      , m_gameContext, callfuncO_selector(OptionsScene::onVibrateToggleOnChanged), this);
    this->m_vibrateToggleButtonOn->setPosition(rightX - 120, topY - 200);
    this->addChild(this->m_vibrateToggleButtonOn);
    
    this->m_vibrateToggleButtonOff = new TextToggleButton(toggleColorBorder, toggleColorBorder, toggleColorBackgroundOn
      , toggleColorBackgroundOff, toggleColorTextOn, toggleColorTextOff
      , "Off"
      , m_gameContext->getIsVibrateOn() ? OFF : ON
      , size
      , m_gameContext, callfuncO_selector(OptionsScene::onVibrateToggleOffChanged), this);
    this->m_vibrateToggleButtonOff->setPosition(rightX - 60, topY - 200);
    this->addChild(this->m_vibrateToggleButtonOff);
  }
}
void OptionsScene::showMenuCallback(CCObject* pSender)
{ 
  NavigationManager::showScene(MENU_SCENE, m_gameContext, NEW);
}
void OptionsScene::onBackKeyPressed()
{
  NavigationManager::showScene(MENU_SCENE, m_gameContext, NEW);
}


void OptionsScene::onSoundToggleOnChanged(CCObject* pSender)
{
  this->m_soundToggleButtonOff->setToggleState(this->m_soundToggleButtonOn->getToggleState() == ON ? OFF : ON);
  this->m_gameContext->setIsSoundOn(this->m_soundToggleButtonOn->getToggleState() == ON);
}
void OptionsScene::onSoundToggleOffChanged(CCObject* pSender)
{
  this->m_soundToggleButtonOn->setToggleState(this->m_soundToggleButtonOff->getToggleState() == ON ? OFF : ON);
  this->m_gameContext->setIsSoundOn(this->m_soundToggleButtonOn->getToggleState() == ON);
}
void OptionsScene::onVibrateToggleOnChanged(CCObject* pSender)
{
  this->m_vibrateToggleButtonOff->setToggleState(this->m_vibrateToggleButtonOn->getToggleState() == ON ? OFF : ON);
  this->m_gameContext->setIsVibrateOn(this->m_vibrateToggleButtonOn->getToggleState() == ON);
}
void OptionsScene::onVibrateToggleOffChanged(CCObject* pSender)
{
  this->m_vibrateToggleButtonOn->setToggleState(this->m_vibrateToggleButtonOff->getToggleState() == ON ? OFF : ON);
  this->m_gameContext->setIsVibrateOn(this->m_vibrateToggleButtonOn->getToggleState() == ON);
}