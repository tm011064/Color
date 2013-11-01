#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "BaseLayer.h"
#include "BaseFileUtils.h"
#include "Types.h"
#include "GameConstants.h"
#include "GameContext.h"
#include "NavigationManager.h"
#include <cstring> 
#include <sstream>

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
  :m_pGameContext(NULL)
{
}

AppDelegate::~AppDelegate()
{
  CC_SAFE_DELETE(m_pGameContext);

  SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
  // initialize director
  CCDirector *pDirector = CCDirector::sharedDirector();
    
  CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
  pDirector->setOpenGLView(pEGLView);

  GameContext* gameContext = new GameContext();
  gameContext->init(27);
     
  gameContext->setResolutionPolicy(kResolutionNoBorder); // kResolutionShowAll // kResolutionExactFit // kResolutionNoBorder
  gameContext->setOriginalSize(pEGLView->getDesignResolutionSize());
    
  CCSize frameSize = pEGLView->getFrameSize();
  
  gameContext->setResourceDefinition( SIZE_1536x2048 );
  gameContext->setGuaranteedVisibleSize( SIZE_960x1280.size.width, SIZE_960x1280.size.height );
  if (frameSize.width <= SIZE_960x1280.size.width
    && frameSize.height <= SIZE_960x1280.size.height)
  { 
    gameContext->setResourceDefinition( SIZE_960x1280 );
    gameContext->setGuaranteedVisibleSize( SIZE_720x960.size.width, SIZE_720x960.size.height );
  }
  if (frameSize.width <= SIZE_720x960.size.width
    && frameSize.height <= SIZE_720x960.size.height) 
  { 
    gameContext->setResourceDefinition( SIZE_720x960 );
    gameContext->setGuaranteedVisibleSize( SIZE_720x960.size.width, SIZE_720x960.size.height );
  }
  if (frameSize.width <= SIZE_360x480.size.width
    && frameSize.height <= SIZE_360x480.size.height)
  { 
    gameContext->setResourceDefinition( SIZE_360x480 );
    gameContext->setGuaranteedVisibleSize( SIZE_240x320.size.width, SIZE_240x320.size.height );
  }
  if (frameSize.width <= SIZE_240x320.size.width
    && frameSize.height <= SIZE_240x320.size.height)
  { 
    gameContext->setResourceDefinition( SIZE_240x320 );
    gameContext->setGuaranteedVisibleSize( SIZE_240x320.size.width, SIZE_240x320.size.height );
  }

  std::vector<std::string> searchPaths;
  searchPaths.push_back(gameContext->getResourceDefinition().directory);
  CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

  gameContext->setHorizontalScaleFactor(gameContext->getResourceDefinition().size.width/frameSize.width);
  gameContext->setVerticalScaleFactor(1.0f);

  // turn on display FPS
  pDirector->setDisplayStats(false);
    
  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);
    
  gameContext->setFrameSize(frameSize.width, frameSize.height);

  // gameContext->setTotalCoins(5000);

  NavigationManager::showScene(LOAD_GAME_SCENE, gameContext, FIRST_RUN, true);
  
  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
