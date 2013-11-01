#include "ChallengeButtonPanel.h"

ChallengeButtonPanel* ChallengeButtonPanel::create(GameContext* gameContext
  , SEL_CallFunc goBackDelegate, CCNode* callbackTarget)
{
  ChallengeButtonPanel* challengeButtonPanel = new ChallengeButtonPanel(gameContext, goBackDelegate, callbackTarget);
  challengeButtonPanel->autorelease();
  return challengeButtonPanel;
}

void ChallengeButtonPanel::onEnter()
{
  CCNode::onEnter();

  if (!this->m_isLayoutInitialized)
  {    
    this->m_isLayoutInitialized = true;
            
    /*************** STORY MODE ***************/    
    CCPoint rightTop = VisibleRect::rightTop();
    CCPoint leftTop = VisibleRect::leftTop();
    CCPoint position = this->getPosition();
    
    m_rectOrigin = ccpRounded (leftTop.x - position.x
      , leftTop.y - m_pGameContext->getFontHeightNormal() - m_pGameContext->getDefaultPadding() * 3 - position.y);
    m_rectDestination = ccpRounded (rightTop.x - position.x, rightTop.y - position.y);
    
    m_borderOrigin = ccp (m_rectOrigin.x, m_rectOrigin.y - m_pGameContext->getDefaultBorderThickness());
    m_borderDestination = ccp (m_rectDestination.x, m_rectOrigin.y);
    
    m_heart = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("heart_small"));
    m_heart->setPosition(ccp(m_rectDestination.x - m_pGameContext->getDefaultPadding() * 3 - m_heart->getContentSize().width/2
      , m_rectDestination.y - m_pGameContext->getDefaultPadding() * 2 - m_pGameContext->getFontHeightNormal()/2));
    this->addChild(m_heart);

    m_rectColor.r = 0;
    m_rectColor.g = 0;
    m_rectColor.b = 0;
    m_rectColor.a = 1;
    m_borderColor.r = .5;
    m_borderColor.g = .5;
    m_borderColor.b = .5;
    m_borderColor.a = 1;


    m_storyModeNextPage = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "next"
      , m_pGameContext->getDefaultButtonSize()
      , m_pGameContext->getDefaultBorderThickness()
      , this->m_pGameContext
      , callfuncO_selector(ChallengeButtonPanel::nextStoryModePage)
      , this);
    this->addChild(m_storyModeNextPage);
    
    m_storyModePreviousPage = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
      , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
      , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
      , "back"
      , m_pGameContext->getDefaultButtonSize()
      , m_pGameContext->getDefaultBorderThickness()
      , this->m_pGameContext
      , callfuncO_selector(ChallengeButtonPanel::previousStoryModePage)
      , this);
    this->addChild(m_storyModePreviousPage);
                
    int releasingFrames[] = { 0 };
    int pressingFrames[] = { 0 };
    
    int lastChallengeStatus = 1;
    int newChallengeStatus = 0;
   
    int index = 0;
    ChallengeButton* challengeButton;
    
    std::string challengeButtonIconName;
    ChallengePointScoreDefinition challengePointScoreDefinition;

    for (int i = 0; i < STORYMODE_TOTAL_PAGES; ++i)
    {
      for (int j = 0; j < STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE; ++j)
      {        
        for (int k = 0; k < STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE; ++k)
        {
          newChallengeStatus = this->m_pGameContext->getChallengeInfo(index);

          if ( newChallengeStatus == 0 && lastChallengeStatus <= 0 )
          {
            challengeButton = ChallengeButton::create(index, REACH_LEVEL, -1, m_pGameContext
              , callfuncO_selector(ChallengeButtonPanel::startChallenge), this);
            lastChallengeStatus = 0;
          }
          else
          {
            challengePointScoreDefinition = this->m_pGameContext->getChallengePointScoreDefinition(index);
            challengeButton = ChallengeButton::create(index, challengePointScoreDefinition.challengeSceneType
              , newChallengeStatus
              , m_pGameContext
              , callfuncO_selector(ChallengeButtonPanel::startChallenge), this);
            
            if ( newChallengeStatus == 0 )
              lastChallengeStatus = 0;
          }

          this->addChild(challengeButton);

          challengeButton->setVisible(false);
          this->m_challengeButtons.push_back(challengeButton);
          index++;
        }
      }
    }

    challengeButton = NULL;
        
    m_nextLifeText_Left = CCLabelBMFont::create("( next life in ", m_pGameContext->getFontNormalPath().c_str());
    this->addChild(m_nextLifeText_Left);
    
    m_nextLifeText_Right = CCLabelBMFont::create(" )", m_pGameContext->getFontNormalPath().c_str());
    this->addChild(m_nextLifeText_Right);

    m_totalLifeLabel = CCLabelBMFont::create("NA", m_pGameContext->getFontNormalPath().c_str());
    this->addChild(m_totalLifeLabel);
    
    m_deltaNextLifeIncreaseLabel_Separator = CCLabelBMFont::create(":", m_pGameContext->getFontNormalPath().c_str());
    this->addChild(m_deltaNextLifeIncreaseLabel_Separator);

    m_deltaNextLifeIncreaseLabel_M1 = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    this->addChild(m_deltaNextLifeIncreaseLabel_M1);
    
    m_deltaNextLifeIncreaseLabel_M2 = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    this->addChild(m_deltaNextLifeIncreaseLabel_M2);

    m_deltaNextLifeIncreaseLabel_S2 = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    this->addChild(m_deltaNextLifeIncreaseLabel_S2);
    
    m_deltaNextLifeIncreaseLabel_S1 = CCLabelBMFont::create("0", m_pGameContext->getFontNormalPath().c_str());
    this->addChild(m_deltaNextLifeIncreaseLabel_S1);

    updateLifeDisplay(.0f);
    this->schedule(schedule_selector(ChallengeButtonPanel::updateLifeDisplay), 1);    
  }
}

void ChallengeButtonPanel::updateLifeDisplay(float dt)
{
  LifeInfo lifeInfo = this->m_pGameContext->refreshTotalLifesCount();

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

void ChallengeButtonPanel::startChallenge(CCObject* pSender)
{
  ChallengeButton* sender = (ChallengeButton*)pSender;
  
  int challengeIndex = 0;
  std::vector<ChallengeButton*>::iterator it;
  for(it=this->m_challengeButtons.begin();it!=this->m_challengeButtons.end();++it)
  {
    if (*it == sender)
    {
      challengeIndex = it - this->m_challengeButtons.begin();
      break;
    }
  }

  NavigationManager::showChallengeScene(m_pGameContext, challengeIndex, NEW, true);
}

void ChallengeButtonPanel::goBackCallback(CCObject* pSender)
{
  if(m_pTarget != 0 && this->m_fnpGoBackDelegate != 0)
    (m_pTarget->*this->m_fnpGoBackDelegate)();
}

void ChallengeButtonPanel::nextStoryModePage(CCObject* pSender)
{  
  resetChallengeButtons(false);
  CCRect visibleRect = VisibleRect::getVisibleRect();

  float easeRate = .5f;
  CCActionInterval* moveLeft = CCMoveBy::create(.3f, ccp(-(visibleRect.size.width),0));
  CCActionInterval* moveRight = CCMoveBy::create(.3f, ccp((visibleRect.size.width),0));
    
  ChallengeButton* challengeButton;
  
  int startIndex = this->m_storyModePageIndex * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
  int endIndex = (this->m_storyModePageIndex + 1 ) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
  for (int i = startIndex; i < endIndex; ++i)
  {
    challengeButton = (ChallengeButton*)this->m_challengeButtons.at(i);
    challengeButton->setVisible(true);
    challengeButton->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
  }
  startIndex = (this->m_storyModePageIndex + 1) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
  endIndex = (this->m_storyModePageIndex + 2 ) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
  for (int i = startIndex; i < endIndex; ++i)
  {
    challengeButton = (ChallengeButton*)this->m_challengeButtons.at(i);
    challengeButton->setVisible(true);
    challengeButton->setPositionX(challengeButton->getPositionX() + visibleRect.size.width);
    challengeButton->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
  }

  challengeButton = NULL;

  this->m_storyModePageIndex++;

  this->m_storyModeNextPage->setVisible(this->m_storyModePageIndex < STORYMODE_TOTAL_PAGES - 1);
}
void ChallengeButtonPanel::previousStoryModePage(CCObject* pSender)
{  
  if (this->m_storyModePageIndex == 0)
  {
    this->goBackCallback(this);
  }
  else
  {
    resetChallengeButtons(false);
    CCRect visibleRect = VisibleRect::getVisibleRect();

    float easeRate = .5f;
    CCActionInterval* moveLeft = CCMoveBy::create(.3f, ccp(-(visibleRect.size.width),0));
    CCActionInterval* moveRight = CCMoveBy::create(.3f, ccp((visibleRect.size.width),0));
    
    ChallengeButton* challengeButton;
  
    int startIndex = this->m_storyModePageIndex * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
    int endIndex = (this->m_storyModePageIndex + 1 ) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
    for (int i = startIndex; i < endIndex; ++i)
    {
      challengeButton = (ChallengeButton*)this->m_challengeButtons.at(i);
      challengeButton->setVisible(true);
      challengeButton->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
    }
    startIndex = (this->m_storyModePageIndex - 1) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
    endIndex = (this->m_storyModePageIndex ) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
    for (int i = startIndex; i < endIndex; ++i)
    {
      challengeButton = (ChallengeButton*)this->m_challengeButtons.at(i);
      challengeButton->setVisible(true);
      challengeButton->setPositionX(challengeButton->getPositionX() - visibleRect.size.width);
      challengeButton->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
    }

    challengeButton = NULL;

    this->m_storyModePageIndex--;

    this->m_storyModeNextPage->setVisible(STORYMODE_TOTAL_PAGES > 1);
  }
}

void ChallengeButtonPanel::resetChallengeButtons(bool isVisible)
{  
  this->m_storyModeNextPage->setVisible(STORYMODE_TOTAL_PAGES > 1);
  
  CCPoint position = this->getPosition();
  
  CCPoint rightTop = VisibleRect::rightTop();
  CCPoint leftBottom = VisibleRect::leftBottom();
  CCPoint leftTop = VisibleRect::leftTop();

  float targetedSpacingToButtonRatio = 1.08f;

  float posX, posY;
  
  if (this->m_challengeButtons.size() <= 0)
    return;

  CCSize size = ((ChallengeButton*)(this->m_challengeButtons.at(0)))->getSize();
  
  float availableHeight = rightTop.y - leftBottom.y;
  float availableWidth = rightTop.x - leftBottom.x;
    
  float horizontalSpacing = round( size.width * targetedSpacingToButtonRatio );
  float overallWidth = horizontalSpacing * (STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE - 1) + size.width; 
  if (overallWidth > availableWidth)
  {
    horizontalSpacing = (availableWidth - size.width*STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE) / STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE + size.width;
    overallWidth = horizontalSpacing * (STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE - 1) + size.width;
  }
  
  float verticalSpacing = round( size.height * targetedSpacingToButtonRatio );
  float overallHeight = verticalSpacing * (STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE - 1) + size.height; 
  if (overallHeight > availableHeight)
  {
    verticalSpacing = (availableHeight - size.height*STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE) / STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE + size.height;
    overallHeight = verticalSpacing * (STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE - 1) + size.height;
  }

  if ( horizontalSpacing > verticalSpacing )
  {
    horizontalSpacing = verticalSpacing;
    overallWidth = horizontalSpacing * (STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE - 1) + size.width;
  }
  else
  {
    verticalSpacing = horizontalSpacing;
    overallHeight = verticalSpacing * (STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE - 1) + size.height;
  }
  
  posX = round ( leftBottom.x + (availableWidth - overallWidth)/2 + size.width/2 ) - position.x;
  posY = round ( rightTop.y - (availableHeight - overallHeight)/2 - size.height/2 ) - position.y;
  
  ChallengeButton* challengeButton;
  int index = 0;
  float basePosX = posX;
  float basePosY = posY;
  for (int i = 0; i < STORYMODE_TOTAL_PAGES; ++i)
  {
    posX = basePosX;
    posY = basePosY;

    for (int j = 0; j < STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE; ++j)
    {        
      for (int k = 0; k < STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE; ++k)
      {
        challengeButton = (ChallengeButton*)(this->m_challengeButtons.at(index));
          
        challengeButton->setPosition(ccp(posX, posY));
        challengeButton->setVisible(isVisible);

        ++index;
        posX += horizontalSpacing;
      }
      posY -= verticalSpacing;
      posX = basePosX;
    }
  }
  challengeButton = NULL;
  
  posX = leftBottom.x + (availableWidth - overallWidth)/2 - position.x;
  size = this->m_storyModeNextPage->getSize();
  this->m_storyModeNextPage->setPosition(    
    posX + overallWidth - size.width/2 - m_pGameContext->getDefaultPadding()*2
    , posY);
  
  this->m_storyModePreviousPage->setPosition(
    posX + size.width/2 + m_pGameContext->getDefaultPadding()*2
    , this->m_storyModeNextPage->getPositionY());
  
  posY = m_heart->getPositionY();
  
  this->m_totalLifeLabel->setPosition( 
    posX + m_totalLifeLabel->getContentSize().width/2 + m_pGameContext->getDefaultPadding()*2
    , posY);
  m_heart->setPositionX(m_totalLifeLabel->getPositionX() + m_totalLifeLabel->getContentSize().width/2
    + this->m_pGameContext->getDefaultPadding()*2 + m_heart->getContentSize().width/2 );

  m_nextLifeText_Left->setPosition( m_heart->getPositionX() + m_heart->getContentSize().width/2
    + this->m_pGameContext->getDefaultPadding()*2 + m_nextLifeText_Left->getContentSize().width/2
    , posY);

  float separatorWidth = m_deltaNextLifeIncreaseLabel_Separator->getContentSize().width;

  m_deltaNextLifeIncreaseLabel_Separator->setPosition(m_nextLifeText_Left->getPositionX()
    + m_nextLifeText_Left->getContentSize().width/2 + m_pGameContext->getMaxDigitFontNormalWidth()*3
    , posY);
 
  m_deltaNextLifeIncreaseLabel_M1->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() - separatorWidth/2 - m_pGameContext->getDefaultPadding()*2 - m_pGameContext->getMaxDigitFontNormalWidth()*1.5, m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
  m_deltaNextLifeIncreaseLabel_M2->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() - separatorWidth/2 - m_pGameContext->getDefaultPadding() - m_pGameContext->getMaxDigitFontNormalWidth()*.5, m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
  m_deltaNextLifeIncreaseLabel_S2->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() + separatorWidth/2 + m_pGameContext->getDefaultPadding()*2 + m_pGameContext->getMaxDigitFontNormalWidth()*1.5, m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
  m_deltaNextLifeIncreaseLabel_S1->setPosition(m_deltaNextLifeIncreaseLabel_Separator->getPositionX() + separatorWidth/2 + m_pGameContext->getDefaultPadding() + m_pGameContext->getMaxDigitFontNormalWidth()*.5, m_deltaNextLifeIncreaseLabel_Separator->getPositionY());
  
  m_nextLifeText_Right->setPosition( m_deltaNextLifeIncreaseLabel_S2->getPositionX() + m_deltaNextLifeIncreaseLabel_S2->getContentSize().width/2
    + m_nextLifeText_Right->getContentSize().width/2
    , posY);
    
  this->updateLifeDisplay(.0f);
}

void ChallengeButtonPanel::reset()
{
  this->m_storyModePageIndex = 0;
  resetChallengeButtons(false);

  ChallengeButton* challengeButton;
  for (int i = 0; i < STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE; i++)
  {
    challengeButton = (ChallengeButton*)this->m_challengeButtons.at(i);
    challengeButton->setVisible(true);
  }
  challengeButton = NULL;
}

void ChallengeButtonPanel::draw()
{     
  ccDrawSolidRect(m_rectOrigin, m_rectDestination, m_rectColor);
  ccDrawSolidRect(m_borderOrigin, m_borderDestination, m_borderColor);
}