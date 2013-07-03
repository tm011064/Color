#include "GameContext.h"

GameContext::GameContext()
  : m_imageMap(NULL)
{
}

GameContext::~GameContext()
{
  CC_SAFE_DELETE(m_imageMap);
  CC_SAFE_DELETE(this->m_spriteFrameCache);
}

void GameContext::init(int totalChallenges)
{
  CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();

  this->m_totalCoins = userDefault->getIntegerForKey("totalCoins", 0);
  this->m_highscoreEasy = userDefault->getIntegerForKey("highscoreEasy", 0);
  this->m_highscoreNormal = userDefault->getIntegerForKey("highscoreNormal", 0);
  this->m_highscoreHard = userDefault->getIntegerForKey("highscoreHard", 0);

  this->m_isSoundOn = userDefault->getBoolForKey("isSoundOn", true);
  this->m_isVibrateOn = userDefault->getBoolForKey("isVibrateOn", true);

  this->m_totalChallenges = totalChallenges;
  char str[4];
  for (short i = 0; i < totalChallenges; ++i)
  {
    sprintf(str, "l%i", i);
    this->m_challengeStatuses.push_back(userDefault->getIntegerForKey(str));
  }

  this->m_spriteFrameCache = new SpriteFrameCache();
  this->m_spriteFrameCache->init();
}

void GameContext::registerImageMapFile(const char *pList, const char *textureFileName)
{
  if (!m_imageMap)
  {  
    m_imageMap = new BaseTileMap(pList,textureFileName);
  }
  else
  {
    m_imageMap->RegisterTextureFileName(pList, textureFileName);
  }
}

void GameContext::setTotalCoins(unsigned int totalCoins)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("totalCoins", totalCoins);
  this->m_totalCoins = totalCoins;
}
void GameContext::setIsSoundOn(bool isSoundOn)
{  
  CCUserDefault::sharedUserDefault()->setBoolForKey("isSoundOn", isSoundOn);
  this->m_isSoundOn = isSoundOn;
}
void GameContext::setIsVibrateOn(bool isVibrateOn)
{  
  CCUserDefault::sharedUserDefault()->setBoolForKey("isVibrateOn", isVibrateOn);
  this->m_isVibrateOn = isVibrateOn;
}

void GameContext::setHighscoreEasy(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreEasy", totalPoints);
  this->m_highscoreEasy = totalPoints;
}
void GameContext::setHighscoreNormal(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreNormal", totalPoints);
  this->m_highscoreNormal = totalPoints;
}
void GameContext::setHighscoreHard(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("highscoreHard", totalPoints);
  this->m_highscoreHard = totalPoints;
}


void GameContext::setChallengeInfo(unsigned int index, int status)
{
  char str[4];
  sprintf(str, "l%i", index);
  
  CCUserDefault::sharedUserDefault()->setIntegerForKey(str, status);
  this->m_challengeStatuses[index] = status;
}