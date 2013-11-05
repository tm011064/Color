#include "GameScorePointsPanel.h"

GameScorePointsPanel* GameScorePointsPanel::create(GameContext* gameContext, float width, ccColor4F separatorColor) 
{ 
  GameScorePointsPanel* gameScorePointsPanel = new GameScorePointsPanel(gameContext, width, separatorColor);
  gameScorePointsPanel->autorelease();
  return gameScorePointsPanel;
}

void GameScorePointsPanel::onEnter()
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

    float verticalSpacing = (m_pGameContext->getFontHeightNormal() + m_padding)*this->m_pGameContext->getFontScale();
    float verticalSpacingLarge = (m_pGameContext->getFontHeightLarge() + m_padding*3)*this->m_pGameContext->getFontScale();
    
    char str[256];        

    float posY = -(this->m_pGameContext->getFontHeightNormal()/2 * this->m_pGameContext->getFontScale());    
    m_pointsLabelDescription = CCLabelBMFont::create("Points", m_pGameContext->getFontNormalPath().c_str());
    m_pointsLabelDescription->setScale(this->m_pGameContext->getFontScale());
    m_pointsLabelDescription->setPosition(
      this->m_textIndentLeft + m_pointsLabelDescription->getContentSize().width/2*this->m_pGameContext->getFontScale()
      , posY);
    this->addChild(m_pointsLabelDescription);
    sprintf(str, "%i", (int)(gameScore.totalPoints));
    m_pointsLabel = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    m_pointsLabel->setScale(this->m_pGameContext->getFontScale());
    m_pointsLabel->setPosition(this->m_textIndentRight - m_pointsLabel->getContentSize().width/2*this->m_pGameContext->getFontScale(), posY);
    this->addChild(m_pointsLabel);
    
    posY -= verticalSpacing;
    m_levelBonusLabelDescription = CCLabelBMFont::create("Level bonus", m_pGameContext->getFontNormalPath().c_str());
    m_levelBonusLabelDescription->setScale(this->m_pGameContext->getFontScale());
    m_levelBonusLabelDescription->setPosition(this->m_textIndentLeft + m_levelBonusLabelDescription->getContentSize().width/2*this->m_pGameContext->getFontScale(), posY);
    this->addChild(m_levelBonusLabelDescription);
    sprintf(str, "%i", (int)(gameScore.totalLevelBonus));
    m_levelBonusLabel = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    m_levelBonusLabel->setScale(this->m_pGameContext->getFontScale());
    m_levelBonusLabel->setPosition(this->m_textIndentRight - m_levelBonusLabel->getContentSize().width/2*this->m_pGameContext->getFontScale(), posY);
    this->addChild(m_levelBonusLabel);
    
    posY -= verticalSpacing;
    m_timeBonusLabelDescription = CCLabelBMFont::create("Time bonus", m_pGameContext->getFontNormalPath().c_str());
    m_timeBonusLabelDescription->setScale(this->m_pGameContext->getFontScale());
    m_timeBonusLabelDescription->setPosition(this->m_textIndentLeft + m_timeBonusLabelDescription->getContentSize().width/2*this->m_pGameContext->getFontScale(), posY);
    this->addChild(m_timeBonusLabelDescription);
    sprintf(str, "%i", (int)(gameScore.totalButtonBonus));
    m_timeBonusLabel = CCLabelBMFont::create(str, m_pGameContext->getFontNormalPath().c_str());
    m_timeBonusLabel->setScale(this->m_pGameContext->getFontScale());
    m_timeBonusLabel->setPosition(this->m_textIndentRight - m_timeBonusLabel->getContentSize().width/2*this->m_pGameContext->getFontScale(), posY);
    this->addChild(m_timeBonusLabel);
    
    posY -= (verticalSpacing/2);
    m_separatorLineLeftBottom = ccpRounded ( this->m_textIndentLeft, posY - this->m_borderThickness );
    m_separatorLineRightTop = ccpRounded ( this->m_textIndentRight, posY );
  
    posY -= (verticalSpacing/2 + this->m_padding * 6);
    CCLabelBMFont* label = CCLabelBMFont::create("Total Points", m_pGameContext->getFontNormalPath().c_str());
    label->setScale(this->m_pGameContext->getFontScale());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2*this->m_pGameContext->getFontScale(), posY);
    this->addChild(label);
    m_totalPointsLabel = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    m_totalPointsLabel->setScale(this->m_pGameContext->getFontScale());
    m_totalPointsLabel->setPosition(this->m_textIndentRight - m_totalPointsLabel->getContentSize().width/2*this->m_pGameContext->getFontScale(), posY);
    this->addChild(m_totalPointsLabel);

    posY -= verticalSpacing;
    label = CCLabelBMFont::create("Coins earned", m_pGameContext->getFontNormalPath().c_str());
    label->setScale(this->m_pGameContext->getFontScale());
    label->setPosition(this->m_textIndentLeft + label->getContentSize().width/2*this->m_pGameContext->getFontScale(), posY);
    this->addChild(label);
    m_coinsEarnedLabel = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    m_coinsEarnedLabel->setScale(this->m_pGameContext->getFontScale());
    m_coinsEarnedLabel->setPosition(this->m_textIndentRight - m_coinsEarnedLabel->getContentSize().width/2*this->m_pGameContext->getFontScale(), posY);
    this->addChild(m_coinsEarnedLabel);
        
    posY -= this->m_pGameContext->getFontHeightNormal()/2 * this->m_pGameContext->getFontScale();
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
    m_separatorLineLeftBottom.y += round(posY);
    m_separatorLineRightTop.y += round(posY);
  }
}

void GameScorePointsPanel::refresh()
{
  char str[256];        
  GameScore gameScore = m_pGameContext->getGameScore();
  
  m_totalPointsLabel->setString("0");
  m_totalPointsLabel->setPositionX(this->m_textIndentRight - m_totalPointsLabel->getContentSize().width/2*this->m_pGameContext->getFontScale());
  
  sprintf(str, "+%i", (int)(gameScore.totalPoints - gameScore.totalLevelBonus - gameScore.totalButtonBonus));
  m_pointsLabel->setString(str);
  m_pointsLabel->setPositionX(this->m_textIndentRight - m_pointsLabel->getContentSize().width/2*this->m_pGameContext->getFontScale());
  m_pointsLabel->setVisible(false);
  
  sprintf(str, "+%i", (int)(gameScore.totalLevelBonus));
  m_levelBonusLabel->setString(str);
  m_levelBonusLabel->setPositionX(this->m_textIndentRight - m_levelBonusLabel->getContentSize().width/2*this->m_pGameContext->getFontScale());
  m_levelBonusLabel->setVisible(false);

  sprintf(str, "+%i", (int)(gameScore.totalButtonBonus));
  m_timeBonusLabel->setString(str);
  m_timeBonusLabel->setPositionX(this->m_textIndentRight - m_timeBonusLabel->getContentSize().width/2*this->m_pGameContext->getFontScale());
  m_timeBonusLabel->setVisible(false);

  m_coinsEarnedLabel->setString("0");
  m_coinsEarnedLabel->setPositionX(this->m_textIndentRight - m_coinsEarnedLabel->getContentSize().width/2*this->m_pGameContext->getFontScale());
  m_coinsEarnedLabel->setVisible(false);

  m_pointsLabelDescription->setVisible(false);
  m_levelBonusLabelDescription->setVisible(false);
  m_timeBonusLabelDescription->setVisible(false);
}

void GameScorePointsPanel::draw()
{ 
  ccDrawSolidRect(m_separatorLineLeftBottom, m_separatorLineRightTop, m_separatorColor);
}

void GameScorePointsPanel::show()
{
  BaseNode::show();

  // get the score
  this->refresh();

  // now start animation... 
  float coinsDelay = .8f;

  this->m_elaspeTimePoints = 0;
  this->m_elaspeTimeCoins = -coinsDelay;
  this->m_targetTime = .8f;

  this->schedule(schedule_selector(GameScorePointsPanel::updatePointsDisplay), 0.021f); // framerate: 1/48
  this->schedule(schedule_selector(GameScorePointsPanel::updateCoinsDisplay), 0.021f, -1, coinsDelay); // framerate: 1/48
}

void GameScorePointsPanel::updateCoinsDisplay(float dt)
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
    this->unschedule(schedule_selector(GameScorePointsPanel::updateCoinsDisplay));
  }
  
  char str[256];
  sprintf(str, "%d", (int)(val));
  m_coinsEarnedLabel->setString(str);
  m_coinsEarnedLabel->setPositionX(this->m_textIndentRight - m_coinsEarnedLabel->getContentSize().width/2*this->m_pGameContext->getFontScale());  
}

void GameScorePointsPanel::updatePointsDisplay(float dt)
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
    
    this->unschedule(schedule_selector(GameScorePointsPanel::updatePointsDisplay));
  }

  m_totalPointsLabel->setString(UtilityHelper::convertToString((int)val).c_str());
  m_totalPointsLabel->setPositionX(this->m_textIndentRight - m_totalPointsLabel->getContentSize().width/2*this->m_pGameContext->getFontScale());  
}