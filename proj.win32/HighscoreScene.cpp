#include "HighscoreScene.h"

using namespace cocos2d;

void HighscoreScene::onEnter()
{
  CCScene::onEnter();

  if (!this->m_isInitialized)
  {  
    this->m_isInitialized = true;    

    CCPoint center = VisibleRect::center();
    CCRect rect = VisibleRect::getVisibleRect();

    this->m_padding = m_gameContext->getDefaultPadding();
    float verticalSpacing = m_gameContext->getFontHeightNormal() + m_padding;

    float leftX, rightX;
    float topY, bottomY;

    leftX = rect.size.width * .15;
    rightX = rect.size.width - leftX;
    topY = rect.size.height * .7;

    GameScore gameScore = m_gameContext->getGameScore();
        
    char str[256];        

    CCLabelBMFont* label = CCLabelBMFont::create("Easy", m_gameContext->getFontNormalPath().c_str());
    label->setPosition(leftX + m_padding + label->getContentSize().width/2, topY - verticalSpacing);
    this->addChild(label);
    sprintf(str, "%i", m_gameContext->getHighscoreEasy());
    label = CCLabelBMFont::create(str, m_gameContext->getFontNormalPath().c_str());
    label->setPosition(rightX - label->getContentSize().width/2, topY - verticalSpacing);
    this->addChild(label);

    label = CCLabelBMFont::create("Normal", m_gameContext->getFontNormalPath().c_str());
    label->setPosition(leftX + m_padding + label->getContentSize().width/2, topY - verticalSpacing * 2);
    this->addChild(label);
    sprintf(str, "%i", m_gameContext->getHighscoreNormal());
    label = CCLabelBMFont::create(str, m_gameContext->getFontNormalPath().c_str());
    label->setPosition(rightX - label->getContentSize().width/2, topY - verticalSpacing * 2);
    this->addChild(label);

    label = CCLabelBMFont::create("Hard", m_gameContext->getFontNormalPath().c_str());
    label->setPosition(leftX + m_padding + label->getContentSize().width/2, topY - verticalSpacing * 3);
    this->addChild(label);
    sprintf(str, "%i", m_gameContext->getHighscoreHard());
    label = CCLabelBMFont::create(str, m_gameContext->getFontNormalPath().c_str());
    label->setPosition(rightX - label->getContentSize().width/2, topY - verticalSpacing * 3);
    this->addChild(label);
    
    bottomY = label->getPositionY() - label->getContentSize().height / 2;
  }
}
void HighscoreScene::showMenuCallback(CCObject* pSender)
{ 
  NavigationManager::showScene(MENU_SCENE, m_gameContext, NEW);
}
void HighscoreScene::onBackKeyPressed()
{
  NavigationManager::showScene(MENU_SCENE, m_gameContext, NEW);
}