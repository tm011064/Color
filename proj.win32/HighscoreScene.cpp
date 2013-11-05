#include "HighscoreScene.h"

using namespace cocos2d;

void HighscoreScene::onEnter()
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
    
    LayoutController::addBackground(m_pGameContext, this, -1);
        
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
    float indentLeft = (visibleRect.size.width - this->m_pGameContext->getPanelInnerWidthWide())/2;
    float indentRight = indentLeft + this->m_pGameContext->getPanelInnerWidthWide();

    m_panelRectInnerLeftBottom = ccp( indentLeft + borderThickness, m_panelRectLeftBottom.y + borderThickness );
    m_panelRectInnerRightTop = ccp( indentRight - borderThickness, m_panelRectRightTop.y - borderThickness );

    this->m_textIndentLeft = m_panelRectInnerLeftBottom.x + padding * 3;
    this->m_textIndentRight = m_panelRectInnerRightTop.x - padding * 3;
        
    float posY = round( m_panelRectInnerRightTop.y + verticalSpacingLarge/2 );

    CCLabelBMFont* label = CCLabelBMFont::create("HIGHSCORE", m_pGameContext->getFontLargePath().c_str());
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
        
    GameScore gameScore = m_pGameContext->getGameScore();
        
    char str[256];        

    label = CCLabelBMFont::create("Easy", m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2, posY);
    this->addChild(label);
    sprintf(str, "%i", m_pGameContext->getHighscoreEasy());
    label = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentRight - label->getContentSize().width/2, posY);
    this->addChild(label);

    posY -= round( verticalSpacing );
    label = CCLabelBMFont::create("Normal", m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2, posY);
    this->addChild(label);
    sprintf(str, "%i", m_pGameContext->getHighscoreNormal());
    label = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentRight - label->getContentSize().width/2, posY);
    this->addChild(label);

    posY -= round( verticalSpacing );
    label = CCLabelBMFont::create("Hard", m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2, posY);
    this->addChild(label);
    sprintf(str, "%i", m_pGameContext->getHighscoreHard());
    label = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentRight - label->getContentSize().width/2, posY);
    this->addChild(label);
    
    TextButton* textButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "back"
      , m_pGameContext->getDefaultButtonSize()
      , borderThickness
      , this->m_pGameContext
      , callfuncO_selector(HighscoreScene::showMenuCallback)
      , this);
    textButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    size = textButton->getScaledSize();
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

void HighscoreScene::draw()
{ 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
  ccDrawSolidRect(m_panelRectLeftBottom, m_panelRectRightTop, m_bgDark);
  
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  ccDrawSolidRect(m_panelRectLeftTop, m_separatorTopRight, m_separatorColor);
  ccDrawSolidRect(m_panelRectLeftBottom, m_separatorBottomRight, m_separatorColor);
}

void HighscoreScene::showMenuCallback(CCObject* pSender)
{ 
  NavigationManager::showMainMenu(m_pGameContext, NEW, false, HOME);
}
void HighscoreScene::onBackKeyPressed()
{
  NavigationManager::showMainMenu(m_pGameContext, NEW, false, HOME);
}