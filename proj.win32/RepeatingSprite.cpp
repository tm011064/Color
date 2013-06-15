#include "RepeatingSprite.h"

void RepeatingSprite::onEnter()
{
  CCNode::onEnter();

  if (!this->m_isLayoutInitialized)
  {
    this->m_isLayoutInitialized = true;
        
    CCSprite* bg = CCSprite::createWithSpriteFrame(m_spriteFrame);
    CCSize bgPatternSize = bg->getContentSize();

    float xPos, yPos
      , scaleX = 1 //m_gameContext->getHorizontalScaleFactor()
      , scaleY = 1; //m_gameContext->getVerticalScaleFactor();

    float scaleMultiplier = this->m_mode == NORMAL ? 1 : -1;
      CCSize s = m_gameContext->getOriginalSize();
      CCRect visibleRect = VisibleRect::getVisibleRect();
    switch (this->m_direction)
    {
    case HORIZONTAL:

      xPos = round(-this->getPositionX() + visibleRect.origin.x);
      for (int i = round(bgPatternSize.width/2); i < m_boundingBox.width; i += bgPatternSize.width)
      {
        bg = CCSprite::createWithSpriteFrame(m_spriteFrame);
        bg->setPosition(ccp(xPos + i, 0));
        bg->setScaleX(scaleX);
        this->addChild(bg);
        bg = NULL;

        scaleX *= scaleMultiplier;
      }
      break;

    case VERTICAL:      
      yPos = -this->getPositionY();
      for (int i = round(bgPatternSize.height/2); i < m_boundingBox.height; i += bgPatternSize.height)
      {
        bg = CCSprite::createWithSpriteFrame(m_spriteFrame);
        bg->setPosition(ccp(0, yPos + i));
        bg->setScaleY(scaleY);
        this->addChild(bg);
        bg = NULL;

        scaleY *= scaleMultiplier;
      }
      break;
      
    case HORIZONTAL_AND_VERTICAL:
      yPos = m_boundingBox.height - bgPatternSize.height/2;
      while (yPos >= 0)
      {
        for (int i = round(bgPatternSize.width/2); i < m_boundingBox.width; i += bgPatternSize.width)
        {
          bg = CCSprite::createWithSpriteFrame(m_spriteFrame);
          bg->setPosition(ccp(i, yPos));
          bg->setScaleX(scaleX);
          bg->setScaleY(scaleY);
          this->addChild(bg);
          bg = NULL;

          scaleX *= scaleMultiplier;
        }

        scaleY *= scaleMultiplier;
        yPos -= bgPatternSize.height;
      }
      break;
    }    
  }
}
