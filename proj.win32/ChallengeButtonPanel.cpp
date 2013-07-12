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
    ImageButton* imageButton;
    
    for (int i = 0; i < STORYMODE_TOTAL_PAGES; ++i)
    {
      for (int j = 0; j < STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE; ++j)
      {        
        for (int k = 0; k < STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE; ++k)
        {
          newChallengeStatus = this->m_pGameContext->getChallengeInfo(index);
          switch (newChallengeStatus)
          {
          case 0: 
            if (lastChallengeStatus > 0)
            {
              imageButton = ImageButton::create(this
                , callfuncO_selector(ChallengeButtonPanel::startChallenge)
                , NULL
                , m_pGameContext
                , "challengeButton_N"
                , -1
                , 0
                , pressingFrames, 1
                , releasingFrames, 1
                , 0
                , 0
                , TOUCH_PRIORITY_NORMAL);
              this->addChild(imageButton);
            }
            else
            {
              imageButton = ImageButton::create(this
                , callfuncO_selector(ChallengeButtonPanel::startChallenge)
                , NULL
                , m_pGameContext
                , "challengeButton_L"
                , -1
                , 0
                , pressingFrames, 1
                , releasingFrames, 1
                , 0
                , 0
                , TOUCH_PRIORITY_NORMAL);
              this->addChild(imageButton);
            }
            lastChallengeStatus = 0;
          break;
          case 1: 
              imageButton = ImageButton::create(this
                , callfuncO_selector(ChallengeButtonPanel::startChallenge)
                , NULL
                , m_pGameContext
                , "challengeButton_1"
                , -1
                , 0
                , pressingFrames, 1
                , releasingFrames, 1
                , 0
                , 0
                , TOUCH_PRIORITY_NORMAL);
              this->addChild(imageButton);
          break;
          case 2: 
              imageButton = ImageButton::create(this
                , callfuncO_selector(ChallengeButtonPanel::startChallenge)
                , NULL
                , m_pGameContext
                , "challengeButton_2"
                , -1
                , 0
                , pressingFrames, 1
                , releasingFrames, 1
                , 0
                , 0
                , TOUCH_PRIORITY_NORMAL);
              this->addChild(imageButton);
          break;
          case 3: 
              imageButton = ImageButton::create(this
                , callfuncO_selector(ChallengeButtonPanel::startChallenge)
                , NULL
                , m_pGameContext
                , "challengeButton_3"
                , -1
                , 0
                , pressingFrames, 1
                , releasingFrames, 1
                , 0
                , 0
                , TOUCH_PRIORITY_NORMAL);
              this->addChild(imageButton);
          break;
          }

          imageButton->setVisible(false);
          this->m_challengeButtons.push_back(imageButton);
          index++;
        }
      }
    }

    imageButton = NULL;
  }
}


void ChallengeButtonPanel::startChallenge(CCObject* pSender)
{
  ImageButton* sender = (ImageButton*)pSender;
  
  int challengeIndex = 0;
  std::vector<ImageButton*>::iterator it;
  for(it=this->m_challengeButtons.begin();it!=this->m_challengeButtons.end();++it)
  {
    if (*it == sender)
    {
      challengeIndex = it - this->m_challengeButtons.begin();
      break;
    }
  }

  NavigationManager::showChallengeScene(m_pGameContext, challengeIndex, NEW);
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
    
  ImageButton* imageButton;
  
  int startIndex = this->m_storyModePageIndex * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
  int endIndex = (this->m_storyModePageIndex + 1 ) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
  for (int i = startIndex; i < endIndex; ++i)
  {
    imageButton = (ImageButton*)this->m_challengeButtons.at(i);
    imageButton->setVisible(true);
    imageButton->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
  }
  startIndex = (this->m_storyModePageIndex + 1) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
  endIndex = (this->m_storyModePageIndex + 2 ) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
  for (int i = startIndex; i < endIndex; ++i)
  {
    imageButton = (ImageButton*)this->m_challengeButtons.at(i);
    imageButton->setVisible(true);
    imageButton->setPositionX(imageButton->getPositionX() + visibleRect.size.width);
    imageButton->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
  }

  imageButton = NULL;

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
    
    ImageButton* imageButton;
  
    int startIndex = this->m_storyModePageIndex * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
    int endIndex = (this->m_storyModePageIndex + 1 ) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
    for (int i = startIndex; i < endIndex; ++i)
    {
      imageButton = (ImageButton*)this->m_challengeButtons.at(i);
      imageButton->setVisible(true);
      imageButton->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
    }
    startIndex = (this->m_storyModePageIndex - 1) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
    endIndex = (this->m_storyModePageIndex ) * STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE;
    for (int i = startIndex; i < endIndex; ++i)
    {
      imageButton = (ImageButton*)this->m_challengeButtons.at(i);
      imageButton->setVisible(true);
      imageButton->setPositionX(imageButton->getPositionX() - visibleRect.size.width);
      imageButton->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
    }

    imageButton = NULL;

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

  float targetedSpacingToButtonRatio = 1.38f;

  CCSize size = this->m_storyModeNextPage->getSize();

  this->m_storyModeNextPage->setPosition(
    rightTop.x - size.width/2 - size.height * .618 - position.x
    , leftBottom.y + size.height/2 + size.height * .618 - position.y);
  
  this->m_storyModePreviousPage->setPosition(
    leftBottom.x + size.width/2 + size.height * .618 - position.x
    , leftBottom.y + size.height/2 + size.height * .618 - position.y);

  if (this->m_challengeButtons.size() <= 0)
    return;

  size = ((ImageButton*)(this->m_challengeButtons.at(0)))->getContentSize();
  
  float availableHeight = rightTop.y - leftBottom.y;
  float availableWidth = rightTop.x - leftBottom.x;
    
  float horizontalSpacing = round( size.width * targetedSpacingToButtonRatio );
  float overallWidth = horizontalSpacing * (STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE - 1) + size.width; 
  if (overallWidth > availableWidth)
  {
    horizontalSpacing = (availableWidth - size.width*STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE) / STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE + size.width;
    overallWidth = horizontalSpacing * (STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE - 1) + size.width;
  }
  float posX = round ( leftBottom.x + (availableWidth - overallWidth)/2 + size.width/2 ) - position.x;
  
  float verticalSpacing = round( size.height * targetedSpacingToButtonRatio );
  float overallHeight = verticalSpacing * (STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE - 1) + size.height; 
  if (overallHeight > availableHeight)
  {
    verticalSpacing = (availableHeight - size.height*STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE) / STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE + size.height;
    overallHeight = verticalSpacing * (STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE - 1) + size.height;
  }
  float posY = round ( rightTop.y - (availableHeight - overallHeight)/2 - size.height/2 ) - position.y;

  ImageButton* imageButton;
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
        imageButton = (ImageButton*)(this->m_challengeButtons.at(index));
          
        imageButton->setPosition(ccp(posX, posY));
        imageButton->setVisible(isVisible);

        ++index;
        posX += horizontalSpacing;
      }
      posY -= verticalSpacing;
      posX = basePosX;
    }
  }
  imageButton = NULL;
}

void ChallengeButtonPanel::reset()
{
  this->m_storyModePageIndex = 0;
  resetChallengeButtons(false);

  ImageButton* imageButton;
  for (int i = 0; i < STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE; i++)
  {
    imageButton = (ImageButton*)this->m_challengeButtons.at(i);
    imageButton->setVisible(true);
  }
  imageButton = NULL;
}