#include "GameScorePopup.h"

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
    CCLabelBMFont* label = CCLabelBMFont::create("GAME OVER", m_pGameContext->getFontLargePath().c_str());
    label->setPosition(center.x, posY );
    this->addChild(label);
    
    char str[256];        

    posY -= (verticalSpacingLarge/2 + verticalSpacing/2 + this->m_padding * 8);

    m_pointsLabelDescription = CCLabelBMFont::create("Points", m_pGameContext->getFontNormalPath().c_str());
    m_pointsLabelDescription->setPosition(this->m_textIndentLeft + m_pointsLabelDescription->getContentSize().width/2, posY);
    this->addChild(m_pointsLabelDescription);
    sprintf(str, "%i", (int)(gameScore.totalPoints));
    m_pointsLabel = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    m_pointsLabel->setPosition(this->m_textIndentRight - m_pointsLabel->getContentSize().width/2, posY);
    this->addChild(m_pointsLabel);
    
    posY -= verticalSpacing;
    m_levelBonusLabelDescription = CCLabelBMFont::create("Level bonus", m_pGameContext->getFontNormalPath().c_str());
    m_levelBonusLabelDescription->setPosition(this->m_textIndentLeft + m_levelBonusLabelDescription->getContentSize().width/2, posY);
    this->addChild(m_levelBonusLabelDescription);
    sprintf(str, "%i", (int)(gameScore.totalLevelBonus));
    m_levelBonusLabel = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    m_levelBonusLabel->setPosition(this->m_textIndentRight - m_levelBonusLabel->getContentSize().width/2, posY);
    this->addChild(m_levelBonusLabel);
    
    posY -= verticalSpacing;
    m_timeBonusLabelDescription = CCLabelBMFont::create("Time bonus", m_pGameContext->getFontNormalPath().c_str());
    m_timeBonusLabelDescription->setPosition(this->m_textIndentLeft + m_timeBonusLabelDescription->getContentSize().width/2, posY);
    this->addChild(m_timeBonusLabelDescription);
    sprintf(str, "%i", (int)(gameScore.totalButtonBonus));
    m_timeBonusLabel = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    m_timeBonusLabel->setPosition(this->m_textIndentRight - m_timeBonusLabel->getContentSize().width/2, posY);
    this->addChild(m_timeBonusLabel);
    
    posY -= (verticalSpacing/2);
    m_separatorLineLeftBottom = ccp ( this->m_textIndentLeft, posY - this->m_borderThickness );
    m_separatorLineRightTop = ccp ( this->m_textIndentRight, posY );
  
    posY -= (verticalSpacing/2 + this->m_padding * 6);
    label = CCLabelBMFont::create("Total Points", m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2, posY);
    this->addChild(label);
    m_totalPointsLabel = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    m_totalPointsLabel->setPosition(this->m_textIndentRight - m_totalPointsLabel->getContentSize().width/2, posY);
    this->addChild(m_totalPointsLabel);

    posY -= verticalSpacing;
    label = CCLabelBMFont::create("Coins earned", m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2, posY);
    this->addChild(label);
    m_coinsEarnedLabel = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    m_coinsEarnedLabel->setPosition(this->m_textIndentRight - m_coinsEarnedLabel->getContentSize().width/2, posY);
    this->addChild(m_coinsEarnedLabel);
        
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

void GameScorePopup::refresh()
{
  char str[256];        
  GameScore gameScore = m_pGameContext->getGameScore();
  
  m_totalPointsLabel->setString("0");
  m_totalPointsLabel->setPositionX(this->m_textIndentRight - m_totalPointsLabel->getContentSize().width/2);
  
  sprintf(str, "+%i", (int)(gameScore.totalPoints - gameScore.totalLevelBonus - gameScore.totalButtonBonus));
  m_pointsLabel->setString(str);
  m_pointsLabel->setPositionX(this->m_textIndentRight - m_pointsLabel->getContentSize().width/2);
  m_pointsLabel->setVisible(false);
  
  sprintf(str, "+%i", (int)(gameScore.totalLevelBonus));
  m_levelBonusLabel->setString(str);
  m_levelBonusLabel->setPositionX(this->m_textIndentRight - m_levelBonusLabel->getContentSize().width/2);
  m_levelBonusLabel->setVisible(false);

  sprintf(str, "+%i", (int)(gameScore.totalButtonBonus));
  m_timeBonusLabel->setString(str);
  m_timeBonusLabel->setPositionX(this->m_textIndentRight - m_timeBonusLabel->getContentSize().width/2);
  m_timeBonusLabel->setVisible(false);

  m_coinsEarnedLabel->setString("0");
  m_coinsEarnedLabel->setPositionX(this->m_textIndentRight - m_coinsEarnedLabel->getContentSize().width/2);
  m_coinsEarnedLabel->setVisible(false);

  m_pointsLabelDescription->setVisible(false);
  m_levelBonusLabelDescription->setVisible(false);
  m_timeBonusLabelDescription->setVisible(false);
}

void GameScorePopup::show()
{
  ModalControl::show();

  // get the score
  this->refresh();

  // now start animation... 
  float coinsDelay = .8f;

  this->m_elaspeTimePoints = 0;
  this->m_elaspeTimeCoins = -coinsDelay;
  this->m_targetTime = .8f;

  this->schedule(schedule_selector(GameScorePopup::updatePointsDisplay), 0.021f); // framerate: 1/48
  this->schedule(schedule_selector(GameScorePopup::updateCoinsDisplay), 0.021f, -1, coinsDelay); // framerate: 1/48
}

void GameScorePopup::updateCoinsDisplay(float dt)
{
  m_elaspeTimeCoins += dt;

  GameScore gameScore = m_pGameContext->getGameScore();

  float val = m_elaspeTimeCoins * gameScore.coinsEarned / m_targetTime;
  if (val >= 1)
    m_coinsEarnedLabel->setVisible(true);
  
  if (this->m_elaspeTimeCoins >= this->m_targetTime)
  {   
    val = gameScore.coinsEarned;    
    m_coinsEarnedLabel->setVisible(true);
    this->unschedule(schedule_selector(GameScorePopup::updateCoinsDisplay));
  }
  
  char str[256];
  sprintf(str, "%d", (int)(val));
  m_coinsEarnedLabel->setString(str);
  m_coinsEarnedLabel->setPositionX(this->m_textIndentRight - m_coinsEarnedLabel->getContentSize().width/2);  
}

void GameScorePopup::updatePointsDisplay(float dt)
{
  m_elaspeTimePoints += dt;
  
  GameScore gameScore = m_pGameContext->getGameScore();
  float points = gameScore.totalPoints - gameScore.totalLevelBonus - gameScore.totalButtonBonus;
  float val = m_elaspeTimePoints * gameScore.totalPoints / m_targetTime;
  if (val >= 0)
  {
    this->m_pointsLabel->setVisible(true);
    this->m_pointsLabelDescription->setVisible(true);    
  }
  if (val >= points)
  {
    this->m_levelBonusLabel->setVisible(true);
    this->m_levelBonusLabelDescription->setVisible(true);
  }
  if (val >= points + gameScore.totalLevelBonus)
  {
    this->m_timeBonusLabel->setVisible(true);
    this->m_timeBonusLabelDescription->setVisible(true);
  }

  if (this->m_elaspeTimePoints >= this->m_targetTime)
  {
    this->m_pointsLabel->setVisible(true);
    this->m_pointsLabelDescription->setVisible(true);
    this->m_levelBonusLabel->setVisible(true);
    this->m_levelBonusLabelDescription->setVisible(true);
    this->m_timeBonusLabel->setVisible(true);
    this->m_timeBonusLabelDescription->setVisible(true);

    val = gameScore.totalPoints;
    
    this->unschedule(schedule_selector(GameScorePopup::updatePointsDisplay));
  }

  char str[256];

  sprintf(str, "%i", (int)(val));
  m_totalPointsLabel->setString(str);
  m_totalPointsLabel->setPositionX(this->m_textIndentRight - m_totalPointsLabel->getContentSize().width/2);  
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
  ccDrawSolidRect(m_separatorLineLeftBottom, m_separatorLineRightTop, m_separatorColor);
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