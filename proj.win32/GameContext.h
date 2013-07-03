#ifndef __GAMECONTEXT_H__
#define __GAMECONTEXT_H__

#include "cocos2d.h"
#include "GameConstants.h"
#include "SpriteFrameCache.h"
#include "Types.h"
#include "BaseTileMap.h"

using namespace cocos2d;

class GameContext 
{
private:

  std::vector<int> m_challengeStatuses;
  int m_totalChallenges;

  bool m_isSoundOn;
  bool m_isVibrateOn;
  
  float m_fontHeightNormal;
  float m_fontHeightLarge;
  float m_defaultBorderThickness;
  float m_defaultPadding;
  CCSize m_defaultButtonSize;

  int m_highscoreEasy;
  int m_highscoreNormal;
  int m_highscoreHard;

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

  std::string m_soundPath;

  unsigned int m_totalCoins;
  
public:  
  GameContext();
  ~GameContext();

  void init(int totalChallenges);

  GameScore getGameScore() { return this->m_currentGameScore; }
  void setGameScore(GameScore gameScore) { this->m_currentGameScore = gameScore; }

  ResourceDefinition getResourceDefinition() { return this->m_resourceDefinition; }
  void setResourceDefinition(ResourceDefinition resourceDefinition) { this->m_resourceDefinition = resourceDefinition; }
    
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
    
  std::string getSoundPath() { return this->m_soundPath; }
  void setSoundPath(std::string soundPath) { this->m_soundPath = soundPath; }
  
  float getDefaultBorderThickness() { return this->m_defaultBorderThickness; }
  void setDefaultBorderThickness(float defaultBorderThickness) { this->m_defaultBorderThickness = defaultBorderThickness; }

  float getDefaultPadding() { return this->m_defaultPadding; }
  void setDefaultPadding(float defaultPadding) { this->m_defaultPadding = defaultPadding; }
  
  float getFontHeightLarge() { return this->m_fontHeightLarge; }
  void setFontHeightLarge(float fontHeightLarge) { this->m_fontHeightLarge = fontHeightLarge; }

  float getFontHeightNormal() { return this->m_fontHeightNormal; }
  void setFontHeightNormal(float fontHeightNormal) { this->m_fontHeightNormal = fontHeightNormal; }
  
  CCSize getDefaultButtonSize() { return this->m_defaultButtonSize; }
  void setDefaultButtonSize(float width, float height) { this->m_defaultButtonSize.setSize(width, height); }

  bool getIsSoundOn() { return this->m_isSoundOn; }
  void setIsSoundOn(bool isSoundOn);
  
  bool getIsVibrateOn() { return this->m_isVibrateOn; }
  void setIsVibrateOn(bool isVibrateOn);
  
  int getHighscoreEasy() { return this->m_highscoreEasy; }
  void setHighscoreEasy(int totalPoints);
  
  int getHighscoreNormal() { return this->m_highscoreNormal; }
  void setHighscoreNormal(int totalPoints);
  
  int getHighscoreHard() { return this->m_highscoreHard; }
  void setHighscoreHard(int totalPoints);

  void registerImageMapFile(const char *pList, const char *textureFileName);
  BaseTileMap* getImageMap(){ return this->m_imageMap; }
  
  SpriteFrameCache* getSpriteFrameCache() { return this->m_spriteFrameCache; }
  void setSpriteFrameCache(SpriteFrameCache* spriteFrameCache) { this->m_spriteFrameCache = spriteFrameCache; }

  unsigned int getTotalCoins() { return this->m_totalCoins; }
  void setTotalCoins(unsigned int totalCoins);
  
  int getChallengeInfo(unsigned int index) { return this->m_challengeStatuses.at(index); }
  void setChallengeInfo(unsigned int index, int status);
};

#endif  // __GAMECONTEXT_H__