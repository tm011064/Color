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
  if (frameSize.width <= SIZE_960x1280.size.width
    && frameSize.height <= SIZE_960x1280.size.height)
  { 
    gameContext->setResourceDefinition( SIZE_960x1280 );
  }
  if (frameSize.width <= SIZE_720x960.size.width
    && frameSize.height <= SIZE_720x960.size.height) 
  { 
    gameContext->setResourceDefinition( SIZE_720x960 );
  }
  if (frameSize.width <= SIZE_360x480.size.width
    && frameSize.height <= SIZE_360x480.size.height)
  { 
    gameContext->setResourceDefinition( SIZE_360x480 );
  }
  if (frameSize.width <= SIZE_240x320.size.width
    && frameSize.height <= SIZE_240x320.size.height)
  { 
    gameContext->setResourceDefinition( SIZE_240x320 );
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
    
  gameContext->setImageMapPListPath(CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(gameContext, "imagemap.plist").c_str()));
  gameContext->setImageMapPngPath(CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(gameContext, "imagemap.png").c_str()));

  gameContext->setSoundPath(CCFileUtils::sharedFileUtils()->fullPathForFilename("sounds/"));
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_s1.wav").c_str() );
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_s2.wav").c_str() );
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_s3.wav").c_str() );
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_s4.wav").c_str() );
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_s5.wav").c_str() );
  SimpleAudioEngine::sharedEngine()->preloadEffect( (gameContext->getSoundPath() + "button_wrong.wav").c_str() );

  BaseFileUtils* baseFileUtils = new BaseFileUtils(); 
  baseFileUtils->loadFilenameLookupDictionaryFromFile(
    CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(gameContext, "resourceLookup.plist").c_str()).c_str());
  std::vector<std::string> mapFiles = baseFileUtils->getNumberedResourceFiles("img_buttonmap");
  std::vector<std::string>::iterator it;
  for(it=mapFiles.begin();it!=mapFiles.end();++it)
  {
    gameContext->registerImageMapFile(std::string(*it + ".plist").c_str(), std::string(*it + ".png").c_str());
  }
  mapFiles = baseFileUtils->getNumberedResourceFiles("img_imagemap");
  for(it=mapFiles.begin();it!=mapFiles.end();++it)
  {
    gameContext->registerImageMapFile(std::string(*it + ".plist").c_str(), std::string(*it + ".png").c_str());
  }
  // TODO (Roman): get sound files as well??
  CC_SAFE_DELETE(baseFileUtils);
  
  // Fonts
  baseFileUtils = new BaseFileUtils(); 
  baseFileUtils->loadFilenameLookupDictionaryFromFile(
    CCFileUtils::sharedFileUtils()->fullPathForFilename("fontResourceLookup.plist").c_str());
  mapFiles = baseFileUtils->getNumberedKeys("fs_");
  std::vector<int> fontSizes;
  for(it=mapFiles.begin();it!=mapFiles.end();++it)
  {
    // this will be fs_18, fs_20...
    fontSizes.push_back(atoi(((it)->substr(3, (it)->length() - 3)).c_str()));
  }
  
  std::vector<int>::iterator itInt;
  int targetNormalFontSize = (int)round(frameSize.height * .0375);
  int targetLargeFontSize = (int)round(frameSize.height * .0625);
  int actualNormalFontSize, actualLargeFontSize, delta;
  int closestNormalFontSizeDistance = INT_MAX;
  int closestLargeFontSizeDistance = INT_MAX;
  
  for(itInt=fontSizes.begin();itInt!=fontSizes.end();++itInt)
  {
    delta = abs(targetNormalFontSize - *itInt);
    if (delta < closestNormalFontSizeDistance)
    {
      closestNormalFontSizeDistance = delta;
      actualNormalFontSize = *itInt;
    }
    delta = abs(targetLargeFontSize - *itInt);
    if (delta < closestLargeFontSizeDistance)
    {
      closestLargeFontSizeDistance = delta;
      actualLargeFontSize = *itInt;
    }
  }

  std::ostringstream ossNormal;
  ossNormal << "fs_" << actualNormalFontSize;
  std::string normalPath = CCFileUtils::sharedFileUtils()->fullPathForFilename((baseFileUtils->valueForKey(ossNormal.str())).c_str());
  
  std::ostringstream ossLarge;
  ossLarge << "fs_" << actualLargeFontSize;
  std::string largePath = CCFileUtils::sharedFileUtils()->fullPathForFilename((baseFileUtils->valueForKey(ossLarge.str())).c_str());
  
  gameContext->setFontNormalPath(normalPath);
  gameContext->setFontLargePath(largePath);
  CC_SAFE_DELETE(baseFileUtils);
      
  // set default sizes
  CCLabelBMFont* label = CCLabelBMFont::create("Replay", normalPath.c_str());    
  CCSize letterSize = label->getContentSize();
  
  gameContext->setFontHeightNormal(letterSize.height);
  gameContext->setDefaultButtonSize(round(letterSize.width * 1.5), round(letterSize.height * 1.5));
  
  gameContext->setDefaultPadding(round(letterSize.height * .1));
  if (gameContext->getDefaultPadding() < 2.0f)
    gameContext->setDefaultPadding(2.0f);

  gameContext->setDefaultBorderThickness(round(gameContext->getDefaultPadding() * .25));
  if (gameContext->getDefaultBorderThickness() < 1.0f)
    gameContext->setDefaultBorderThickness(1.0f);

  label = CCLabelBMFont::create("Replay", largePath.c_str()); 
  gameContext->setFontHeightLarge(label->getContentSize().height);

  label->release();  

  this->m_pGameContext = gameContext;

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
