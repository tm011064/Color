#include "GameScorePopup.h"

GameScorePopup* GameScorePopup::create(GameContext* gameContext, std::string headerText
  , SEL_CallFuncO playAgainCallbackDelegate
  , SEL_CallFuncO mainMenuCallbackDelegate
  , SEL_CallFuncO nextChallengeCallbackDelegate
  , std::vector<WildcardButtonDefinition> wildcardButtonDefinitions
  , CCNode* callbackTarget
  , GameScorePopupType gameScorePopupType
  , GameScorePopupMode gameScorePopupMode)
{ 
  GameScorePopup* gameScorePopup = new GameScorePopup(gameContext, headerText
    , playAgainCallbackDelegate, mainMenuCallbackDelegate, nextChallengeCallbackDelegate
    , wildcardButtonDefinitions
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
    
    
    float posY = round( m_dialogRectInnerRightTop.y + verticalSpacing/2 + m_padding*2 );
    m_coinsLabelDescription = CCLabelBMFont::create("coins available", m_pGameContext->getFontNormalPath().c_str());
    m_coinsLabelDescription->setPosition(this->m_textIndentLeft + m_coinsLabelDescription->getContentSize().width/2, posY );
    this->addChild(m_coinsLabelDescription);
       
    m_coinsLabel = CCLabelBMFont::create("NA", m_pGameContext->getFontNormalPath().c_str());
    m_coinsLabel->setPosition(ccp(this->m_textIndentRight - m_coinsLabel->getContentSize().width/2, posY));
    this->addChild(m_coinsLabel);
    
    m_availableCoinsCoin = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("coin_small"));
    m_availableCoinsCoin->setScale(this->m_pGameContext->getFontHeightNormal() / m_availableCoinsCoin->getContentSize().height * 1.5);
    m_availableCoinsCoin->setPosition(ccpRounded(m_coinsLabel->getPositionX() - m_coinsLabel->getContentSize().width/2 - m_padding, posY));
    this->addChild(m_availableCoinsCoin);


    posY = m_dialogRectInnerRightTop.y - verticalSpacingLarge/2 - this->m_padding * 4;
    m_headerTextLabel = CCLabelBMFont::create(m_headerText.c_str(), m_pGameContext->getFontLargePath().c_str());
    m_headerTextLabel->setPosition(center.x, posY );
    this->addChild(m_headerTextLabel);
    posY -= m_pGameContext->getFontHeightLarge()/2;
        
    int headerTextBottomEdgePosY = posY;

    CCSize size;
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

      posY -= verticalSpacing;
      m_blackStar1 = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("starBlack"));
      size = m_blackStar1->getContentSize();

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
      m_retryButton->setPosition(this->m_textIndentRight - m_retryButton->getSize().width/2, menuButtonPosYTop);
      this->addChild(m_retryButton);
      
      m_moreCoinsTextButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
        , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
        , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
        , "+coins"
        , m_pGameContext->getDefaultButtonSize()
        , this->m_borderThickness
        , this->m_pGameContext
        , callfuncO_selector(GameScorePopup::moreCoinsCallback)
        , this);
      m_moreCoinsTextButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
      m_moreCoinsTextButton->setPosition(this->m_textIndentLeft + m_moreCoinsTextButton->getSize().width/2
        , menuButtonPosYTop);
      this->addChild(m_moreCoinsTextButton);
      
      m_moreCoinsBackTextButton = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
        , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
        , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
        , "back"
        , m_pGameContext->getDefaultButtonSize()
        , this->m_borderThickness
        , this->m_pGameContext
        , callfuncO_selector(GameScorePopup::gameScoreInfoPanelCallback)
        , this);
      m_moreCoinsBackTextButton->setTouchPriority(TOUCH_PRIORITY_MODAL_ITEM);
      m_moreCoinsBackTextButton->setPosition(this->m_textIndentLeft + m_moreCoinsBackTextButton->getSize().width/2
        , menuButtonPosYTop);
      this->addChild(m_moreCoinsBackTextButton);      

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

    m_innerWildcardRectPanel = CCRectMake( this->m_textIndentLeft, menuButtonPosYTopEdge
      , this->m_textIndentRight - this->m_textIndentLeft, headerTextBottomEdgePosY - menuButtonPosYTopEdge );

    m_wildcardPopupButtonPanel = WildcardPopupButtonPanel::create(m_pGameContext
      , CCSizeMake(this->m_textIndentRight - this->m_textIndentLeft, 0)
      , m_wildcardButtonDefinitions);
    m_wildcardPopupButtonPanel->setPosition(center.x, m_innerWildcardRectPanel.getMidY() );
    this->addChild(m_wildcardPopupButtonPanel);
    
    this->m_wildcardPopupBuyCoinsPanel = WildcardPopupBuyCoinsPanel::create(
      this->m_pGameContext
      , CCSizeMake( this->m_textIndentRight - this->m_textIndentLeft, 0 )
      , callfuncO_selector(GameScorePopup::gameScoreInfoPanelCallback)
      , this);
    m_wildcardPopupBuyCoinsPanel->setPosition(center.x, m_innerWildcardRectPanel.getMidY() );
    this->addChild(this->m_wildcardPopupBuyCoinsPanel);

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
  this->show(true, "play on?", false, "", ""); 
}

void GameScorePopup::show(bool showWildcardHeader, std::string headerText
    , bool showWildcardScoreInfo, std::string scoreInfoLeft, std::string scoreInfoRight)
{
  ModalControl::show();
 
  if (this->m_gameScorePopupMode == GSPMODE_CHALLENGE)
  {
    GameScore gameScore = this->m_pGameContext->getGameScore();

    m_coinsLabel->setString(UtilityHelper::convertToString(m_pGameContext->getTotalCoins()).c_str());  
    m_coinsLabel->setPositionX(round(m_textIndentRight - m_padding*2 - m_coinsLabel->getContentSize().width/2));
    m_availableCoinsCoin->setPositionX(round(m_coinsLabel->getPositionX() - m_coinsLabel->getContentSize().width/2 
                                                                          - m_padding
                                                                          - m_availableCoinsCoin->getContentSize().width/2));

    this->m_goldStar1->setVisible(false);
    this->m_goldStar2->setVisible(false);
    this->m_goldStar3->setVisible(false);
    
    if (gameScore.starsEarned > 0)
    {
      this->m_gameScorePanel->show();
      this->m_wildcardPopupButtonPanel->hide();
      this->m_wildcardPopupBuyCoinsPanel->hide();

      this->m_blackStar1->setVisible(true);
      this->m_blackStar2->setVisible(true);
      this->m_blackStar3->setVisible(true);

      this->m_headerTextLabel->setString("LEVEL COMPLETED");
      this->m_coinsLabel->setVisible(false);
      this->m_availableCoinsCoin->setVisible(false);
      this->m_coinsLabelDescription->setVisible(false);      
      this->m_moreCoinsTextButton->setVisible(false);
      this->m_moreCoinsBackTextButton->setVisible(false);
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
      this->m_goldStar1->runAction(CCSequence::create(CCDelayTime::create(startDelay), CCScaleBy::create(.1f, scaleTo), CCScaleBy::create(.3f, scaleBackTo), NULL));
            
      if (gameScore.starsEarned > 1)
      {
        this->m_goldStar2->setOpacity((GLubyte)0);
        this->m_goldStar2->setVisible(true);
        this->m_goldStar2->runAction(CCSequence::create(CCDelayTime::create(startDelay + interval), CCFadeIn::create(.4f), NULL));
        this->m_goldStar2->runAction(CCSequence::create(CCDelayTime::create(startDelay + interval), CCScaleBy::create(.1f, scaleTo), CCScaleBy::create(.3f, scaleBackTo), NULL));
      }
      if (gameScore.starsEarned > 2)
      {
        this->m_goldStar3->setOpacity((GLubyte)0);
        this->m_goldStar3->setVisible(true);
        this->m_goldStar3->runAction(CCSequence::create(CCDelayTime::create(startDelay + interval*2), CCFadeIn::create(.4f), NULL));
        this->m_goldStar3->runAction(CCSequence::create(CCDelayTime::create(startDelay + interval*2), CCScaleBy::create(.1f, scaleTo), CCScaleBy::create(.3f, scaleBackTo), NULL));
      }
    }
    else
    {
      this->m_gameScorePanel->hide();

      this->m_wildcardPopupButtonPanel->updateLayout(showWildcardHeader, headerText
        , showWildcardScoreInfo, scoreInfoLeft, scoreInfoRight);

      this->m_wildcardPopupButtonPanel->show();
      this->m_wildcardPopupBuyCoinsPanel->hide();

      this->m_blackStar1->setVisible(false);
      this->m_blackStar2->setVisible(false);
      this->m_blackStar3->setVisible(false);

      this->m_headerTextLabel->setString("LEVEL FAILED");
      
      this->m_coinsLabel->setVisible(true);
      this->m_availableCoinsCoin->setVisible(true);
      this->m_coinsLabelDescription->setVisible(true);  
      this->m_moreCoinsTextButton->setVisible(true);
      this->m_moreCoinsBackTextButton->setVisible(false);
      this->m_retryButton->setVisible(true);
      this->m_nextButton->setVisible(false);
      this->m_replayButton->setVisible(false);
    }  
  }
  else
  {
    this->m_wildcardPopupBuyCoinsPanel->hide();
    this->m_wildcardPopupButtonPanel->hide();
      
    if ( this->m_coinsLabel ) 
      this->m_coinsLabel->setVisible(false);
    if ( this->m_availableCoinsCoin ) 
      this->m_availableCoinsCoin->setVisible(false);
    if ( this->m_coinsLabelDescription ) 
      this->m_coinsLabelDescription->setVisible(false);  

    if ( this->m_moreCoinsTextButton ) 
      this->m_moreCoinsTextButton->setVisible(false);
    if ( this->m_moreCoinsBackTextButton ) 
      this->m_moreCoinsBackTextButton->setVisible(false);
    if ( this->m_retryButton ) 
      this->m_retryButton->setVisible(false);
    if ( this->m_nextButton ) 
      this->m_nextButton->setVisible(false);
    if ( this->m_replayButton ) 
      this->m_replayButton->setVisible(false);

    this->m_gameScorePanel->show();
  }
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

void GameScorePopup::showMoreCoinsPanel()
{
  activatePanel(GSPPO_MORE_COINS_PANEL);
}

void GameScorePopup::activatePanel(GameScorePopupPlayOnPanel gameScorePopupPlayOnPanel)
{
  CCActionInterval* moveLeft = CCMoveBy::create(.15f, ccp(-(VisibleRect::getVisibleRect().size.width),0));
  CCActionInterval* moveRight = CCMoveBy::create(.15f, ccp((VisibleRect::getVisibleRect().size.width),0));
  
  CCPoint center = VisibleRect::center();
  CCRect visibleRect = VisibleRect::getVisibleRect();
  float easeRate = .5f;
  float posLeft = center.x - visibleRect.size.width;
  float posRight = center.x + visibleRect.size.width;
    
  this->m_wildcardPopupBuyCoinsPanel->show();
  this->m_wildcardPopupButtonPanel->show();

  switch (gameScorePopupPlayOnPanel)
  {
  case GSPPO_GAMESCORE_INFO_PANEL:
    this->m_wildcardPopupBuyCoinsPanel->setPositionX(center.x);
    this->m_wildcardPopupBuyCoinsPanel->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));

    this->m_wildcardPopupButtonPanel->setPositionX(posLeft);
    this->m_wildcardPopupButtonPanel->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      
    this->m_moreCoinsTextButton->setVisible(true);
    this->m_moreCoinsBackTextButton->setVisible(false);
    break;

  case GSPPO_MORE_COINS_PANEL:
    this->m_wildcardPopupBuyCoinsPanel->setPositionX(posRight);
    this->m_wildcardPopupBuyCoinsPanel->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));

    this->m_wildcardPopupButtonPanel->setPositionX(center.x);
    this->m_wildcardPopupButtonPanel->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
  
    this->m_moreCoinsTextButton->setVisible(false);
    this->m_moreCoinsBackTextButton->setVisible(true);
    break;
  }
  
  this->m_activeGameScorePopupPlayOnPanel = gameScorePopupPlayOnPanel;
}

void GameScorePopup::moreCoinsCallback(CCObject* pSender)
{
  activatePanel(GSPPO_MORE_COINS_PANEL);
}
void GameScorePopup::gameScoreInfoPanelCallback(CCObject* pSender)
{    
  activatePanel(GSPPO_GAMESCORE_INFO_PANEL);
}