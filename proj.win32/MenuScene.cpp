#include "MenuScene.h"

using namespace cocos2d;

void MenuScene::onEnter()
{
  CCScene::onEnter();
        // TODO (Roman): memory management for all enter methods
  if (!this->m_isInitialized)
  {  
    this->m_isInitialized = true;

    CCLOG("initializing MenuScene");
    CCPoint center = VisibleRect::center();

    CCSprite* bg = CCSprite::createWithSpriteFrame(m_gameContext->getImageMap()->getTile(0));
    bg->setPosition(center);
    this->addChild(bg, 0);
    
    CCRect visibleRect = VisibleRect::getVisibleRect();
    float top = visibleRect.size.height * .6f;
    float spacing = 50.0f;
    float buttonWidth = visibleRect.size.width * .75;

    /*************** HOME ***************/
    int counter = 0;
    m_homeStoryMode = new MenuButton(
      m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , m_gameContext->getImageMap()->getTile(6), m_gameContext->getImageMap()->getTile(7), m_gameContext->getImageMap()->getTile(8)
      , m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , buttonWidth, buttonWidth, buttonWidth
      , "STORY MODE", m_gameContext, menu_selector(MenuScene::showStoryModeMenu), this);
    m_homeStoryMode->setPosition(center.x, top - spacing*counter++);
    this->addChild(m_homeStoryMode);

#if GAME_VERSION < 2
    m_homeStoryMode->setVisible(false);
#endif

    m_homeArcade = new MenuButton(
      m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , m_gameContext->getImageMap()->getTile(6), m_gameContext->getImageMap()->getTile(7), m_gameContext->getImageMap()->getTile(8)
      , m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , buttonWidth, buttonWidth, buttonWidth
      , "ARCADE", m_gameContext, menu_selector(MenuScene::showArcadeMenu), this);
    m_homeArcade->setPosition(center.x, top - spacing*counter++);
    this->addChild(m_homeArcade);

    m_homeHighscore = new MenuButton(
      m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , m_gameContext->getImageMap()->getTile(6), m_gameContext->getImageMap()->getTile(7), m_gameContext->getImageMap()->getTile(8)
      , m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , buttonWidth, buttonWidth, buttonWidth
      , "HIGHSCORE", m_gameContext, menu_selector(MenuScene::showHighscore), this);
    m_homeHighscore->setPosition(center.x, top - spacing*counter++);
    this->addChild(m_homeHighscore);
    
    m_homeOptions = new MenuButton(
      m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , m_gameContext->getImageMap()->getTile(6), m_gameContext->getImageMap()->getTile(7), m_gameContext->getImageMap()->getTile(8)
      , m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , buttonWidth, buttonWidth, buttonWidth
      , "OPTIONS", m_gameContext, menu_selector(MenuScene::showOptions), this);
    m_homeOptions->setPosition(center.x, top - spacing*counter++);
    this->addChild(m_homeOptions);

    
    /*************** ARCADE ***************/
    m_arcadeEasy = new MenuButton(
      m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , m_gameContext->getImageMap()->getTile(6), m_gameContext->getImageMap()->getTile(7), m_gameContext->getImageMap()->getTile(8)
      , m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , buttonWidth, buttonWidth, buttonWidth
      , "EASY", m_gameContext, menu_selector(MenuScene::startArcadeEasyGameCallback), this);
    m_arcadeEasy->setPosition(center.x + visibleRect.size.width, top);
    this->addChild(m_arcadeEasy);

    m_arcadeClassic = new MenuButton(
      m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , m_gameContext->getImageMap()->getTile(6), m_gameContext->getImageMap()->getTile(7), m_gameContext->getImageMap()->getTile(8)
      , m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , buttonWidth, buttonWidth, buttonWidth
      , "CLASSIC", m_gameContext, menu_selector(MenuScene::startArcadeClassicGameCallback), this);
    m_arcadeClassic->setPosition(center.x + visibleRect.size.width, top - spacing);
    this->addChild(m_arcadeClassic);

    m_arcadeHard = new MenuButton(
      m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , m_gameContext->getImageMap()->getTile(6), m_gameContext->getImageMap()->getTile(7), m_gameContext->getImageMap()->getTile(8)
      , m_gameContext->getImageMap()->getTile(3), m_gameContext->getImageMap()->getTile(4), m_gameContext->getImageMap()->getTile(5)
      , buttonWidth, buttonWidth, buttonWidth
      , "HARD", m_gameContext, menu_selector(MenuScene::startArcadeHardGameCallback), this);
    m_arcadeHard->setPosition(center.x + visibleRect.size.width, top - spacing*2);
    this->addChild(m_arcadeHard);    

    /*************** STORY MODE ***************/
    int nextReleasingFrames[] = { 24 };
    int nextPressingFrames[] = { 24 };
    m_storyModeNextPage = ImageButton::create(this, callfuncO_selector(MenuScene::nextStoryModePage), NULL, m_gameContext
      , this->m_gameContext->getImageMapPListPath(), this->m_gameContext->getImageMapPngPath(), -1
      , 24
      , nextReleasingFrames, 1
      , nextPressingFrames, 1
      , 24
      , 24
      , TOUCH_PRIORITY_NORMAL);
    m_storyModeNextPage->setPosition(ccp( VisibleRect::right().x - 60, VisibleRect::top().y - 60 ) );
    m_storyModeNextPage->setVisible(false);
    
    int previousReleasingFrames[] = { 24 };
    int previousPressingFrames[] = { 24 };
    m_storyModePreviousPage = ImageButton::create(this, callfuncO_selector(MenuScene::previousStoryModePage), NULL, m_gameContext
      , this->m_gameContext->getImageMapPListPath(), this->m_gameContext->getImageMapPngPath(), -1
      , 24
      , previousReleasingFrames, 1
      , previousPressingFrames, 1
      , 24
      , 24
      , TOUCH_PRIORITY_NORMAL);
    m_storyModePreviousPage->setPosition(ccp( VisibleRect::left().x + 60, VisibleRect::top().y - 60 ) );
    m_storyModePreviousPage->setVisible(false);

    // 16 - 0
    // 17 - 1
    // 18 - 2
    // 19 - 3
    // 20 - locked
    int challenge_0_ReleasingFrames[] = { 20 };
    int challenge_0_PressingFrames[] = { 20 };
    int challenge_1_ReleasingFrames[] = { 16 };
    int challenge_1_PressingFrames[] = { 16 };
    int challenge_2_ReleasingFrames[] = { 17 };
    int challenge_2_PressingFrames[] = { 17 };
    int challenge_3_ReleasingFrames[] = { 18 };
    int challenge_3_PressingFrames[] = { 18 };
    int challenge_4_ReleasingFrames[] = { 19 };
    int challenge_4_PressingFrames[] = { 19 };
    
    int lastChallengeStatus = 1;
    int newChallengeStatus = 0;

    // TODO (Roman): positioning
    // TODO (Roman): proper images    
    int index = 0;
    ImageButton* imageButton;
    
    for (int i = 0; i < STORYMODE_TOTAL_PAGES; ++i)
    {
      for (int j = 0; j < STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE; ++j)
      {        
        for (int k = 0; k < STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE; ++k)
        {
          newChallengeStatus = this->m_gameContext->getChallengeInfo(index);
          switch (newChallengeStatus)
          {
          case 0: 
            if (lastChallengeStatus > 0)
            {
              imageButton = ImageButton::create(this, callfuncO_selector(MenuScene::startChallenge), NULL, m_gameContext
                , this->m_gameContext->getImageMapPListPath(), this->m_gameContext->getImageMapPngPath(), -1
                , 16
                , challenge_1_ReleasingFrames, 1
                , challenge_1_PressingFrames, 1
                , 16
                , 16
                , TOUCH_PRIORITY_NORMAL);
            }
            else
            {
              imageButton = ImageButton::create(this, callfuncO_selector(MenuScene::startChallenge), NULL, m_gameContext
                , this->m_gameContext->getImageMapPListPath(), this->m_gameContext->getImageMapPngPath(), -1
                , 20
                , challenge_0_ReleasingFrames, 1
                , challenge_0_PressingFrames, 1
                , 20
                , 20
                , TOUCH_PRIORITY_NORMAL);
            }
            lastChallengeStatus = 0;
          break;
          case 1: 
          imageButton = ImageButton::create(this, callfuncO_selector(MenuScene::startChallenge), NULL, m_gameContext
            , this->m_gameContext->getImageMapPListPath(), this->m_gameContext->getImageMapPngPath(), -1
            , 16
            , challenge_1_ReleasingFrames, 1
            , challenge_1_PressingFrames, 1
            , 16
            , 16
            , TOUCH_PRIORITY_NORMAL);
            lastChallengeStatus = 1;
          break;
          case 2: 
          imageButton = ImageButton::create(this, callfuncO_selector(MenuScene::startChallenge), NULL, m_gameContext
            , this->m_gameContext->getImageMapPListPath(), this->m_gameContext->getImageMapPngPath(), -1
            , 17
            , challenge_2_ReleasingFrames, 1
            , challenge_2_PressingFrames, 1
            , 17
            , 17
            , TOUCH_PRIORITY_NORMAL);
            lastChallengeStatus = 2;
          break;
          case 3: 
          imageButton = ImageButton::create(this, callfuncO_selector(MenuScene::startChallenge), NULL, m_gameContext
            , this->m_gameContext->getImageMapPListPath(), this->m_gameContext->getImageMapPngPath(), -1
            , 18
            , challenge_3_ReleasingFrames, 1
            , challenge_3_PressingFrames, 1
            , 18
            , 18
            , TOUCH_PRIORITY_NORMAL);
            lastChallengeStatus = 3;
          break;
          case 4: 
          imageButton = ImageButton::create(this, callfuncO_selector(MenuScene::startChallenge), NULL, m_gameContext
            , this->m_gameContext->getImageMapPListPath(), this->m_gameContext->getImageMapPngPath(), -1
            , 19
            , challenge_4_ReleasingFrames, 1
            , challenge_4_PressingFrames, 1
            , 19
            , 19
            , TOUCH_PRIORITY_NORMAL);
            lastChallengeStatus = 4;
          break;
          }

          imageButton->setVisible(false);
          this->m_challengeButtons.push_back(imageButton);
          index++;
          CCLOG("loop end %i %i %i %i", i, j, k, index);
        }
      }
    }

    CCLOG("set image button null");
    imageButton = NULL;

    CCLOG("finished initializing MenuScene");
  }
}

void MenuScene::resetHomeButtons(bool isVisible)
{
  m_homeStoryMode->setVisible(isVisible);
  m_homeArcade->setVisible(isVisible);
  m_homeOptions->setVisible(isVisible);
  m_homeHighscore->setVisible(isVisible);
}

void MenuScene::resetArcadeButtons(bool isVisible)
{
  m_arcadeEasy->setVisible(isVisible);
  m_arcadeClassic->setVisible(isVisible);
  m_arcadeHard->setVisible(isVisible);
}

void MenuScene::resetChallengeButtons(bool isVisible, bool areNavigationButtonsVisible)
{
  m_storyModeNextPage->setVisible(areNavigationButtonsVisible);
  m_storyModePreviousPage->setVisible(areNavigationButtonsVisible);

  ImageButton* imageButton;
  int totalChallenges = STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE 
                      * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE
                      * STORYMODE_TOTAL_PAGES;
  CCRect visibleRect = VisibleRect::getVisibleRect();

  float topY = visibleRect.size.height * .7;
  float leftX = visibleRect.origin.x + visibleRect.size.width * .2;
    
  int index = 0;
  for (int i = 0; i < STORYMODE_TOTAL_PAGES; ++i)
  {
    for (int j = 0; j < STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE; ++j)
    {        
      for (int k = 0; k < STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE; ++k)
      {
        imageButton = (ImageButton*)(this->m_challengeButtons.at(index));
          
        imageButton->setPosition(ccp(leftX + k * 80, topY - j * 80));
        imageButton->setVisible(isVisible);

        ++index;
      }
    }
  }
  imageButton = NULL;
}

void MenuScene::showView(MenuViewType menuViewType)
{
  CCLOG("Show scene");
  CCActionInterval* moveLeft = CCMoveBy::create(.3, ccp(-(VisibleRect::getVisibleRect().size.width),0));
  CCActionInterval* moveRight = CCMoveBy::create(.3, ccp((VisibleRect::getVisibleRect().size.width),0));
  
  CCPoint center = VisibleRect::center();
  CCRect visibleRect = VisibleRect::getVisibleRect();
  float easeRate = .5f;
  float posLeft = center.x - visibleRect.size.width;
  float posRight = center.x + visibleRect.size.width;

  switch(menuViewType)
  {
  case HOME:
        
    switch (m_menuViewType)
    {
    case STORY_MODE:
    
      resetHomeButtons(true);
      resetArcadeButtons(false);
      resetChallengeButtons(false, false);

      m_homeStoryMode->setPositionX(center.x);
      m_homeArcade->setPositionX(center.x);
      m_homeOptions->setPositionX(center.x);
      m_homeHighscore->setPositionX(center.x);

      break;

    case ARCADE:
      resetHomeButtons(true);
      resetArcadeButtons(true);
      resetChallengeButtons(false, false);

      m_homeStoryMode->setPositionX(posLeft);
      m_homeArcade->setPositionX(posLeft);
      m_homeOptions->setPositionX(posLeft);
      m_homeHighscore->setPositionX(posLeft);

      m_homeStoryMode->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      m_homeArcade->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      m_homeOptions->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      m_homeHighscore->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));    
    
      m_arcadeEasy->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      m_arcadeClassic->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      m_arcadeHard->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      break;
    }

    break;

  case ARCADE:
    
    resetHomeButtons(true);
    resetArcadeButtons(true);
    resetChallengeButtons(false, false);

    m_homeStoryMode->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    m_homeArcade->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    m_homeOptions->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    m_homeHighscore->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    
    m_arcadeEasy->setPositionX(posRight);
    m_arcadeClassic->setPositionX(posRight);
    m_arcadeHard->setPositionX(posRight);

    m_arcadeEasy->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    m_arcadeClassic->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    m_arcadeHard->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));

    break;

  case STORY_MODE:
  
    resetHomeButtons(false);
    resetArcadeButtons(false);
    resetChallengeButtons(false, true);

    this->m_storyModePreviousPage->setIsEnabled(false);
    this->m_storyModeNextPage->setIsEnabled(true);

    ImageButton* imageButton;
    for (int i = 0; i < STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE * STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE; i++)
    {
      imageButton = (ImageButton*)this->m_challengeButtons.at(i);
      imageButton->setVisible(true);
    }
    imageButton = NULL;

  break;
  }

  m_menuViewType = menuViewType;
}

void MenuScene::startArcadeEasyGameCallback(CCObject* pSender)
{ 
  NavigationManager::showScene(ARCADE_EASY_GAME_SCENE, m_gameContext, NEW);
}
void MenuScene::startArcadeHardGameCallback(CCObject* pSender)
{ 
  NavigationManager::showScene(ARCADE_HARD_GAME_SCENE, m_gameContext, NEW);
}
void MenuScene::startArcadeClassicGameCallback(CCObject* pSender)
{ 
  NavigationManager::showScene(ARCADE_CLASSIC_GAME_SCENE, m_gameContext, NEW);
}

void MenuScene::showStoryModeMenu(CCObject* pSender)
{ 
  showView(STORY_MODE);
}
void MenuScene::showArcadeMenu(CCObject* pSender)
{ 
  showView(ARCADE);
}

void MenuScene::startChallenge(CCObject* pSender)
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

  NavigationManager::showChallengeScene(m_gameContext, challengeIndex, NEW);
}
void MenuScene::nextStoryModePage(CCObject* pSender)
{  
  resetChallengeButtons(false, true);
  CCRect visibleRect = VisibleRect::getVisibleRect();

  float easeRate = .5f;
  CCActionInterval* moveLeft = CCMoveBy::create(.3, ccp(-(visibleRect.size.width),0));
  CCActionInterval* moveRight = CCMoveBy::create(.3, ccp((visibleRect.size.width),0));
    
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
  
  this->m_storyModePreviousPage->setIsEnabled(true);
  this->m_storyModeNextPage->setIsEnabled(this->m_storyModePageIndex < STORYMODE_TOTAL_PAGES - 1);
}
void MenuScene::previousStoryModePage(CCObject* pSender)
{  
  resetChallengeButtons(false, true);
  CCRect visibleRect = VisibleRect::getVisibleRect();

  float easeRate = .5f;
  CCActionInterval* moveLeft = CCMoveBy::create(.3, ccp(-(visibleRect.size.width),0));
  CCActionInterval* moveRight = CCMoveBy::create(.3, ccp((visibleRect.size.width),0));
    
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
  this->m_storyModePreviousPage->setIsEnabled(this->m_storyModePageIndex > 0);
  this->m_storyModeNextPage->setIsEnabled(true);
}

void MenuScene::showOptions(CCObject* pSender)
{ 
  NavigationManager::showScene(OPTIONS_SCENE, m_gameContext, NEW);
}
void MenuScene::showHighscore(CCObject* pSender)
{ 
  NavigationManager::showScene(HIGHSCORE_SCENE, m_gameContext, NEW);
}
void MenuScene::onBackKeyPressed()
{
  switch(m_menuViewType)
  {
  case HOME:
    CCDirector::sharedDirector()->end();
    break;

  case ARCADE:
  case STORY_MODE:
  case OPTIONS:
  case HIGHSCORE:
    showView(HOME);
    break;
  }
}

