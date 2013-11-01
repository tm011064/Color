#include "DescriptionPopup.h"
#include "LayoutController.h"

DescriptionPopup* DescriptionPopup::create(GameContext* gameContext
    , SEL_CallFuncO closeCallbackDelegate
    , CCNode* callbackTarget, ChallengePointScoreDefinition challengePointScoreDefinition)
{
  DescriptionPopup* descriptionPopup = new DescriptionPopup(gameContext, closeCallbackDelegate
    , callbackTarget, challengePointScoreDefinition);

  descriptionPopup->autorelease();

  return descriptionPopup;
}

void DescriptionPopup::onEnter()
{
  ModalControl::onEnter();

  if (!this->m_isLayoutInitialized)
  {
    CCPoint center = VisibleRect::center();
    CCRect visibleRect = VisibleRect::getVisibleRect();
    
    CCSize guaranteedVisibleSize = m_pGameContext->getGuaranteedVisibleSize();
    CCRect guaranteedVisibleRect = CCRectMake(
      visibleRect.origin.x + (visibleRect.size.width - guaranteedVisibleSize.width)/2
      , visibleRect.origin.y + (visibleRect.size.height - guaranteedVisibleSize.height)/2
      , guaranteedVisibleSize.width
      , guaranteedVisibleSize.height);
    
    m_descriptionBoxLeftBottom.setPoint(
      guaranteedVisibleRect.origin.x + m_pGameContext->getDefaultPadding()
      , guaranteedVisibleRect.origin.y + m_pGameContext->getDefaultPadding());
    
    m_headerBoxRightTop.setPoint(
      guaranteedVisibleRect.getMaxX() - m_pGameContext->getDefaultPadding()
      , guaranteedVisibleRect.getMaxY() - m_pGameContext->getDefaultPadding());

    CCSize descriptionBoxSize = CCSizeMake( 
      m_headerBoxRightTop.x - m_descriptionBoxLeftBottom.x
      , m_headerBoxRightTop.y - m_descriptionBoxLeftBottom.y );

    m_descriptionBoxRightTop.setPoint(
      m_headerBoxRightTop.x
      , m_descriptionBoxLeftBottom.y + round(descriptionBoxSize.height * .68));
    
    m_scoreBoxLeftBottom.setPoint(
      m_descriptionBoxLeftBottom.x
      , m_descriptionBoxRightTop.y );

    m_scoreBoxRightTop.setPoint(
      m_headerBoxRightTop.x
      , m_descriptionBoxRightTop.y + round(descriptionBoxSize.height * .08));
    
    m_headerBoxLeftBottom.setPoint(
      m_descriptionBoxLeftBottom.x
      , m_scoreBoxRightTop.y );

    m_borderLeftRightTop.setPoint(
      m_descriptionBoxLeftBottom.x + m_pGameContext->getDefaultBorderThickness()
      , m_headerBoxRightTop.y );
    
    m_borderBottomRightTop.setPoint(
      m_headerBoxRightTop.x
      , m_descriptionBoxLeftBottom.y + m_pGameContext->getDefaultBorderThickness());
    
    m_borderRightLeftBottom.setPoint(
      m_headerBoxRightTop.x - m_pGameContext->getDefaultBorderThickness()
      , m_descriptionBoxLeftBottom.y);
    
    m_borderTopLeftBottom.setPoint(
      m_descriptionBoxLeftBottom.x
      , m_headerBoxRightTop.y - m_pGameContext->getDefaultBorderThickness());
    
    m_lowerSeparatorRightTop.setPoint(
      m_headerBoxRightTop.x
      , m_scoreBoxLeftBottom.y + m_pGameContext->getDefaultBorderThickness());
    
    m_upperSeparatorRightTop.setPoint(
      m_headerBoxRightTop.x
      , m_headerBoxLeftBottom.y + m_pGameContext->getDefaultBorderThickness());
    
    m_dialogBorderColor.r = 1.0f;
    m_dialogBorderColor.g = 1.0f;
    m_dialogBorderColor.b = 1.0f;
    m_dialogBorderColor.a = 1.0f;
    
    m_backgroundColor.r = 0.0f;
    m_backgroundColor.g = 0.0f;
    m_backgroundColor.b = 0.0f;
    m_backgroundColor.a = 0.2f;
      
    m_targetBackgroundColor.r = 0.1f;
    m_targetBackgroundColor.g = 0.1f;
    m_targetBackgroundColor.b = 0.1f;
    m_targetBackgroundColor.a = 0.2f;

    std::string headerText, targetScoreText, descriptionText, loadingIconFrameName;
    switch ( m_challengePointScoreDefinition.challengeSceneType )
    {
      case REACH_LEVEL: 
        headerText = "MEMORY\nCHALLENGE";
        loadingIconFrameName = "loading_icon_memory";
        targetScoreText = UtilityHelper::convertToString(m_challengePointScoreDefinition.levelToReach) + " Blinks";
        descriptionText = "Try to reapeat the\nbutton blinks in\nsequence.\nThe quicker you are, the\nmore stars you will\nget.";
        m_descriptionBackgroundColor.r = 126.0f / 255.0f;
        m_descriptionBackgroundColor.g = 137.0f / 255.0f;
        m_descriptionBackgroundColor.b = 89.0f / 255.0f;
        m_descriptionBackgroundColor.a = 0.2f;
        break;
      case REPEAT_ONE_OFF: 
        headerText = "SPEED\nCHALLENGE";
        loadingIconFrameName = "loading_icon_speed";
        targetScoreText = UtilityHelper::convertToString(m_challengePointScoreDefinition.levelToReach) + " Blinks";
        descriptionText = "Here you have to be\nvery quick. You will see\nthe sequence only once,\nso try to keep track of\nall those blinks!\nThe quicker you are,\nthe more points you\nwill receive.";
        m_descriptionBackgroundColor.r = 90.0f / 255.0f;
        m_descriptionBackgroundColor.g = 59.0f / 255.0f;
        m_descriptionBackgroundColor.b = 0.0f / 255.0f;
        m_descriptionBackgroundColor.a = 0.2f;
        break;
      case EXACT_LENGTH: 
        headerText = "BALANCE\nCHALLENGE";
        loadingIconFrameName = "loading_icon_balance";
        targetScoreText = UtilityHelper::convertToString((int)(m_challengePointScoreDefinition.minimumTotalTimePercentageForOneStar*100)) + " / 100 Points";
        descriptionText = "Listen closely and try\nto press the buttons as\nlong as they are shown.\nAlso pay attention to\ngaps between blinks,\nmore accuract means\nmore points!";
        m_descriptionBackgroundColor.r = 110.0f / 255.0f;
        m_descriptionBackgroundColor.g = 36.0f / 255.0f;
        m_descriptionBackgroundColor.b = 5.0f / 255.0f;
        m_descriptionBackgroundColor.a = 0.2f;
        break;
      case RHYTHM:
        headerText = "RHYTHM\nCHALLENGE";
        loadingIconFrameName = "loading_icon_rhythm";
        targetScoreText = UtilityHelper::convertToString((int)(m_challengePointScoreDefinition.minimumTotalTimePercentageForOneStar*100)) + " / 100 Points";
        descriptionText = "At this challenge, you\nhave to get the rhythm\nright.\nRepeat the beat as\nclosely as you can.\nAccuracy is key here!";
        m_descriptionBackgroundColor.r = 49.0f / 255.0f;
        m_descriptionBackgroundColor.g = 123.0f / 255.0f;
        m_descriptionBackgroundColor.b = 145.0f / 255.0f;
        m_descriptionBackgroundColor.a = 0.2f;
        break;
    }
    
    LayoutController::AddBackground(m_pGameContext, this, -1);
        
    CCLabelBMFont* label = CCLabelBMFont::create(headerText.c_str(), m_pGameContext->getFontLargePath().c_str());
    label->setPosition(ccpRounded(
      m_borderRightLeftBottom.x - m_pGameContext->getDefaultPadding()*6 - label->getContentSize().width/2
      , m_headerBoxLeftBottom.y + (m_headerBoxRightTop.y - m_headerBoxLeftBottom.y)/2));
    this->addChild(label);
    
    CCSprite* sprite = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile(loadingIconFrameName));
    sprite->setScale((m_headerBoxRightTop.y - m_headerBoxLeftBottom.y)/sprite->getContentSize().height);
    sprite->setPosition(ccpRounded(
      m_headerBoxLeftBottom.x + sprite->getContentSize().width/2 * sprite->getScale()
      , m_headerBoxLeftBottom.y + (m_headerBoxRightTop.y - m_headerBoxLeftBottom.y)/2));
    this->addChild(sprite);

    label = CCLabelBMFont::create("Target:", m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(
      m_borderLeftRightTop.x + m_pGameContext->getDefaultPadding()*4 + label->getContentSize().width/2
      , m_lowerSeparatorRightTop.y + (m_headerBoxLeftBottom.y - m_lowerSeparatorRightTop.y)/2);
    this->addChild(label);
    
    label = CCLabelBMFont::create(targetScoreText.c_str(), m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(
      m_borderRightLeftBottom.x - m_pGameContext->getDefaultPadding()*4 - label->getContentSize().width/2
      , m_lowerSeparatorRightTop.y + (m_headerBoxLeftBottom.y - m_lowerSeparatorRightTop.y)/2);
    this->addChild(label);
    
    label = CCLabelBMFont::create(descriptionText.c_str(), m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(
      m_borderLeftRightTop.x + m_pGameContext->getDefaultPadding()*4 + label->getContentSize().width/2
      , m_scoreBoxLeftBottom.y - m_pGameContext->getDefaultPadding()*2 - label->getContentSize().height/2);
    this->addChild(label);
        
    m_playButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
    , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
    , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
    , "play"
    , m_pGameContext->getDefaultButtonSize()
    , this->m_pGameContext->getDefaultBorderThickness()
    , this->m_pGameContext
    , callfuncO_selector(DescriptionPopup::playCallback)
    , this);
    m_playButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);    
    m_playButton->setPosition(center.x, m_descriptionBoxLeftBottom.y 
      + m_playButton->getSize().height);
    m_playButton->setVisible(false);
    this->addChild(m_playButton);
    /*
    float innerTopY = header->getPositionY() - header->getContentSize().height/2;
    float innerBottomY = m_playButton->getPositionY() + m_playButton->getSize().height/2;
            
    CCLabelBMFont* body = CCLabelBMFont::create(m_text.c_str(), m_pGameContext->getFontNormalPath().c_str());
    body->setPosition(ccpRounded(
      m_dialogRectInnerLeftBottom.x + padding + body->getContentSize().width/2
      , innerTopY - (innerTopY - innerBottomY)/2
      ));
    this->addChild(body);*/
    /*
    m_visibleRectLeftBottom = VisibleRect::leftBottom();
    m_visibleRectRightTop = VisibleRect::rightTop();*/
  }
}

void DescriptionPopup::setEnablePlayButton(bool isEnabled)
{
  if (this->m_playButton)
  {
    this->m_playButton->setVisible(isEnabled);
  }
}

void DescriptionPopup::draw()
{  
  // rectangles
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  ccDrawSolidRect(m_descriptionBoxLeftBottom, m_descriptionBoxRightTop, m_descriptionBackgroundColor);
  ccDrawSolidRect(m_scoreBoxLeftBottom, m_scoreBoxRightTop, m_targetBackgroundColor);
  ccDrawSolidRect(m_headerBoxLeftBottom, m_headerBoxRightTop, m_backgroundColor);

  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  // separators
  ccDrawSolidRect(m_scoreBoxLeftBottom, m_lowerSeparatorRightTop, m_dialogBorderColor);
  ccDrawSolidRect(m_headerBoxLeftBottom, m_upperSeparatorRightTop, m_dialogBorderColor);

  // borders
  ccDrawSolidRect(m_descriptionBoxLeftBottom, m_borderLeftRightTop, m_dialogBorderColor);
  ccDrawSolidRect(m_descriptionBoxLeftBottom, m_borderBottomRightTop, m_dialogBorderColor);
  ccDrawSolidRect(m_borderRightLeftBottom, m_headerBoxRightTop, m_dialogBorderColor);
  ccDrawSolidRect(m_borderTopLeftBottom, m_headerBoxRightTop, m_dialogBorderColor);

}

void DescriptionPopup::playCallback(CCObject* pSender)
{
  if(m_pTarget != 0 && this->m_fnpCloseCallbackDelegate != 0)
      (m_pTarget->*this->m_fnpCloseCallbackDelegate)(this);
}