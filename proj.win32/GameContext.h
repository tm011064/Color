#ifndef __GAMECONTEXT_H__
#define __GAMECONTEXT_H__

#include "cocos2d.h"
#include "GameConstants.h"
#include "SpriteFrameCache.h"
#include "Types.h"
#include "BaseTileMap.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class GameContext 
{
private:

  std::vector<int> m_challengeStatuses;
  std::map<std::string, std::string> m_soundLookup;
  int m_totalChallenges;

  bool m_isSoundOn;
  bool m_isVibrateOn;
  
  float m_maxDigitWidthNormal;
  float m_maxDigitWidthLarge;

  float m_fontSpaceWidthLarge;
  float m_fontHeightNormal;
  float m_fontHeightLarge;
  float m_defaultBorderThickness;
  float m_defaultPadding;

  float m_fontScale;
  float m_panelInnerWidthWide;
  float m_panelInnerWidthNarrow;

  std::vector<std::string> m_digitsFontNormal;
  std::vector<std::string> m_digitsFontLarge;
  std::vector<int> m_digitFontNormalWidths;
  std::vector<int> m_digitFontLargeWidths;
  
  std::map<int, ChallengePointScoreDefinition> m_challengePointScoreDefinitions;

  CCSize m_defaultButtonSize;

  CCSize m_frameSize;

  int m_highscoreMemory2b;
  int m_highscoreMemory3b;
  int m_highscoreMemory4b;

  int m_highscoreMemory2bTotal;
  int m_highscoreMemory3bTotal;
  int m_highscoreMemory4bTotal;
  
  int m_highscoreSpeed2b;
  int m_highscoreSpeed3b;
  int m_highscoreSpeed4b;
  
  int m_highscoreSpeed2bTotal;
  int m_highscoreSpeed3bTotal;
  int m_highscoreSpeed4bTotal;

  int m_highscoreRhythm;
  int m_highscoreBalance;

  BaseTileMap* m_imageMap;  
  SpriteFrameCache* m_spriteFrameCache;

  GameScore m_currentGameScore;
  ResourceDefinition m_resourceDefinition;

  float m_horizontalScaleFactor;
  float m_verticalScaleFactor;
  CCSize m_originalSize;
  ResolutionPolicy m_resolutionPolicy;

  std::string m_fontNormalPath;
  std::string m_fontLargePath;

  std::string m_imageMapPListPath;
  std::string m_imageMapPngPath;
  
  unsigned int m_totalCoins;
  int m_totalLifes;
  long m_lastLifeIncreaseTime;
  
  void createChallengePointScoreDefinitions();
  ChallengePointScoreDefinition getBaseChallengePointScoreDefinition(int totalButtons);

public:  
  GameContext();
  ~GameContext();

  void init(int totalChallenges);

  GameScore getGameScore() { return this->m_currentGameScore; }
  void setGameScore(GameScore gameScore) { this->m_currentGameScore = gameScore; }

  ResourceDefinition getResourceDefinition() { return this->m_resourceDefinition; }
  void setResourceDefinition(ResourceDefinition resourceDefinition) { this->m_resourceDefinition = resourceDefinition; }
    
  float getPanelInnerWidthWide() { return this->m_panelInnerWidthWide; }
  void setPanelInnerWidthWide(float panelInnerWidthWide) { this->m_panelInnerWidthWide = panelInnerWidthWide; }
  float getPanelInnerWidthNarrow() { return this->m_panelInnerWidthNarrow; }
  void setPanelInnerWidthNarrow(float panelInnerWidthNarrow) { this->m_panelInnerWidthNarrow = panelInnerWidthNarrow; }
  float getFontScale() { return this->m_fontScale; }
  void setFontScale(float fontScale) { this->m_fontScale = fontScale; }
   
  float getHorizontalScaleFactor() { return this->m_horizontalScaleFactor; }
  void setHorizontalScaleFactor(float horizontalScaleFactor) { this->m_horizontalScaleFactor = horizontalScaleFactor; }
  
  float getVerticalScaleFactor() { return this->m_verticalScaleFactor; }
  void setVerticalScaleFactor(float verticalScaleFactor) { this->m_verticalScaleFactor = verticalScaleFactor; }

  CCSize getOriginalSize() { return this->m_originalSize; }
  void setOriginalSize(CCSize originalSize) { this->m_originalSize = originalSize; }

  ResolutionPolicy getResolutionPolicy() { return this->m_resolutionPolicy; }
  void setResolutionPolicy(ResolutionPolicy resolutionPolicy) { this->m_resolutionPolicy = resolutionPolicy; }

  std::string getFontNormalPath() { return this->m_fontNormalPath; }
  void setFontNormalPath(std::string fontNormalPath) { this->m_fontNormalPath = fontNormalPath; }

  std::string getFontLargePath() { return this->m_fontLargePath; }
  void setFontLargePath(std::string fontLargePath) { this->m_fontLargePath = fontLargePath; }
  
  std::string getImageMapPListPath() { return this->m_imageMapPListPath; }
  void setImageMapPListPath(std::string imageMapPListPath) { this->m_imageMapPListPath = imageMapPListPath; }
  
  std::string getImageMapPngPath() { return this->m_imageMapPngPath; }
  void setImageMapPngPath(std::string imageMapPngPath) { this->m_imageMapPngPath = imageMapPngPath; }
      
  float getDefaultBorderThickness() { return this->m_defaultBorderThickness; }
  void setDefaultBorderThickness(float defaultBorderThickness) { this->m_defaultBorderThickness = defaultBorderThickness; }

  float getDefaultPadding() { return this->m_defaultPadding; }
  void setDefaultPadding(float defaultPadding) { this->m_defaultPadding = defaultPadding; }
  
  float getOuterPanelPadding() { return this->m_defaultPadding * 4; }

  float getFontHeightLarge() { return this->m_fontHeightLarge; }
  void setFontHeightLarge(float fontHeightLarge) { this->m_fontHeightLarge = fontHeightLarge; }
  
  float getFontSpaceWidthLarge() { return this->m_fontSpaceWidthLarge; }
  void setFontSpaceWidthLarge(float fontSpaceWidthLarge) { this->m_fontSpaceWidthLarge = fontSpaceWidthLarge; }
  
  float getFontHeightNormal() { return this->m_fontHeightNormal; }
  void setFontHeightNormal(float fontHeightNormal) { this->m_fontHeightNormal = fontHeightNormal; }
  
  CCSize getDefaultButtonSize() { return this->m_defaultButtonSize; }
  void setDefaultButtonSize(float width, float height) { this->m_defaultButtonSize.setSize(width, height); }
  
  CCSize getFrameSize() { return this->m_frameSize; }
  void setFrameSize(float width, float height) { this->m_frameSize.setSize(width, height); }
  
  bool getIsSoundOn() { return this->m_isSoundOn; }
  void setIsSoundOn(bool isSoundOn);
  
  bool getIsVibrateOn() { return this->m_isVibrateOn; }
  void setIsVibrateOn(bool isVibrateOn);
    
  int getHighscoreMemory2b() { return this->m_highscoreMemory2b; }
  void setHighscoreMemory2b(int totalPoints);
  int getHighscoreMemory3b() { return this->m_highscoreMemory3b; }
  void setHighscoreMemory3b(int totalPoints);
  int getHighscoreMemory4b() { return this->m_highscoreMemory4b; }
  void setHighscoreMemory4b(int totalPoints);

  int getHighscoreMemory2bTotal() { return this->m_highscoreMemory2bTotal; }
  void setHighscoreMemory2bTotal(int totalPoints);
  int getHighscoreMemory3bTotal() { return this->m_highscoreMemory3bTotal; }
  void setHighscoreMemory3bTotal(int totalPoints);
  int getHighscoreMemory4bTotal() { return this->m_highscoreMemory4bTotal; }
  void setHighscoreMemory4bTotal(int totalPoints);
  
  int getHighscoreSpeed2b() { return this->m_highscoreSpeed2b; }
  void setHighscoreSpeed2b(int totalPoints);
  int getHighscoreSpeed3b() { return this->m_highscoreSpeed3b; }
  void setHighscoreSpeed3b(int totalPoints);
  int getHighscoreSpeed4b() { return this->m_highscoreSpeed4b; }
  void setHighscoreSpeed4b(int totalPoints);
  
  int getHighscoreSpeed2bTotal() { return this->m_highscoreSpeed2bTotal; }
  void setHighscoreSpeed2bTotal(int totalPoints);
  int getHighscoreSpeed3bTotal() { return this->m_highscoreSpeed3bTotal; }
  void setHighscoreSpeed3bTotal(int totalPoints);
  int getHighscoreSpeed4bTotal() { return this->m_highscoreSpeed4bTotal; }
  void setHighscoreSpeed4bTotal(int totalPoints);

  int getHighscoreRhythm() { return this->m_highscoreRhythm; }
  void setHighscoreRhythm(int totalPoints);
  int getHighscoreBalance() { return this->m_highscoreBalance; }
  void setHighscoreBalance(int totalPoints);
  
  void registerImageFile(const char *filePath, const char *key);
  void registerImageMapFile(const char *pList, const char *textureFileName);
  BaseTileMap* getImageMap(){ return this->m_imageMap; }
  
  SpriteFrameCache* getSpriteFrameCache() { return this->m_spriteFrameCache; }
  void setSpriteFrameCache(SpriteFrameCache* spriteFrameCache) { this->m_spriteFrameCache = spriteFrameCache; }

  unsigned int getTotalCoins() { return this->m_totalCoins; }
  void setTotalCoins(unsigned int totalCoins);
  
  unsigned int getTotalLifes() { return this->m_totalLifes; }
  void setTotalLifes(int totalLifes);
  
  long getLastLifeIncreaseTime() { return this->m_lastLifeIncreaseTime; }
  void setLastLifeIncreaseTime(long lastLifeIncreaseTime);  

  int getChallengeInfo(unsigned int index) { return this->m_challengeStatuses.at(index); }
  void setChallengeInfo(unsigned int index, int status);
  
  void registerDigitFontNormal(int d, int width, std::string c);
  void registerDigitFontLarge(int d, int width, std::string c);

  int getMaxDigitFontNormalWidth() { return m_maxDigitWidthNormal; }
  int getMaxDigitFontLargeWidth() { return m_maxDigitWidthLarge; }
  int getDigitFontNormalWidth(int d) { return m_digitFontNormalWidths[d]; }
  int getDigitFontLargeWidth(int d) { return m_digitFontLargeWidths[d]; }
  std::string getDigitFontNormal(int d) { return m_digitsFontNormal[d]; }
  std::string getDigitFontLarge(int d) { return m_digitsFontLarge[d]; }

  LifeInfo refreshTotalLifesCount();

  ChallengePointScoreDefinition getChallengePointScoreDefinition(int index)
  {
    return m_challengePointScoreDefinitions[index];
  }

  void registerSoundFile(std::string key, std::string filePath) 
  { 
    m_soundLookup[key] = filePath; 
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect( filePath.c_str() );
  }
  std::string getSoundPath(std::string key) { return m_soundLookup[key]; }
};

#endif  // __GAMECONTEXT_H__