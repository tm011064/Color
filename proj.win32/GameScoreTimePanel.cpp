#include "GameScoreTimePanel.h"

GameScoreTimePanel* GameScoreTimePanel::create(GameContext* gameContext, float width
  , bool showAverageDuration, ccColor4F separatorColor) 
{ 
  GameScoreTimePanel* gameScorePointsPanel = new GameScoreTimePanel(gameContext, width, showAverageDuration, separatorColor);
  gameScorePointsPanel->autorelease();
  return gameScorePointsPanel;
}

void GameScoreTimePanel::onEnter()
{
  CCNode::onEnter();

  if (!this->m_isLayoutInitialized)
  {    
    this->m_isLayoutInitialized = true;
    
    CCPoint center = VisibleRect::center();
        
    CCRect visibleRect = VisibleRect::getVisibleRect();
        
    GameScore gameScore = m_pGameContext->getGameScore();
        
    this->m_padding = m_pGameContext->getDefaultPadding();
    this->m_borderThickness = m_pGameContext->getDefaultBorderThickness();

    float verticalSpacing = m_pGameContext->getFontHeightNormal() + m_padding;
    float verticalSpacingLarge = m_pGameContext->getFontHeightLarge() + m_padding*3;
    
    char str[256];        

    float posY = 0;
    
    m_pointsLabelDescription = CCLabelBMFont::create("Points", m_pGameContext->getFontNormalPath().c_str());
    m_pointsLabelDescription->setPosition(this->m_textIndentLeft + m_pointsLabelDescription->getContentSize().width/2, posY);
    this->addChild(m_pointsLabelDescription);
    sprintf(str, "%i", (int)(gameScore.totalPoints));
    m_pointsLabel = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    m_pointsLabel->setPosition(this->m_textIndentRight - m_pointsLabel->getContentSize().width/2, posY);
    this->addChild(m_pointsLabel);

    posY -= verticalSpacing;
    m_timingLabelDescription = CCLabelBMFont::create("Avg Timing", m_pGameContext->getFontNormalPath().c_str());
    m_timingLabelDescription->setPosition(this->m_textIndentLeft + m_timingLabelDescription->getContentSize().width/2, posY);
    this->addChild(m_timingLabelDescription);
    sprintf(str, "%i", (int)(gameScore.totalPoints));
    m_timingLabel = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    m_timingLabel->setPosition(this->m_textIndentRight - m_timingLabel->getContentSize().width/2, posY);
    this->addChild(m_timingLabel);
    
    if (m_showAverageDuration)
    {
      posY -= verticalSpacing;
      m_durationLabelDescription = CCLabelBMFont::create("Avg Duration", m_pGameContext->getFontNormalPath().c_str());
      m_durationLabelDescription->setPosition(this->m_textIndentLeft + m_durationLabelDescription->getContentSize().width/2, posY);
      this->addChild(m_durationLabelDescription);
      sprintf(str, "%i", (int)(gameScore.totalPoints));
      m_durationLabel = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
      m_durationLabel->setPosition(this->m_textIndentRight - m_durationLabel->getContentSize().width/2, posY);
      this->addChild(m_durationLabel);
    }   

    posY -= verticalSpacing;
    m_scoreLabelDescription = CCLabelBMFont::create("Score", m_pGameContext->getFontNormalPath().c_str());
    m_scoreLabelDescription->setPosition(this->m_textIndentLeft + m_scoreLabelDescription->getContentSize().width/2, posY);
    this->addChild(m_scoreLabelDescription);
    sprintf(str, "%i", (int)(gameScore.totalPoints));
    m_scoreLabel = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    m_scoreLabel->setPosition(this->m_textIndentRight - m_scoreLabel->getContentSize().width/2, posY);
    this->addChild(m_scoreLabel);
    
    posY -= verticalSpacing;
    CCLabelBMFont* label = CCLabelBMFont::create("Coins earned", m_pGameContext->getFontNormalPath().c_str());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2, posY);
    this->addChild(label);
    m_coinsEarnedLabel = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    m_coinsEarnedLabel->setPosition(this->m_textIndentRight - m_coinsEarnedLabel->getContentSize().width/2, posY);
    this->addChild(m_coinsEarnedLabel);
        
    this->setContentSize(CCSizeMake( this->m_textIndentRight - this->m_textIndentLeft, -posY ));
    CCArray *pChildren = this->getChildren();
    if (pChildren && pChildren->count() > 0)
    {
      CCObject* pObject = NULL;
      posY = -posY/2;
      CCNode* pNode;
      CCARRAY_FOREACH(pChildren, pObject)
      {
        pNode = (CCNode*) pObject;
        pNode->setPositionY(round( pNode->getPositionY() + posY ));
      }
    }

  }
}

void GameScoreTimePanel::refresh()
{
  char str[256];        
  GameScore gameScore = m_pGameContext->getGameScore();
  
  sprintf(str, "%i", (int)gameScore.totalPoints);
  m_pointsLabel->setString(str);
  m_pointsLabel->setPositionX(this->m_textIndentRight - m_pointsLabel->getContentSize().width/2);
  m_pointsLabel->setVisible(false);
  
  if (gameScore.averageButtonBlinkStartOffset >= 0)
    sprintf(str, "%.3f s", gameScore.averageButtonBlinkStartOffset);
  else
    sprintf(str, "NA");
  m_timingLabel->setString(str);
  m_timingLabel->setPositionX(this->m_textIndentRight - m_timingLabel->getContentSize().width/2);
  m_timingLabel->setVisible(false);
  
  if (m_showAverageDuration)
  {
    if (gameScore.averageButtonBlinkStartOffset >= 0)
      sprintf(str, "%.3f s", gameScore.averageButtonBlinkDurationOffset);
    else
      sprintf(str, "NA");
    m_durationLabel->setString(str);
    m_durationLabel->setPositionX(this->m_textIndentRight - m_durationLabel->getContentSize().width/2);
    m_durationLabel->setVisible(false);
  }

  if (gameScore.averageButtonBlinkStartOffset >= 0)
    sprintf(str, "%i / 100", (int)round(gameScore.averageButtonBlinkPercentage*100));
  else
    sprintf(str, "NA");
  m_scoreLabel->setString(str);
  m_scoreLabel->setPositionX(this->m_textIndentRight - m_scoreLabel->getContentSize().width/2);
  m_scoreLabel->setVisible(false);

  m_coinsEarnedLabel->setString("0");
  m_coinsEarnedLabel->setPositionX(this->m_textIndentRight - m_coinsEarnedLabel->getContentSize().width/2);
  m_coinsEarnedLabel->setVisible(false);

  m_pointsLabelDescription->setVisible(false);
}

void GameScoreTimePanel::draw()
{ 
  ccDrawSolidRect(m_separatorLineLeftBottom, m_separatorLineRightTop, m_separatorColor);
}

void GameScoreTimePanel::show()
{
  BaseNode::show();

  // get the score
  this->refresh();

  // now start animation... 
  float coinsDelay = .8f;

  this->m_elaspeTimePoints = 0;
  this->m_elaspeTimeCoins = -coinsDelay;
  this->m_targetTime = .8f;

  this->schedule(schedule_selector(GameScoreTimePanel::updatePointsDisplay), 0.021f); // framerate: 1/48
  this->schedule(schedule_selector(GameScoreTimePanel::updateCoinsDisplay), 0.021f, -1, coinsDelay); // framerate: 1/48
}

void GameScoreTimePanel::updateCoinsDisplay(float dt)
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
    this->unschedule(schedule_selector(GameScoreTimePanel::updateCoinsDisplay));
  }
  
  char str[256];
  sprintf(str, "%d", (int)(val));
  m_coinsEarnedLabel->setString(str);
  m_coinsEarnedLabel->setPositionX(this->m_textIndentRight - m_coinsEarnedLabel->getContentSize().width/2);  
}

void GameScoreTimePanel::updatePointsDisplay(float dt)
{
  m_elaspeTimePoints += dt;

  if (this->m_elaspeTimePoints >= this->m_targetTime * .25f)
  {
    this->m_pointsLabel->setVisible(true);
    this->m_pointsLabelDescription->setVisible(true);    
  }  
  if (this->m_elaspeTimePoints >= this->m_targetTime * .5f)
  {
    this->m_timingLabel->setVisible(true);
    this->m_timingLabelDescription->setVisible(true);    
  }
  if (this->m_elaspeTimePoints >= this->m_targetTime * .75f)
  {
    if (m_showAverageDuration)
    {
      this->m_durationLabel->setVisible(true);
      this->m_durationLabelDescription->setVisible(true);    
    }
  }
  if (this->m_elaspeTimePoints >= this->m_targetTime)
  {
    this->m_pointsLabel->setVisible(true);
    this->m_pointsLabelDescription->setVisible(true);
    this->m_timingLabel->setVisible(true);
    this->m_timingLabelDescription->setVisible(true);
    if (m_showAverageDuration)
    {
      this->m_durationLabel->setVisible(true);
      this->m_durationLabelDescription->setVisible(true);
    }
    this->m_scoreLabel->setVisible(true);
    this->m_scoreLabelDescription->setVisible(true);
        
    this->unschedule(schedule_selector(GameScoreTimePanel::updatePointsDisplay));
  }
}