#include "GameScorePopup.h"

GameScorePopup* GameScorePopup::create(GameContext* gameContext, std::string headerText
  , SEL_CallFuncO playAgainCallbackDelegate
  , SEL_CallFuncO mainMenuCallbackDelegate
  , CCNode* callbackTarget, GameScorePopupType gameScorePopupType)
{ 
  GameScorePopup* gameScorePopup = new GameScorePopup(gameContext, headerText
    , playAgainCallbackDelegate, mainMenuCallbackDelegate, callbackTarget, gameScorePopupType);
  gameScorePopup->autorelease();
  return gameScorePopup;
}

void GameScorePopup::onEnter()
{
  ModalControl::onEnter();

  if (!this->m_isLayoutInitialized)
  {
    CCPoint center = VisibleRect::center();
        
    CCRect visibleRect = VisibleRect::getVisibleRect();
    m_visibleRectLeftBottom = VisibleRect::leftBottom();
    m_visibleRectRightTop = VisibleRect::rightTop();
        
    GameScore gameScore = m_pGameContext->getGameScore();
        
    this->m_padding = m_pGameContext->getDefaultPadding();
    this->m_borderThickness = m_pGameContext->getDefaultBorderThickness();

    float verticalSpacing = m_pGameContext->getFontHeightNormal() + m_padding;
    float verticalSpacingLarge = m_pGameContext->getFontHeightLarge() + m_padding*3;
            
    m_dialogRectLeftTop = ccpRounded ( 0, m_visibleRectRightTop.y * .825);
    m_dialogRectLeftBottom = ccpRounded ( 0, m_visibleRectRightTop.y * .26 );
    m_dialogRectRightTop = ccp ( m_visibleRectRightTop.x, m_dialogRectLeftTop.y);
    m_dialogRectRightBottom = ccp ( m_visibleRectRightTop.x, m_dialogRectLeftBottom.y);

    m_separatorTopRight = ccp ( m_visibleRectRightTop.x, m_dialogRectRightTop.y + m_borderThickness);
    m_separatorBottomRight = ccp ( m_visibleRectRightTop.x, m_dialogRectRightBottom.y - m_borderThickness);
      
    // now we have the border thickness and padding, so we can set the boundaries 
    float indentLeft = round ( m_visibleRectLeftBottom.x + (visibleRect.size.width * .15) );
    float indentRight = round ( m_visibleRectLeftBottom.x + (visibleRect.size.width * .85) ) ;
    m_dialogRectInnerLeftBottom = ccp( indentLeft + this->m_borderThickness, m_dialogRectLeftBottom.y + this->m_borderThickness );
    m_dialogRectInnerRightTop = ccp( indentRight - this->m_borderThickness, m_dialogRectRightTop.y - this->m_borderThickness );

    this->m_textIndentLeft = m_dialogRectInnerLeftBottom.x + m_padding * 3;
    this->m_textIndentRight = m_dialogRectInnerRightTop.x - m_padding * 3;
    
    float posY = m_dialogRectInnerRightTop.y - verticalSpacingLarge/2 - this->m_padding * 4;
    m_headerTextLabel = CCLabelBMFont::create(m_headerText.c_str(), m_pGameContext->getFontLargePath().c_str());
    m_headerTextLabel->setPosition(center.x, posY );
    this->addChild(m_headerTextLabel);
    posY -= m_pGameContext->getFontHeightLarge()/2 ;//+ verticalSpacingLarge/2;
    
    TextButton* textButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "menu"
      , m_pGameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_pGameContext
      , callfuncO_selector(GameScorePopup::mainMenuCallback)
      , this);
    textButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    textButton->setPosition(this->m_textIndentLeft + textButton->getSize().width/2
      , m_dialogRectInnerLeftBottom.y + this->m_padding * 5 + textButton->getSize().height/2);
    this->addChild(textButton);
    
    textButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "retry"
      , m_pGameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_pGameContext
      , callfuncO_selector(GameScorePopup::playAgainCallback)
      , this);
    textButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    textButton->setPosition(this->m_textIndentRight - textButton->getSize().width/2
      , m_dialogRectInnerLeftBottom.y + this->m_padding * 5 + textButton->getSize().height/2);
    this->addChild(textButton);
    
    m_separatorColor.a = 1; 
    m_separatorColor.r = 1; 
    m_separatorColor.g = 1; 
    m_separatorColor.b = 1; 
    switch (this->m_gameScorePopupType)
    {
    case GSPTYPE_POINTS:
      m_gameScorePanel = GameScorePointsPanel::create(this->m_pGameContext
        , this->m_textIndentRight - this->m_textIndentLeft, m_separatorColor);
      this->m_gameScorePanel->setPosition(center.x, posY - ( posY - textButton->getPositionY() - textButton->getSize().height/2 )/2);
      this->addChild(m_gameScorePanel);
      break;

    case GSPTYPE_TIME_INTERVALS:
      m_gameScorePanel = GameScoreTimePanel::create(this->m_pGameContext
        , this->m_textIndentRight - this->m_textIndentLeft, m_separatorColor);
      this->m_gameScorePanel->setPosition(center.x, posY - ( posY - textButton->getPositionY() - textButton->getSize().height/2 )/2);
      this->addChild(m_gameScorePanel);
      break;
    }


    m_bgLight.a = .6f; 
    m_bgLight.r = 0; 
    m_bgLight.g = 0; 
    m_bgLight.b = 0;
    m_bgDark.a = .8f; 
    m_bgDark.r = 0; 
    m_bgDark.g = 0; 
    m_bgDark.b = 0;
  }
}

void GameScorePopup::setHeaderText(std::string text)
{
  this->m_headerTextLabel->setString(text.c_str());
}

void GameScorePopup::show()
{
  ModalControl::show();
  this->m_gameScorePanel->show();
}

void GameScorePopup::draw()
{ 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  ccDrawSolidRect(m_dialogRectLeftTop, m_visibleRectRightTop, m_bgLight);
  ccDrawSolidRect(m_dialogRectLeftBottom, m_dialogRectRightTop, m_bgDark);
  ccDrawSolidRect(m_visibleRectLeftBottom, m_dialogRectRightBottom, m_bgLight);

  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  ccDrawSolidRect(m_dialogRectLeftTop, m_separatorTopRight, m_separatorColor);
  ccDrawSolidRect(m_dialogRectLeftBottom, m_separatorBottomRight, m_separatorColor);
}

void GameScorePopup::playAgainCallback(CCObject* pSender)
{
  if(m_pTarget != 0 && this->m_fnpPlayAgainCallbackDelegate != 0)
      (m_pTarget->*this->m_fnpPlayAgainCallbackDelegate)(this);
}
void GameScorePopup::mainMenuCallback(CCObject* pSender)
{  
  if(m_pTarget != 0 && this->m_fnpMainMenuCallbackDelegate != 0)
      (m_pTarget->*this->m_fnpMainMenuCallbackDelegate)(this);
}