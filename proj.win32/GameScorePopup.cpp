#include "GameScorePopup.h"

GameScorePopup* GameScorePopup::create(GameContext* gameContext, std::string headerText
  , SEL_CallFuncO playAgainCallbackDelegate
  , SEL_CallFuncO mainMenuCallbackDelegate
  , SEL_CallFuncO nextChallengeCallbackDelegate
  , CCNode* callbackTarget, GameScorePopupType gameScorePopupType
  , GameScorePopupMode gameScorePopupMode)
{ 
  GameScorePopup* gameScorePopup = new GameScorePopup(gameContext, headerText
    , playAgainCallbackDelegate, mainMenuCallbackDelegate, nextChallengeCallbackDelegate
    , callbackTarget, gameScorePopupType, gameScorePopupMode);
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
    posY -= m_pGameContext->getFontHeightLarge()/2;
        
    posY -= verticalSpacing;
    m_blackStar1 = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("starBlack"));
    CCSize size = m_blackStar1->getContentSize();

    m_blackStar1->setPosition(ccpRounded(center.x - size.width * 1.5f, posY));
    this->addChild(m_blackStar1);
    
    m_blackStar2 = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("starBlack"));
    m_blackStar2->setPosition(ccpRounded(center.x, posY));
    this->addChild(m_blackStar2);
    
    m_blackStar3 = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("starBlack"));
    m_blackStar3->setPosition(ccpRounded(center.x + size.width * 1.5f, posY));
    this->addChild(m_blackStar3);
    
    m_goldStar1 = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("starGolden"));
    m_goldStar1->setPosition(ccpRounded(center.x - size.width * 1.5f, posY));
    this->addChild(m_goldStar1);
    
    m_goldStar2 = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("starGolden"));
    m_goldStar2->setPosition(ccpRounded(center.x, posY));
    this->addChild(m_goldStar2);
    
    m_goldStar3 = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("starGolden"));
    m_goldStar3->setPosition(ccpRounded(center.x + size.width * 1.5f, posY));
    this->addChild(m_goldStar3);

    posY -= verticalSpacing;

    TextButton* textButton;
    int menuButtonPosYTop, menuButtonPosYBottom, menuButtonPosYTopEdge;
    switch (m_gameScorePopupMode)
    {
    case GSPMODE_ARCADE:

      textButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
        , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
        , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
        , "menu"
        , m_pGameContext->getDefaultButtonSize()
        , this->m_borderThickness
        , this->m_pGameContext
        , callfuncO_selector(GameScorePopup::mainMenuCallback)
        , this);
      textButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);

      menuButtonPosYTop = m_dialogRectInnerLeftBottom.y + this->m_padding * 5 + textButton->getSize().height/2;
      menuButtonPosYBottom = m_dialogRectInnerLeftBottom.y - this->m_padding * 5 - textButton->getSize().height/2;
      menuButtonPosYTopEdge = menuButtonPosYTop + textButton->getSize().height/2;

      textButton->setPosition(this->m_textIndentLeft + textButton->getSize().width/2
        , menuButtonPosYTop);
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
        , menuButtonPosYTop);
      this->addChild(textButton);

      break;

      
    case GSPMODE_CHALLENGE:

      textButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
        , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
        , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
        , "menu"
        , m_pGameContext->getDefaultButtonSize()
        , this->m_borderThickness
        , this->m_pGameContext
        , callfuncO_selector(GameScorePopup::mainMenuCallback)
        , this);
      textButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
    
      menuButtonPosYTop = m_dialogRectInnerLeftBottom.y + this->m_padding * 5 + textButton->getSize().height/2;
      menuButtonPosYBottom = m_dialogRectInnerLeftBottom.y - this->m_padding * 5 - textButton->getSize().height/2;
      menuButtonPosYTopEdge = menuButtonPosYTop + textButton->getSize().height/2;
    
      textButton->setPosition(center.x, menuButtonPosYBottom);
      this->addChild(textButton);

      m_retryButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
        , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
        , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
        , "retry"
        , m_pGameContext->getDefaultButtonSize()
        , this->m_borderThickness
        , this->m_pGameContext
        , callfuncO_selector(GameScorePopup::playAgainCallback)
        , this);
      m_retryButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
      m_retryButton->setPosition(center.x, menuButtonPosYTop);
      this->addChild(m_retryButton);

      m_replayButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
        , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
        , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
        , "replay"
        , m_pGameContext->getDefaultButtonSize()
        , this->m_borderThickness
        , this->m_pGameContext
        , callfuncO_selector(GameScorePopup::playAgainCallback)
        , this);
      m_replayButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
      m_replayButton->setPosition(this->m_textIndentLeft + m_replayButton->getSize().width/2
        , menuButtonPosYTop);
      this->addChild(m_replayButton);
    
      m_nextButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
        , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
        , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
        , "next"
        , m_pGameContext->getDefaultButtonSize()
        , this->m_borderThickness
        , this->m_pGameContext
        , callfuncO_selector(GameScorePopup::nextChallengeCallback)
        , this);
      m_nextButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
      m_nextButton->setPosition(this->m_textIndentRight - m_nextButton->getSize().width/2
        , menuButtonPosYTop);
      this->addChild(m_nextButton);
      

      break;
    }
    
    m_separatorColor.a = 1; 
    m_separatorColor.r = 1; 
    m_separatorColor.g = 1; 
    m_separatorColor.b = 1; 
    switch (this->m_gameScorePopupType)
    {
    case GSPTYPE_POINTS:
      m_gameScorePanel = GameScorePointsPanel::create(this->m_pGameContext
        , this->m_textIndentRight - this->m_textIndentLeft, m_separatorColor);
      this->m_gameScorePanel->setPosition(center.x, posY - ( posY - menuButtonPosYTopEdge )/2);
      this->addChild(m_gameScorePanel);
      break;

    case GSPTYPE_TIME_INTERVALS:
      m_gameScorePanel = GameScoreTimePanel::create(this->m_pGameContext
        , this->m_textIndentRight - this->m_textIndentLeft, true, m_separatorColor);
      this->m_gameScorePanel->setPosition(center.x, posY - ( posY - menuButtonPosYTopEdge )/2);
      this->addChild(m_gameScorePanel);
      break;

    case GSPTYPE_RHYTHM:
      m_gameScorePanel = GameScoreTimePanel::create(this->m_pGameContext
        , this->m_textIndentRight - this->m_textIndentLeft, false, m_separatorColor);
      this->m_gameScorePanel->setPosition(center.x, posY - ( posY - menuButtonPosYTopEdge )/2);
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

void GameScorePopup::show()
{
  ModalControl::show();
 
  if (this->m_gameScorePopupMode == GSPMODE_CHALLENGE)
  {
    GameScore gameScore = this->m_pGameContext->getGameScore();

    this->m_goldStar1->setVisible(false);
    this->m_goldStar2->setVisible(false);
    this->m_goldStar3->setVisible(false);
    this->m_blackStar1->setVisible(true);
    this->m_blackStar2->setVisible(true);
    this->m_blackStar3->setVisible(true);
    
    if (gameScore.starsEarned > 0)
    {
      this->m_headerTextLabel->setString("LEVEL COMPLETED");
      this->m_retryButton->setVisible(false);
      this->m_nextButton->setVisible(true);
      this->m_replayButton->setVisible(true);

      float startDelay = .2f;
      float interval = .4f;
      float scaleTo = 1.8f;
      float scaleBackTo = 1.0f/scaleTo;

      CCActionInterval* fadeIn = CCFadeIn::create(.2f);
      this->m_goldStar1->setOpacity((GLubyte)0);
      this->m_goldStar1->setVisible(true);
      this->m_goldStar1->runAction(CCSequence::create(CCDelayTime::create(startDelay), CCFadeIn::create(.4), NULL));
      this->m_goldStar1->runAction(CCSequence::create(CCDelayTime::create(startDelay), CCScaleBy::create(.1, scaleTo), CCScaleBy::create(.3, scaleBackTo), NULL));

      if (gameScore.starsEarned > 1)
      {
        this->m_goldStar2->setOpacity((GLubyte)0);
        this->m_goldStar2->setVisible(true);
        this->m_goldStar2->runAction(CCSequence::create(CCDelayTime::create(startDelay + interval), CCFadeIn::create(.4f), NULL));
        this->m_goldStar2->runAction(CCSequence::create(CCDelayTime::create(startDelay + interval), CCScaleBy::create(.1, scaleTo), CCScaleBy::create(.3, scaleBackTo), NULL));
      }
      if (gameScore.starsEarned > 2)
      {
        this->m_goldStar3->setOpacity((GLubyte)0);
        this->m_goldStar3->setVisible(true);
        this->m_goldStar3->runAction(CCSequence::create(CCDelayTime::create(startDelay + interval*2), CCFadeIn::create(.4f), NULL));
        this->m_goldStar3->runAction(CCSequence::create(CCDelayTime::create(startDelay + interval*2), CCScaleBy::create(.1, scaleTo), CCScaleBy::create(.3, scaleBackTo), NULL));
      }
    }
    else
    {
      this->m_headerTextLabel->setString("LEVEL FAILED");
      this->m_retryButton->setVisible(true);
      this->m_nextButton->setVisible(false);
      this->m_replayButton->setVisible(false);
    }  
  }

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
void GameScorePopup::nextChallengeCallback(CCObject* pSender)
{  
  if(m_pTarget != 0 && this->m_fnpNextChallengeCallbackDelegate != 0)
      (m_pTarget->*this->m_fnpNextChallengeCallbackDelegate)(this);
}