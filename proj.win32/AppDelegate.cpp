#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "BaseLayer.h"
#include "Types.h"
#include "GameConstants.h"
#include "GameContext.h"
#include "NavigationManager.h"
#include <cstring> 

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
  :m_gameContext(NULL)
{
}

AppDelegate::~AppDelegate()
{
  if (m_gameContext)
    CC_SAFE_DELETE(m_gameContext);

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
  
  gameContext->setResolutionPolicy(kResolutionNoBorder);
  gameContext->setOriginalSize(pEGLView->getDesignResolutionSize());
    
  CCSize frameSize = pEGLView->getFrameSize();
    
  if (frameSize.width > SIZE_960x1280.size.width)
  { 
    gameContext->setResourceDefinition( SIZE_1536x2048 );
    pEGLView->setDesignResolutionSize(SIZE_1536x2048.size.width, SIZE_1536x2048.size.height, gameContext->getResolutionPolicy());
  }
  if (frameSize.width > SIZE_720x960.size.width)
  { 
    gameContext->setResourceDefinition( SIZE_960x1280 );
    pEGLView->setDesignResolutionSize(SIZE_960x1280.size.width, SIZE_960x1280.size.height, gameContext->getResolutionPolicy());
  }
  else if (frameSize.width > SIZE_360x480.size.width)
  { 
    gameContext->setResourceDefinition( SIZE_720x960 );
    pEGLView->setDesignResolutionSize(SIZE_720x960.size.width, SIZE_720x960.size.height, gameContext->getResolutionPolicy());
  }
  else if (frameSize.width > SIZE_240x320.size.width)
  { 
    gameContext->setResourceDefinition( SIZE_360x480 );
    pEGLView->setDesignResolutionSize(SIZE_360x480.size.width, SIZE_360x480.size.height, gameContext->getResolutionPolicy());
  }
  else
  { 
    gameContext->setResourceDefinition( SIZE_240x320 );
    pEGLView->setDesignResolutionSize(SIZE_240x320.size.width, SIZE_240x320.size.height, gameContext->getResolutionPolicy());
  }
    
  std::vector<std::string> searchPaths;
  searchPaths.push_back(gameContext->getResourceDefinition().directory);
  CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

  //pDirector->setContentScaleFactor(gameContext->getResourceDefinition().size.width/DESIGN_RESOLUTION_SIZE.width);
    
  gameContext->setHorizontalScaleFactor(gameContext->getResourceDefinition().size.width/frameSize.width);
  gameContext->setVerticalScaleFactor(1.0f);

  // turn on display FPS
  pDirector->setDisplayStats(false);
    
  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);
    
  gameContext->setImageMapPListPath(CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(gameContext, "imagemap.plist").c_str()));
  gameContext->setImageMapPngPath(CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(gameContext, "imagemap.png").c_str()));

  gameContext->setSoundPath(CCFileUtils::sharedFileUtils()->fullPathForFilename("sounds/"));
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_s1.wav").c_str() );
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_s2.wav").c_str() );
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_s3.wav").c_str() );
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_s4.wav").c_str() );
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_s5.wav").c_str() );

  gameContext->initImageMap(gameContext->getImageMapPListPath().c_str(), gameContext->getImageMapPngPath().c_str());
  
  std::string normalPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(gameContext, FONT_MENU_NORMAL).c_str());
  std::string largePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(gameContext, FONT_MENU_LARGE).c_str());
  gameContext->setFontNormalPath(normalPath);
  gameContext->setFontLargePath(largePath);
      
  // set default sizes
  CCLabelBMFont* label = CCLabelBMFont::create("Replay", normalPath.c_str());    
  CCSize letterSize = label->getContentSize();
  
  gameContext->setFontHeightNormal(letterSize.height);
  gameContext->setDefaultButtonSize(round(letterSize.width * 1.5), round(letterSize.height * 1.2));
  
  gameContext->setDefaultPadding(round(letterSize.height * .1));
  if (gameContext->getDefaultPadding() < 2.0f)
    gameContext->setDefaultPadding(2.0f);

  gameContext->setDefaultBorderThickness(round(gameContext->getDefaultPadding() * .25));
  if (gameContext->getDefaultBorderThickness() < 1.0f)
    gameContext->setDefaultBorderThickness(1.0f);

  label = CCLabelBMFont::create("Replay", largePath.c_str());
  gameContext->setFontHeightLarge(label->getContentSize().height);

  label->release();    

  this->m_gameContext = gameContext;

  NavigationManager::showScene(MENU_SCENE, gameContext, FIRST_RUN);
  
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
