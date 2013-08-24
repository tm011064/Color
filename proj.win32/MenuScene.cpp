#include "MenuScene.h"

using namespace cocos2d;

void MenuScene::initialize(float dt)
{
  CCPoint center = VisibleRect::center();
  CCPoint rightTop = VisibleRect::rightTop();
  CCPoint leftBottom = VisibleRect::leftBottom();
  CCRect visibleRect = VisibleRect::getVisibleRect();
            
  RepeatingSprite* bg = RepeatingSprite::create(
    m_pGameContext
    , m_pGameContext->getImageMap()->getTile("background")
    , HORIZONTAL
    , NORMAL
    , visibleRect.size);
  bg->setPosition(center);
  this->addChild(bg, 0);
  bg = NULL;
        
  m_header = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("header"));
  CCSize size = m_header->getContentSize();
  m_header->setScale(visibleRect.size.width / size.height); 
  m_header->setRotation(-90);
  m_header->setPosition(ccp(center.x, rightTop.y - (size.width / 2) * m_header->getScale()));
  this->addChild(m_header);

  float buttonWidth = visibleRect.size.width * .75;
        
  /*************** HOME ***************/
  m_homeStoryMode = MenuButton::create(
    m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_on_left"), m_pGameContext->getImageMap()->getTile("menubutton_on_center"), m_pGameContext->getImageMap()->getTile("menubutton_on_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , buttonWidth, buttonWidth, buttonWidth
    , "CHALLENGES", m_pGameContext, menu_selector(MenuScene::showStoryModeMenu), this);
  this->addChild(m_homeStoryMode);
        
  float topY = round( rightTop.y - size.width*m_header->getScale());
  float availableHeight = round( topY - leftBottom.y );
    
  CCSize buttonSize = this->m_homeStoryMode->getContentSize();
  float posY, spacing;
  float targetedSpacingToButtonHeightRatio = 1.38f;

  CalculateButtonLayoutCoordinates(topY, buttonSize.height, targetedSpacingToButtonHeightRatio, availableHeight, 4, posY, spacing);
    
  m_homeStoryMode->setPosition(center.x, posY);

#if GAME_VERSION < 2
  m_homeStoryMode->setVisible(false);
#endif

  posY -= spacing;
  m_homeArcade = MenuButton::create(
    m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_on_left"), m_pGameContext->getImageMap()->getTile("menubutton_on_center"), m_pGameContext->getImageMap()->getTile("menubutton_on_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , buttonWidth, buttonWidth, buttonWidth
    , "ARCADE", m_pGameContext, menu_selector(MenuScene::showArcadeMenu), this);
  m_homeArcade->setPosition(center.x, posY);
  this->addChild(m_homeArcade);
    
  posY -= spacing;
  m_homeHighscore = MenuButton::create(
    m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_on_left"), m_pGameContext->getImageMap()->getTile("menubutton_on_center"), m_pGameContext->getImageMap()->getTile("menubutton_on_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , buttonWidth, buttonWidth, buttonWidth
    , "HIGHSCORE", m_pGameContext, menu_selector(MenuScene::showHighscore), this);
  m_homeHighscore->setPosition(center.x, posY);
  this->addChild(m_homeHighscore);
    
  posY -= spacing;
  m_homeOptions = MenuButton::create(
    m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_on_left"), m_pGameContext->getImageMap()->getTile("menubutton_on_center"), m_pGameContext->getImageMap()->getTile("menubutton_on_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , buttonWidth, buttonWidth, buttonWidth
    , "OPTIONS", m_pGameContext, menu_selector(MenuScene::showOptions), this);
  m_homeOptions->setPosition(center.x, posY);
  this->addChild(m_homeOptions);

  /*************** ARCADE ***************/
  CalculateButtonLayoutCoordinates(topY, buttonSize.height, targetedSpacingToButtonHeightRatio, availableHeight, 3, posY, spacing);

  m_arcadeEasy = MenuButton::create(
    m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_on_left"), m_pGameContext->getImageMap()->getTile("menubutton_on_center"), m_pGameContext->getImageMap()->getTile("menubutton_on_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , buttonWidth, buttonWidth, buttonWidth
    , "EASY", m_pGameContext, menu_selector(MenuScene::startArcadeEasyGameCallback), this);
  m_arcadeEasy->setPosition(center.x + visibleRect.size.width, posY);
  this->addChild(m_arcadeEasy);

  posY -= spacing;
  m_arcadeNormal = MenuButton::create(
    m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_on_left"), m_pGameContext->getImageMap()->getTile("menubutton_on_center"), m_pGameContext->getImageMap()->getTile("menubutton_on_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , buttonWidth, buttonWidth, buttonWidth
    , "NORMAL", m_pGameContext, menu_selector(MenuScene::startArcadeNormalGameCallback), this);
  m_arcadeNormal->setPosition(center.x + visibleRect.size.width, posY);
  this->addChild(m_arcadeNormal);

  posY -= spacing;
  m_arcadeHard = MenuButton::create(
    m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_on_left"), m_pGameContext->getImageMap()->getTile("menubutton_on_center"), m_pGameContext->getImageMap()->getTile("menubutton_on_right")
    , m_pGameContext->getImageMap()->getTile("menubutton_off_left"), m_pGameContext->getImageMap()->getTile("menubutton_off_center"), m_pGameContext->getImageMap()->getTile("menubutton_off_right")
    , buttonWidth, buttonWidth, buttonWidth
    , "HARD", m_pGameContext, menu_selector(MenuScene::startArcadeHardGameCallback), this);
  m_arcadeHard->setPosition(center.x + visibleRect.size.width, posY);
  this->addChild(m_arcadeHard);    
     
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  posY -= spacing;
  m_arcadeBack = TextButton::create(TEXT_BUTTON_BORDER_COLOR_ON, TEXT_BUTTON_BORDER_COLOR_OFF
    , TEXT_BUTTON_BACKGROUND_COLOR_ON, TEXT_BUTTON_BACKGROUND_COLOR_OFF
    , TEXT_BUTTON_CONTENT_COLOR_ON, TEXT_BUTTON_CONTENT_COLOR_OFF
    , "back"
    , m_pGameContext->getDefaultButtonSize()
    , this->m_pGameContext->getDefaultBorderThickness()
    , this->m_pGameContext
    , callfuncO_selector(MenuScene::showBaseMenu)
    , this);
  m_arcadeBack->setPosition(center.x + visibleRect.size.width, posY);
  this->addChild(m_arcadeBack);
#endif

  this->m_challengeButtonPanel = ChallengeButtonPanel::create(this->m_pGameContext
    , callfunc_selector(MenuScene::onBackKeyPressed), this);
  this->m_challengeButtonPanel->setPosition(center);
  this->addChild(m_challengeButtonPanel);

  this->m_challengeButtonPanel->hide();
  
  hideSplashScreen();
}

void MenuScene::CalculateButtonLayoutCoordinates(float topY, float buttonHeight, float targetedSpacingToButtonHeightRatio, float availableHeight
  , int totalButtons, float& startPosY, float& spacing)
{
  spacing = round( buttonHeight * targetedSpacingToButtonHeightRatio );
  float overallHeight = spacing * (totalButtons - 1) + buttonHeight; 
  if (overallHeight > availableHeight)
  {
    spacing = (availableHeight - buttonHeight*totalButtons) / totalButtons + buttonHeight;
    overallHeight = spacing * (totalButtons - 1) + buttonHeight;
  }
  startPosY = round ( topY - (availableHeight - overallHeight)/2 - buttonHeight/2 );
}


void MenuScene::resetHomeButtons(bool isVisible)
{  
#if GAME_VERSION > 1
  m_homeStoryMode->setVisible(isVisible);
#endif
  m_homeArcade->setVisible(isVisible);
  m_homeOptions->setVisible(isVisible);
  m_homeHighscore->setVisible(isVisible);
}

void MenuScene::resetArcadeButtons(bool isVisible)
{
  m_arcadeEasy->setVisible(isVisible);
  m_arcadeNormal->setVisible(isVisible);
  m_arcadeHard->setVisible(isVisible);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  m_arcadeBack->setVisible(isVisible);
#endif
}

void MenuScene::showView(MenuViewType menuViewType)
{
  CCActionInterval* moveLeft = CCMoveBy::create(.3f, ccp(-(VisibleRect::getVisibleRect().size.width),0));
  CCActionInterval* moveRight = CCMoveBy::create(.3f, ccp((VisibleRect::getVisibleRect().size.width),0));
  
  CCPoint center = VisibleRect::center();
  CCRect visibleRect = VisibleRect::getVisibleRect();
  float easeRate = .5f;
  float posLeft = center.x - visibleRect.size.width;
  float posRight = center.x + visibleRect.size.width;
    
  m_header->setVisible(true);

  switch(menuViewType)
  {
  case HOME:
        
    switch (m_menuViewType)
    {
    case STORY_MODE:
    
      resetHomeButtons(true);
      resetArcadeButtons(false);
      m_challengeButtonPanel->hide();

      m_homeStoryMode->setPositionX(center.x);
      m_homeArcade->setPositionX(center.x);
      m_homeOptions->setPositionX(center.x);
      m_homeHighscore->setPositionX(center.x);

      break;

    case ARCADE:
      resetHomeButtons(true);
      resetArcadeButtons(true);
      m_challengeButtonPanel->hide();

      m_homeStoryMode->setPositionX(posLeft);
      m_homeArcade->setPositionX(posLeft);
      m_homeOptions->setPositionX(posLeft);
      m_homeHighscore->setPositionX(posLeft);

      m_homeStoryMode->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      m_homeArcade->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      m_homeOptions->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      m_homeHighscore->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));    
    
      m_arcadeEasy->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      m_arcadeNormal->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
      m_arcadeHard->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
      m_arcadeBack->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveRight->copy()->autorelease()), easeRate), NULL));
#endif
      break;
    }

    break;

  case ARCADE:
    
    resetHomeButtons(true);
    resetArcadeButtons(true);
    m_challengeButtonPanel->hide();

    m_homeStoryMode->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    m_homeArcade->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    m_homeOptions->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    m_homeHighscore->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    
    m_arcadeEasy->setPositionX(posRight);
    m_arcadeNormal->setPositionX(posRight);
    m_arcadeHard->setPositionX(posRight);

    m_arcadeEasy->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    m_arcadeNormal->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
    m_arcadeHard->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_arcadeBack->runAction(CCSequence::create(CCEaseIn::create((CCActionInterval*)(moveLeft->copy()->autorelease()), easeRate), NULL));
#endif
    break;

  case STORY_MODE:
  
    resetHomeButtons(false);
    resetArcadeButtons(false);

    m_header->setVisible(false);
    m_challengeButtonPanel->show();
    m_challengeButtonPanel->reset();

  break;
  }

  m_menuViewType = menuViewType;
}

void MenuScene::startArcadeEasyGameCallback(CCObject* pSender)
{ 
  NavigationManager::showScene(ARCADE_EASY_GAME_SCENE, m_pGameContext, NEW, true);
}
void MenuScene::startArcadeHardGameCallback(CCObject* pSender)
{ 
  NavigationManager::showScene(ARCADE_HARD_GAME_SCENE, m_pGameContext, NEW, true);
}
void MenuScene::startArcadeNormalGameCallback(CCObject* pSender)
{ 
  NavigationManager::showScene(ARCADE_NORMAL_GAME_SCENE, m_pGameContext, NEW, true);
}

void MenuScene::showStoryModeMenu(CCObject* pSender)
{ 
  showView(STORY_MODE);
}
void MenuScene::showArcadeMenu(CCObject* pSender)
{ 
  showView(ARCADE);
}

void MenuScene::showOptions(CCObject* pSender)
{ 
  NavigationManager::showScene(OPTIONS_SCENE, m_pGameContext, NEW, false);
}
void MenuScene::showHighscore(CCObject* pSender)
{ 
  NavigationManager::showScene(HIGHSCORE_SCENE, m_pGameContext, NEW, false);
}
void MenuScene::showBaseMenu(CCObject* pSender)
{
  showView(HOME);
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

