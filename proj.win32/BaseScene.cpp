#include "BaseScene.h"

void BaseScene::onEnter()
{
  CCScene::onEnter();
  
  if (!this->m_isLayoutInitialized)
  {   
    this->m_isLayoutInitialized = true;
    if (this->m_showSplashScreen)
    {
      CCRect visibleRect = VisibleRect::getVisibleRect();   

      m_splashScreen = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("splash"));
      CCSize s = m_splashScreen->getContentSize();
      m_splashScreen->setScaleX(visibleRect.size.width / s.width);
      m_splashScreen->setScaleY(visibleRect.size.height / s.height);
      m_splashScreen->setPosition(VisibleRect::center());
      this->addChild(m_splashScreen, SPLASH_ZORDER);
    
      m_splashLogoScreen = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("splashLogo"));
      m_splashLogoScreen->setPosition(VisibleRect::center());
      this->addChild(m_splashLogoScreen, SPLASH_ZORDER);
      
      this->scheduleOnce(schedule_selector(BaseScene::initialize), 0.01f);
    }
    else
    {
      initialize(.0f);
    }
  }
}

void BaseScene::hideSplashScreen()
{    
  if (m_splashScreen && m_splashLogoScreen)
  {
    this->m_splashScreen->setOpacity((GLubyte)255);
    this->m_splashLogoScreen->setOpacity((GLubyte)255);
    this->m_splashScreen->runAction(CCSequence::create(CCDelayTime::create(.5f), CCFadeOut::create(.4), NULL));
    this->m_splashLogoScreen->runAction(CCSequence::create(CCDelayTime::create(.1f), CCFadeOut::create(.3), NULL));
  }
}
