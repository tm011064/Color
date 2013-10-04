#include "LoadGameScene.h"
#include "BaseFileUtils.h"
#include "NavigationManager.h"
#include "GameConstants.h"
#include <cstring> 
#include <sstream>

void LoadGameScene::onEnter()
{
  CCScene::onEnter();

  if (!this->m_isLayoutInitialized)
  {  
    this->m_isLayoutInitialized = true;
    
    CCRect visibleRect = VisibleRect::getVisibleRect();  
        
    m_pGameContext->registerImageFile(
      CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(m_pGameContext, "splash.png").c_str()).c_str()
      , "splash");
    m_pGameContext->registerImageFile(
      CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(m_pGameContext, "splashLogo.png").c_str()).c_str()
      , "splashLogo");

    CCSprite* splashScreen = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("splash"));
    CCSize s = splashScreen->getContentSize();
    splashScreen->setScaleX(visibleRect.size.width / s.width);
    splashScreen->setScaleY(visibleRect.size.height / s.height);
    splashScreen->setPosition(VisibleRect::center());
    this->addChild(splashScreen, SPLASH_ZORDER);
    
    CCSprite* splashLogoScreen = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("splashLogo"));
    splashLogoScreen->setPosition(VisibleRect::center());
    this->addChild(splashLogoScreen, SPLASH_ZORDER);

    this->scheduleOnce(schedule_selector(LoadGameScene::loadGame), 0.0f);
  }
}

void LoadGameScene::loadGame(float dt)
{  
  m_pGameContext->setImageMapPListPath(CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(m_pGameContext, "imagemap.plist").c_str()));
  m_pGameContext->setImageMapPngPath(CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(m_pGameContext, "imagemap.png").c_str()));

  BaseFileUtils* baseFileUtils = new BaseFileUtils(); 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  baseFileUtils->loadFilenameLookupDictionaryFromFile(
    CCFileUtils::sharedFileUtils()->fullPathForFilename("soundResourceLookup_android.plist").c_str());
  CCLOG("Initializing android sound files");
#else
  baseFileUtils->loadFilenameLookupDictionaryFromFile(
    CCFileUtils::sharedFileUtils()->fullPathForFilename("soundResourceLookup.plist").c_str());
#endif

  m_pGameContext->registerSoundFile("buttonsound_normal_1", baseFileUtils->valueForKey("buttonsound_normal_1"));
  m_pGameContext->registerSoundFile("buttonsound_normal_2", baseFileUtils->valueForKey("buttonsound_normal_2"));
  m_pGameContext->registerSoundFile("buttonsound_normal_3", baseFileUtils->valueForKey("buttonsound_normal_3"));
  m_pGameContext->registerSoundFile("buttonsound_normal_4", baseFileUtils->valueForKey("buttonsound_normal_4"));
  m_pGameContext->registerSoundFile("buttonsound_wrong", baseFileUtils->valueForKey("buttonsound_wrong"));
  m_pGameContext->registerSoundFile("buttonsound_long_1", baseFileUtils->valueForKey("buttonsound_long_1"));
  m_pGameContext->registerSoundFile("buttonsound_long_2", baseFileUtils->valueForKey("buttonsound_long_2"));
  m_pGameContext->registerSoundFile("buttonsound_long_3", baseFileUtils->valueForKey("buttonsound_long_3"));
  m_pGameContext->registerSoundFile("buttonsound_long_4", baseFileUtils->valueForKey("buttonsound_long_4"));

  baseFileUtils = new BaseFileUtils(); 
  baseFileUtils->loadFilenameLookupDictionaryFromFile(
    CCFileUtils::sharedFileUtils()->fullPathForFilename(NavigationManager::getPath(m_pGameContext, "resourceLookup.plist").c_str()).c_str());
  std::vector<std::string> mapFiles = baseFileUtils->getNumberedResourceFiles("img_buttonmap");
  std::vector<std::string>::iterator it;
  for(it=mapFiles.begin();it!=mapFiles.end();++it)
  {
    m_pGameContext->registerImageMapFile(std::string(*it + ".plist").c_str(), std::string(*it + ".png").c_str());
  }
  mapFiles = baseFileUtils->getNumberedResourceFiles("img_imagemap");
  for(it=mapFiles.begin();it!=mapFiles.end();++it)
  {
    m_pGameContext->registerImageMapFile(std::string(*it + ".plist").c_str(), std::string(*it + ".png").c_str());
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
  int targetNormalFontSize = (int)round(m_pGameContext->getFrameSize().height * .0375);
  int targetLargeFontSize = (int)round(m_pGameContext->getFrameSize().height * .0625);
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
  
  m_pGameContext->setFontNormalPath(normalPath);
  m_pGameContext->setFontLargePath(largePath);
  CC_SAFE_DELETE(baseFileUtils);
      
  // set default sizes
  CCLabelBMFont* label = CCLabelBMFont::create("Replay", normalPath.c_str());    
  CCSize letterSize = label->getContentSize();
  
  m_pGameContext->setFontHeightNormal(letterSize.height);
  m_pGameContext->setDefaultButtonSize(round(letterSize.width * 1.5), round(letterSize.height * 1.5));
  
  m_pGameContext->setDefaultPadding(round(letterSize.height * .1));
  if (m_pGameContext->getDefaultPadding() < 2.0f)
    m_pGameContext->setDefaultPadding(2.0f);

  m_pGameContext->setDefaultBorderThickness(round(m_pGameContext->getDefaultPadding() * .25));
  if (m_pGameContext->getDefaultBorderThickness() < 1.0f)
    m_pGameContext->setDefaultBorderThickness(1.0f);
  
  std::string s;
  for (int i = 0; i < 10; ++i)
  {    
    s = UtilityHelper::convertToString(i);
    label->setString( s.c_str() );
    m_pGameContext->registerDigitFontNormal(i, label->getContentSize().width, s );
  }

  label = CCLabelBMFont::create("Replay", largePath.c_str()); 
  m_pGameContext->setFontHeightLarge(label->getContentSize().height);

  label = CCLabelBMFont::create(" ", largePath.c_str()); 
  m_pGameContext->setFontSpaceWidthLarge(label->getContentSize().width);

  for (int i = 0; i < 10; ++i)
  {
    s = UtilityHelper::convertToString(i);
    label->setString( s.c_str() );
    m_pGameContext->registerDigitFontLarge(i, label->getContentSize().width, s );
  }

  label->release();  

  NavigationManager::showMainMenu(m_pGameContext, NEW, true, HOME);
}

