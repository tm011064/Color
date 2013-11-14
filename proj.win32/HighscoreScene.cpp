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
    
    posY = round( m_panelRectLeftTop.y );    
        
    GameScore gameScore = m_pGameContext->getGameScore();
        
    TableColumn col1, col2, col3, col23;

    float factorThreshold = .0418f;
    float factor = m_pGameContext->getFontHeightNormal()*m_pGameContext->getFontScale() / visibleRect.size.height;
    if ( factor > factorThreshold )
    {
      factor = m_pGameContext->getFontScale();
      m_pGameContext->setFontScale(factorThreshold * visibleRect.size.height/m_pGameContext->getFontHeightNormal());
    }
    else
    {
      factor = m_pGameContext->getFontScale();
    }

    float availableWidth = indentRight - indentLeft;
    float cellHeight = m_pGameContext->getFontHeightNormal()*m_pGameContext->getFontScale() + m_pGameContext->getDefaultPadding()*2*m_pGameContext->getFontScale();
    float defaultHorizontalPadding = m_pGameContext->getDefaultPadding()*4*m_pGameContext->getFontScale();

    ccColor4F headerTopLeftBackgroundColor = { .5f, .5f, .5f, .0f };
    ccColor4F headerBackgroundColor = { .4f, .4f, .4f, 1.0f };
    ccColor4F headerBorderColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    ccColor3B headerForegroundColor = { 26.0f, 26.0f, 26.0f };
    ccColor4F cellBackgroundColor = { .1f, .1f, .1f, 1.0f };
    ccColor4F cellBorderColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    ccColor3B cellForegroundColor = { 255.0f, 255.0f, 255.0f };


    Table* table = Table::create(this->m_pGameContext);
    table->beginLayoutUpdate();

    col1.headerStyle.backgroundColor = headerTopLeftBackgroundColor;
    col1.headerStyle.foregroundColor = cellForegroundColor;
    col1.headerStyle.isBorderVisible = false;
    col1.headerStyle.fontNamePath = m_pGameContext->getFontNormalPath();
    col1.headerStyle.horizontalTextAlignment = LEFT;
    col1.headerStyle.verticalTextAlignment = TOP;
    col1.headerStyle.padding.left = .0f;
    col1.headerStyle.padding.top = .0f;
    col1.headerStyle.size.setSize(availableWidth*.39f, cellHeight);
    
    col1.cellStyle.backgroundColor = cellBackgroundColor;
    col1.cellStyle.foregroundColor = cellForegroundColor;
    col1.cellStyle.isBorderVisible = true;
    col1.cellStyle.borderThickness.left = m_pGameContext->getDefaultBorderThickness();
    col1.cellStyle.borderThickness.top = m_pGameContext->getDefaultBorderThickness();
    col1.cellStyle.borderThickness.right = m_pGameContext->getDefaultBorderThickness();
    col1.cellStyle.borderThickness.bottom = m_pGameContext->getDefaultBorderThickness();
    col1.cellStyle.borderColor = cellBorderColor;
    col1.cellStyle.fontNamePath = m_pGameContext->getFontNormalPath();
    col1.cellStyle.horizontalTextAlignment = RIGHT;
    col1.cellStyle.verticalTextAlignment = TOP;
    col1.cellStyle.padding.right = -defaultHorizontalPadding;
    col1.cellStyle.padding.top = -m_pGameContext->getDefaultPadding()*m_pGameContext->getFontScale();
    col1.cellStyle.size.setSize(availableWidth*.39f, cellHeight);
    
    table->addColumn(col1);
    
    col2.headerStyle.backgroundColor = headerBackgroundColor;
    col2.headerStyle.foregroundColor = headerForegroundColor;
    col2.headerStyle.isBorderVisible = true;
    col2.headerStyle.borderThickness.left = m_pGameContext->getDefaultBorderThickness();
    col2.headerStyle.borderThickness.top = m_pGameContext->getDefaultBorderThickness();
    col2.headerStyle.borderThickness.right = m_pGameContext->getDefaultBorderThickness();
    col2.headerStyle.borderThickness.bottom = m_pGameContext->getDefaultBorderThickness();
    col2.headerStyle.borderColor = headerBorderColor;
    col2.headerStyle.fontNamePath = m_pGameContext->getFontNormalPath();
    col2.headerStyle.horizontalTextAlignment = RIGHT;
    col2.headerStyle.verticalTextAlignment = TOP;
    col2.headerStyle.padding.right = -defaultHorizontalPadding;
    col2.headerStyle.padding.top = -m_pGameContext->getDefaultPadding()*m_pGameContext->getFontScale();
    col2.headerStyle.size.setSize(availableWidth*.39f, cellHeight);
    
    col2.cellStyle.backgroundColor = cellBackgroundColor;
    col2.cellStyle.foregroundColor = cellForegroundColor;
    col2.cellStyle.isBorderVisible = true;
    col2.cellStyle.borderThickness.left = m_pGameContext->getDefaultBorderThickness();
    col2.cellStyle.borderThickness.top = m_pGameContext->getDefaultBorderThickness();
    col2.cellStyle.borderThickness.right = m_pGameContext->getDefaultBorderThickness();
    col2.cellStyle.borderThickness.bottom = m_pGameContext->getDefaultBorderThickness();
    col2.cellStyle.borderColor = cellBorderColor;
    col2.cellStyle.fontNamePath = m_pGameContext->getFontNormalPath();
    col2.cellStyle.horizontalTextAlignment = RIGHT;
    col2.cellStyle.verticalTextAlignment = TOP;
    col2.cellStyle.padding.right = -defaultHorizontalPadding;
    col2.cellStyle.padding.top = -m_pGameContext->getDefaultPadding()*m_pGameContext->getFontScale();
    col2.cellStyle.size.setSize(availableWidth*.39f, cellHeight);
    
    table->addColumn(col2);
    
    col3.headerStyle.backgroundColor = headerBackgroundColor;
    col3.headerStyle.foregroundColor = headerForegroundColor;
    col3.headerStyle.isBorderVisible = true;
    col3.headerStyle.borderThickness.left = m_pGameContext->getDefaultBorderThickness();
    col3.headerStyle.borderThickness.top = m_pGameContext->getDefaultBorderThickness();
    col3.headerStyle.borderThickness.right = m_pGameContext->getDefaultBorderThickness();
    col3.headerStyle.borderThickness.bottom = m_pGameContext->getDefaultBorderThickness();
    col3.headerStyle.borderColor = headerBorderColor;
    col3.headerStyle.fontNamePath = m_pGameContext->getFontNormalPath();
    col3.headerStyle.horizontalTextAlignment = RIGHT;
    col3.headerStyle.verticalTextAlignment = TOP;
    col3.headerStyle.padding.right = -defaultHorizontalPadding;
    col3.headerStyle.padding.top = -m_pGameContext->getDefaultPadding()*m_pGameContext->getFontScale();
    col3.headerStyle.size.setSize(availableWidth*.22f, cellHeight);
    
    col3.cellStyle.backgroundColor = cellBackgroundColor;
    col3.cellStyle.foregroundColor = cellForegroundColor;
    col3.cellStyle.isBorderVisible = true;
    col3.cellStyle.borderThickness.left = m_pGameContext->getDefaultBorderThickness();
    col3.cellStyle.borderThickness.top = m_pGameContext->getDefaultBorderThickness();
    col3.cellStyle.borderThickness.right = m_pGameContext->getDefaultBorderThickness();
    col3.cellStyle.borderThickness.bottom = m_pGameContext->getDefaultBorderThickness();
    col3.cellStyle.borderColor = cellBorderColor;
    col3.cellStyle.fontNamePath = m_pGameContext->getFontNormalPath();
    col3.cellStyle.horizontalTextAlignment = RIGHT;
    col3.cellStyle.verticalTextAlignment = TOP;
    col3.cellStyle.padding.right = -defaultHorizontalPadding;
    col3.cellStyle.padding.top = -m_pGameContext->getDefaultPadding()*m_pGameContext->getFontScale();
    col3.cellStyle.size.setSize(availableWidth*.22f, cellHeight);
    
    table->addColumn(col3);

    std::vector< std::string > vals;

    vals.clear();
    vals.push_back("Memory");
    vals.push_back("Pts");
    vals.push_back("Rep");
    table->addHeader(vals);
    vals.clear();
    vals.push_back("2B");
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreMemory2b()));
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreMemory2bTotal()));
    table->addRow(vals);
    vals.clear();
    vals.push_back("3B");
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreMemory3b()));
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreMemory3bTotal()));
    table->addRow(vals);
    vals.clear();
    vals.push_back("4B");
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreMemory4b()));
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreMemory4bTotal()));
    table->addRow(vals);

    table->endLayoutUpdate();

    posY -= m_pGameContext->getOuterPanelPadding()*2*m_pGameContext->getFontScale();
    table->setPosition(center.x - table->getSize().width/2, posY);
    this->addChild(table);
    posY -= table->getSize().height;

    table = Table::create(this->m_pGameContext);
    table->beginLayoutUpdate();

    table->addColumn(col1);
    table->addColumn(col2);
    table->addColumn(col3);

    vals.clear();
    vals.push_back("Speed");
    vals.push_back("Pts");
    vals.push_back("Rep");
    table->addHeader(vals);
    vals.clear();
    vals.push_back("2B");
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreSpeed2b()));
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreSpeed2bTotal()));
    table->addRow(vals);
    vals.clear();
    vals.push_back("3B");
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreSpeed3b()));
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreSpeed3bTotal()));
    table->addRow(vals);
    vals.clear();
    vals.push_back("4B");
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreSpeed4b()));
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreSpeed4bTotal()));
    table->addRow(vals);

    table->endLayoutUpdate();

    posY -= m_pGameContext->getOuterPanelPadding()*2*m_pGameContext->getFontScale();
    table->setPosition(center.x - table->getSize().width/2, posY);
    this->addChild(table);
    posY -= table->getSize().height;


    
    table = Table::create(this->m_pGameContext);
    table->beginLayoutUpdate();

    table->addColumn(col1);
    
    col23.headerStyle.backgroundColor = headerBackgroundColor;
    col23.headerStyle.foregroundColor = headerForegroundColor;
    col23.headerStyle.isBorderVisible = true;
    col23.headerStyle.borderThickness.left = m_pGameContext->getDefaultBorderThickness();
    col23.headerStyle.borderThickness.top = m_pGameContext->getDefaultBorderThickness();
    col23.headerStyle.borderThickness.right = m_pGameContext->getDefaultBorderThickness();
    col23.headerStyle.borderThickness.bottom = m_pGameContext->getDefaultBorderThickness();
    col23.headerStyle.borderColor = headerBorderColor;
    col23.headerStyle.fontNamePath = m_pGameContext->getFontNormalPath();
    col23.headerStyle.horizontalTextAlignment = RIGHT;
    col23.headerStyle.verticalTextAlignment = TOP;
    col23.headerStyle.padding.right = -defaultHorizontalPadding;
    col23.headerStyle.padding.top = -m_pGameContext->getDefaultPadding()*m_pGameContext->getFontScale();
    col23.headerStyle.size.setSize(availableWidth*.61f, cellHeight);
    
    col23.cellStyle.backgroundColor = cellBackgroundColor;
    col23.cellStyle.foregroundColor = cellForegroundColor;
    col23.cellStyle.isBorderVisible = true;
    col23.cellStyle.borderThickness.left = m_pGameContext->getDefaultBorderThickness();
    col23.cellStyle.borderThickness.top = m_pGameContext->getDefaultBorderThickness();
    col23.cellStyle.borderThickness.right = m_pGameContext->getDefaultBorderThickness();
    col23.cellStyle.borderThickness.bottom = m_pGameContext->getDefaultBorderThickness();
    col23.cellStyle.borderColor = cellBorderColor;
    col23.cellStyle.fontNamePath = m_pGameContext->getFontNormalPath();
    col23.cellStyle.horizontalTextAlignment = RIGHT;
    col23.cellStyle.verticalTextAlignment = TOP;
    col23.cellStyle.padding.right = -defaultHorizontalPadding;
    col23.cellStyle.padding.top = -m_pGameContext->getDefaultPadding()*m_pGameContext->getFontScale();
    col23.cellStyle.size.setSize(availableWidth*.61f, cellHeight);
    
    table->addColumn(col23);

    vals.clear();
    vals.push_back("Misc");
    vals.push_back("Pts");
    table->addHeader(vals);
    vals.clear();
    vals.push_back("Rhythm");
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreRhythm()) + " / 100");
    table->addRow(vals);
    vals.clear();
    vals.push_back("Balance");
    vals.push_back(UtilityHelper::convertToString(m_pGameContext->getHighscoreBalance()) + " / 100");
    table->addRow(vals);

    table->endLayoutUpdate();

    posY -= m_pGameContext->getOuterPanelPadding()*2*m_pGameContext->getFontScale();
    table->setPosition(center.x - table->getSize().width/2, posY);
    this->addChild(table);
    posY -= table->getSize().height;
    
    m_pGameContext->setFontScale(factor);


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