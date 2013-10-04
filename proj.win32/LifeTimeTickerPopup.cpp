#include "LifeTimeTickerPopup.h"

LifeTimeTickerPopup* LifeTimeTickerPopup::create(GameContext* gameContext, CCNode* callbackTarget
  , SEL_CallFuncO playCallbackDelegate)
{ 
  LifeTimeTickerPopup* gameScorePopup = new LifeTimeTickerPopup(gameContext, callbackTarget
    , playCallbackDelegate);
  gameScorePopup->autorelease();
  return gameScorePopup;
}

void LifeTimeTickerPopup::onEnter()
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
            
    m_playButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "play"
      , m_pGameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_pGameContext
      , callfuncO_selector(LifeTimeTickerPopup::playCallback)
      , this);    
    float menuButtonPosYTop = m_dialogRectInnerLeftBottom.y + this->m_padding * 5 + m_playButton->getSize().height/2;
    m_playButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    m_playButton->setPosition(center.x, menuButtonPosYTop);
    this->addChild(m_playButton);
        
    m_getLifesButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "get lifes"
      , m_pGameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_pGameContext
      , callfuncO_selector(LifeTimeTickerPopup::getLifesCallback)
      , this);
    m_getLifesButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    m_getLifesButton->setPosition(center.x, menuButtonPosYTop);
    this->addChild(m_getLifesButton);

    // TODO (Roman): do this properly, make four labels and put the numbers into the middle
    m_totalLifeLabel = CCLabelBMFont::create("NA", m_pGameContext->getFontLargePath().c_str());
    m_totalLifeLabel->setPosition(center.x, center.y + m_pGameContext->getFontHeightLarge());
    this->addChild(m_totalLifeLabel);
      
    m_deltaNextLifeIncreaseLabel_Separator = CCLabelBMFont::create(":", m_pGameContext->getFontLargePath().c_str());
    float separatorWidth = m_deltaNextLifeIncreaseLabel_Separator->getContentSize().width;
    m_deltaNextLifeIncreaseLabel_Separator->setPosition(center.x, center.y - m_pGameContext->getFontHeightLarge());
    this->addChild(m_deltaNextLifeIncreaseLabel_Separator);

    m_deltaNextLifeIncreaseLabel_M1 = CCLabelBMFont::create("0", m_pGameContext->getFontLargePath().c_str());
    m_deltaNextLifeIncreaseLabel_M1->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() - separatorWidth/2 - m_pGameContext->getDefaultPadding()*2 - m_pGameContext->getMaxDigitFontLargeWidth()*1.5, m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
    this->addChild(m_deltaNextLifeIncreaseLabel_M1);
    
    m_deltaNextLifeIncreaseLabel_M2 = CCLabelBMFont::create("0", m_pGameContext->getFontLargePath().c_str());
    m_deltaNextLifeIncreaseLabel_M2->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() - separatorWidth/2 - m_pGameContext->getDefaultPadding() - m_pGameContext->getMaxDigitFontLargeWidth()*.5, m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
    this->addChild(m_deltaNextLifeIncreaseLabel_M2);

    m_deltaNextLifeIncreaseLabel_S2 = CCLabelBMFont::create("0", m_pGameContext->getFontLargePath().c_str());
    m_deltaNextLifeIncreaseLabel_S2->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() + separatorWidth/2 + m_pGameContext->getDefaultPadding()*2 + m_pGameContext->getMaxDigitFontLargeWidth()*1.5, m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
    this->addChild(m_deltaNextLifeIncreaseLabel_S2);
    
    m_deltaNextLifeIncreaseLabel_S1 = CCLabelBMFont::create("0", m_pGameContext->getFontLargePath().c_str());
    m_deltaNextLifeIncreaseLabel_S1->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() + separatorWidth/2 + m_pGameContext->getDefaultPadding() + m_pGameContext->getMaxDigitFontLargeWidth()*.5, m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
    this->addChild(m_deltaNextLifeIncreaseLabel_S1);

    updateLifeDisplay(.0f);
    this->schedule(schedule_selector(LifeTimeTickerPopup::updateLifeDisplay), 1);    

    m_bgLight.a = .6f; 
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

void LifeTimeTickerPopup::updateLifeDisplay(float dt)
{
  if ( !this->m_bVisible )
  {
    if ( m_playButton->isVisible() )
      m_playButton->setVisible(false);
    if ( m_getLifesButton->isVisible() )
      m_getLifesButton->setVisible(false);

    return;
  }
  LifeInfo lifeInfo = this->m_pGameContext->refreshTotalLifesCount();

  if (lifeInfo.totalLifes == 0)
  {
    m_playButton->setVisible(false);
    m_getLifesButton->setVisible(true);
  }
  else
  {
    m_playButton->setVisible(true);
    m_getLifesButton->setVisible(false);
  }

  this->m_totalLifeLabel->setString( UtilityHelper::convertToString( lifeInfo.totalLifes ).c_str() );
  
  int totalMinutes = (int)(lifeInfo.deltaToNextIncreaseInSeconds / 60);
  int totalSeconds = (int)(lifeInfo.deltaToNextIncreaseInSeconds - totalMinutes * 60);

  int m1 = totalMinutes / 10;
  int s1 = totalSeconds / 10;
  
  this->m_deltaNextLifeIncreaseLabel_M1->setString( this->m_pGameContext->getDigitFontNormal( m1 ).c_str() );
  this->m_deltaNextLifeIncreaseLabel_M2->setString( this->m_pGameContext->getDigitFontNormal( totalMinutes - m1*10 ).c_str() );
  
  this->m_deltaNextLifeIncreaseLabel_S1->setString( this->m_pGameContext->getDigitFontNormal( s1 ).c_str() );
  this->m_deltaNextLifeIncreaseLabel_S2->setString( this->m_pGameContext->getDigitFontNormal( totalSeconds - s1*10 ).c_str() );  
}

void LifeTimeTickerPopup::show()
{
  ModalControl::show();

  // update here once we are visible...
  updateLifeDisplay(.0f);
}

void LifeTimeTickerPopup::hide()
{
  ModalControl::hide();

  // update here, since we are hidden this will disable the buttons
  updateLifeDisplay(.0f);
}

void LifeTimeTickerPopup::draw()
{ 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  ccDrawSolidRect(m_dialogRectLeftTop, m_visibleRectRightTop, m_bgLight);
  ccDrawSolidRect(m_dialogRectLeftBottom, m_dialogRectRightTop, m_bgDark);
  ccDrawSolidRect(m_visibleRectLeftBottom, m_dialogRectRightBottom, m_bgLight);

  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  ccDrawSolidRect(m_dialogRectLeftTop, m_separatorTopRight, m_separatorColor);
  ccDrawSolidRect(m_dialogRectLeftBottom, m_separatorBottomRight, m_separatorColor);
}

void LifeTimeTickerPopup::playCallback(CCObject* sender)
{  
  if(m_pTarget != 0 && this->m_fnpPlayCallbackDelegate != 0)
    (m_pTarget->*this->m_fnpPlayCallbackDelegate)(this);
}

void LifeTimeTickerPopup::getLifesCallback(CCObject* sender)
{
  // TODO (Roman): remove this!!!
  this->m_pGameContext->setTotalLifes( MAX_LIFES );
}