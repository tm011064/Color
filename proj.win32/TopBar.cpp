#include "TopBar.h"

void TopBar::onEnter()
{
  CCNode::onEnter();

  if (!this->m_isLayoutInitialized)
  {
    CCLabelBMFont* levelTextLabel = CCLabelBMFont::create("Level:", m_pGameContext->getFontNormalPath().c_str());     
    this->addChild(levelTextLabel);
    CCLabelBMFont* scoreTextLabel = CCLabelBMFont::create("Score:", m_pGameContext->getFontNormalPath().c_str());     
    this->addChild(scoreTextLabel);
    
    m_levelLabel = CCLabelBMFont::create("888", m_pGameContext->getFontNormalPath().c_str());     
    this->addChild(m_levelLabel);
    m_scoreLabel = CCLabelBMFont::create("88888888", m_pGameContext->getFontNormalPath().c_str());     
    this->addChild(m_scoreLabel);
        
    float padding = m_pGameContext->getDefaultPadding();
    float borderThickness = m_pGameContext->getDefaultBorderThickness();
    
    CCPoint leftTop = VisibleRect::leftTop();
    CCPoint rightTop = VisibleRect::rightTop();

    // TODO (Roman): round all points

    m_rectOrigin = ccpRounded (leftTop.x, leftTop.y - m_pGameContext->getFontHeightNormal() - padding * 3);
    m_rectDestination = ccpRounded (rightTop.x, rightTop.y);
    
    m_borderOrigin = ccp (m_rectOrigin.x, m_rectOrigin.y - borderThickness);
    m_borderDestination = ccp (m_rectDestination.x, m_rectOrigin.y);
    
    CCSize levelTextLabelSize = levelTextLabel->getContentSize();
    levelTextLabel->setPosition(ccp(m_rectOrigin.x + padding*2 + levelTextLabelSize.width / 2, m_rectOrigin.y + padding + m_pGameContext->getFontHeightNormal() / 2));
        
    m_levelRightPosX = levelTextLabel->getPositionX() + levelTextLabelSize.width / 2 + padding + m_levelLabel->getContentSize().width;
    m_scoreRightPosX = m_rectDestination.x - padding*2;
        
    CCSize scoreLabelSize = m_scoreLabel->getContentSize();
    scoreTextLabel->setPosition(ccp ( 
      m_scoreRightPosX - m_scoreLabel->getContentSize().width - padding - scoreTextLabel->getContentSize().width / 2
      , levelTextLabel->getPositionY()));

    m_levelLabel->setString("0");
    m_levelLabel->setPosition(ccp(m_levelRightPosX - m_levelLabel->getContentSize().width / 2, levelTextLabel->getPositionY()));
    
    m_scoreLabel->setString("0");
    m_scoreLabel->setPosition(ccp(m_scoreRightPosX - m_scoreLabel->getContentSize().width / 2, levelTextLabel->getPositionY()));

    m_rectColor.r = 0;
    m_rectColor.g = 0;
    m_rectColor.b = 0;
    m_rectColor.a = 1;
    m_borderColor.r = .5;
    m_borderColor.g = .5;
    m_borderColor.b = .5;
    m_borderColor.a = 1;

    this->m_isLayoutInitialized = true;
  }
}

void TopBar::setLevel(int level)
{
  char str[5];
  sprintf(str, "%i", level);
  m_levelLabel->setString(str);
  
  // right align
  m_levelLabel->setPositionX(m_levelRightPosX - m_levelLabel->getContentSize().width / 2);
}

void TopBar::setScore(long score)
{
  char str[10];
  sprintf(str, "%i", score);
  m_scoreLabel->setString(str);
  
  // right align
  m_scoreLabel->setPositionX(m_scoreRightPosX - m_scoreLabel->getContentSize().width / 2);
}

void TopBar::draw()
{     
  ccDrawSolidRect(m_rectOrigin, m_rectDestination, m_rectColor);
  ccDrawSolidRect(m_borderOrigin, m_borderDestination, m_borderColor);
}
