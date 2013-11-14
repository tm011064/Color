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
        
    float scale = 1.0f;

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
    float indentLeft = (visibleRect.size.width - this->m_pGameContext->getPanelInnerWidthWide())/2;
    float indentRight = indentLeft + this->m_pGameContext->getPanelInnerWidthWide();
                
    m_playButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "play"
      , m_pGameContext->getDefaultButtonSize()
      , this->m_borderThickness
      , this->m_pGameContext
      , callfuncO_selector(LifeTimeTickerPopup::playCallback)
      , this);    
    float menuButtonPosYTop = m_dialogRectLeftBottom.y + this->m_padding * 5 + m_playButton->getScaledSize().height/2;
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
        
    CCSprite* heartSprite = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("heart_large"));
    heartSprite->setPosition(ccp(indentLeft + heartSprite->getContentSize().width/2, m_dialogRectLeftTop.y - (m_dialogRectLeftTop.y-m_dialogRectLeftBottom.y)/2));
    this->addChild(heartSprite);

    CCLabelBMFont* descriptionLabel;

    descriptionLabel = CCLabelBMFont::create("lifes left\nnext life in", m_pGameContext->getFontNormalPath().c_str());
    descriptionLabel->setScale(m_pGameContext->getFontScale());
    this->addChild(descriptionLabel);
              
    m_deltaNextLifeIncreaseLabel_Separator = CCLabelBMFont::create(":", m_pGameContext->getFontNormalPath().c_str());
    m_deltaNextLifeIncreaseLabel_Separator->setScale(m_pGameContext->getFontScale());
    float separatorWidth = m_deltaNextLifeIncreaseLabel_Separator->getContentSize().width;
    this->addChild(m_deltaNextLifeIncreaseLabel_Separator);

    // determine text vertical positioning
    float availableLength = heartSprite->getContentSize().height;
    float textHeight = 
      descriptionLabel->getContentSize().height*m_pGameContext->getFontScale() // description height
      + m_pGameContext->getFontHeightNormal()*m_pGameContext->getFontScale() // counter height
      + m_pGameContext->getDefaultPadding()*2; // padding
    float topY = heartSprite->getPositionY() + heartSprite->getContentSize().height/2 - (availableLength - (availableLength - textHeight))/2;
    float bottomY = topY - textHeight;
    
    // center horizontal positioning of heart and text
    availableLength = 
        (
            (heartSprite->getPositionX() + heartSprite->getContentSize().width/2) + m_pGameContext->getDefaultPadding()*8
          + descriptionLabel->getContentSize().width*m_pGameContext->getFontScale()
        ) 
        - ( heartSprite->getPositionX() - heartSprite->getContentSize().width/2 );
    heartSprite->setPositionX((visibleRect.size.width - availableLength)/2 + heartSprite->getContentSize().width/2);

    descriptionLabel->setPosition(
      heartSprite->getPositionX() + heartSprite->getContentSize().width/2 + m_pGameContext->getDefaultPadding()*8 + descriptionLabel->getContentSize().width/2*m_pGameContext->getFontScale()
      , topY - descriptionLabel->getContentSize().height/2*m_pGameContext->getFontScale());
    m_deltaNextLifeIncreaseLabel_Separator->setPosition(
      descriptionLabel->getPositionX()
      , bottomY + m_pGameContext->getFontHeightNormal()/2*m_pGameContext->getFontScale());
    
    m_totalLifeLabel = CCLabelBMFont::create("NA", m_pGameContext->getFontLargePath().c_str());
    m_totalLifeLabel->setPosition(heartSprite->getPosition());
    this->addChild(m_totalLifeLabel);

    m_deltaNextLifeIncreaseLabel_M1 = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    m_deltaNextLifeIncreaseLabel_M1->setScale(m_pGameContext->getFontScale());
    m_deltaNextLifeIncreaseLabel_M1->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() - separatorWidth/2 - m_pGameContext->getDefaultPadding()*2 - m_pGameContext->getMaxDigitFontNormalWidth()*1.5*m_pGameContext->getFontScale(), m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
    this->addChild(m_deltaNextLifeIncreaseLabel_M1);
    
    m_deltaNextLifeIncreaseLabel_M2 = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    m_deltaNextLifeIncreaseLabel_M2->setScale(m_pGameContext->getFontScale());
    m_deltaNextLifeIncreaseLabel_M2->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() - separatorWidth/2 - m_pGameContext->getDefaultPadding() - m_pGameContext->getMaxDigitFontNormalWidth()*.5*m_pGameContext->getFontScale(), m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
    this->addChild(m_deltaNextLifeIncreaseLabel_M2);

    m_deltaNextLifeIncreaseLabel_S2 = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    m_deltaNextLifeIncreaseLabel_S2->setScale(m_pGameContext->getFontScale());
    m_deltaNextLifeIncreaseLabel_S2->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() + separatorWidth/2 + m_pGameContext->getDefaultPadding()*2 + m_pGameContext->getMaxDigitFontNormalWidth()*1.5*m_pGameContext->getFontScale(), m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
    this->addChild(m_deltaNextLifeIncreaseLabel_S2);
    
    m_deltaNextLifeIncreaseLabel_S1 = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    m_deltaNextLifeIncreaseLabel_S1->setScale(m_pGameContext->getFontScale());
    m_deltaNextLifeIncreaseLabel_S1->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() + separatorWidth/2 + m_pGameContext->getDefaultPadding() + m_pGameContext->getMaxDigitFontNormalWidth()*.5*m_pGameContext->getFontScale(), m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
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