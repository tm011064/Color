#include "GameContext.h"
#include "UtilityHelper.h"

GameContext::GameContext()
  : m_imageMap(NULL)
  , m_maxDigitWidthNormal(0)
  , m_maxDigitWidthLarge(0)
{
  m_digitFontNormalWidths.resize(10);
  m_digitFontLargeWidths.resize(10);
  m_digitsFontNormal.resize(10);
  m_digitsFontLarge.resize(10);
}

GameContext::~GameContext()
{
  CC_SAFE_DELETE(m_imageMap);
  CC_SAFE_DELETE(this->m_spriteFrameCache);
}

void GameContext::init(int totalChallenges)
{
  ChallengePointScoreDefinition challengePointScoreDefinition;  

  challengePointScoreDefinition.correctButtonScore = 100.0f;
  challengePointScoreDefinition.maxTimeBonus = 40.0f;
  challengePointScoreDefinition.clickTimeThreshold = 2.0f;
  challengePointScoreDefinition.levelBonus = 400.0f;
  challengePointScoreDefinition.maxLevelTimeBonus = 400.0f;
  challengePointScoreDefinition.coinsEarnedMultiplier = .1f;
  m_challengePointScoreDefinitions[1] = challengePointScoreDefinition;

  challengePointScoreDefinition.correctButtonScore = 300.0f;
  challengePointScoreDefinition.maxTimeBonus = 70.0f;
  challengePointScoreDefinition.clickTimeThreshold = 2.0f;
  challengePointScoreDefinition.levelBonus = 700.0f;
  challengePointScoreDefinition.maxLevelTimeBonus = 700.0f;
  challengePointScoreDefinition.coinsEarnedMultiplier = .15f;
  m_challengePointScoreDefinitions[2] = challengePointScoreDefinition;

  challengePointScoreDefinition.correctButtonScore = 500.0f;
  challengePointScoreDefinition.maxTimeBonus = 100.0f;
  challengePointScoreDefinition.clickTimeThreshold = 2.0f;
  challengePointScoreDefinition.levelBonus = 1000.0f;
  challengePointScoreDefinition.maxLevelTimeBonus = 1000.0f;
  challengePointScoreDefinition.coinsEarnedMultiplier = .3f;
  m_challengePointScoreDefinitions[3] = challengePointScoreDefinition;
  
  challengePointScoreDefinition.correctButtonScore = 700.0f;
  challengePointScoreDefinition.maxTimeBonus = 130.0f;
  challengePointScoreDefinition.clickTimeThreshold = 2.0f;
  challengePointScoreDefinition.levelBonus = 1300.0f;
  challengePointScoreDefinition.maxLevelTimeBonus = 1300.0f;
  challengePointScoreDefinition.coinsEarnedMultiplier = .5f;
  m_challengePointScoreDefinitions[4] = challengePointScoreDefinition;

  CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();

  this->m_totalCoins = userDefault->getIntegerForKey("totalCoins", 0);
  this->m_highscoreEasy = userDefault->getIntegerForKey("highscoreEasy", 0);
  this->m_highscoreNormal = userDefault->getIntegerForKey("highscoreNormal", 0);
  this->m_highscoreHard = userDefault->getIntegerForKey("highscoreHard", 0);
    
  this->m_totalLifes = userDefault->getIntegerForKey("totalLifes", MAX_LIFES);  
  struct cc_timeval now;
  CCTime::gettimeofdayCocos2d(&now, NULL);
  std::string s = userDefault->getStringForKey("lastLifeIncreaseTime", "NA");
  if (s == "NA")
  {
    // first time
    this->setLastLifeIncreaseTime( now.tv_sec );
  }
  else
  {
    long delta = now.tv_sec - atol(s.c_str());
    int lifesGained = delta / LIFE_INCREASE_INTERVAL_SEC;

    this->setLastLifeIncreaseTime( now.tv_sec - ( delta - lifesGained * LIFE_INCREASE_INTERVAL_SEC ) );
    this->setTotalLifes( MIN( MAX_LIFES, MAX( 0, this->m_totalLifes + lifesGained ) ) );
  }

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

LifeInfo GameContext::refreshTotalLifesCount()
{
  struct cc_timeval now;
  CCTime::gettimeofdayCocos2d(&now, NULL);
      
  long delta = MAX( 0, now.tv_sec - this->m_lastLifeIncreaseTime );
  int lifesGained = delta / LIFE_INCREASE_INTERVAL_SEC;

  this->setLastLifeIncreaseTime( now.tv_sec - ( delta - lifesGained * LIFE_INCREASE_INTERVAL_SEC ) );
  this->setTotalLifes( MIN( MAX_LIFES, MAX( 0, this->m_totalLifes + lifesGained ) ) );

  LifeInfo lifeInfo;

  lifeInfo.deltaToNextIncreaseInSeconds = LIFE_INCREASE_INTERVAL_SEC - ( delta - lifesGained * LIFE_INCREASE_INTERVAL_SEC );
  lifeInfo.totalLifes = this->m_totalLifes;

  return lifeInfo;
}

void GameContext::registerImageFile(const char *filePath, const char *key)
{  
  if (!m_imageMap)
  {  
    m_imageMap = new BaseTileMap();
    m_imageMap->RegisterImage(filePath, key);
  }
  else
  {
    m_imageMap->RegisterImage(filePath, key);
  }
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

void GameContext::setTotalLifes(int totalLifes)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("totalLifes", totalLifes);
  this->m_totalLifes = totalLifes;
} 
void GameContext::setLastLifeIncreaseTime(long lastLifeIncreaseTime)
{  
  CCUserDefault::sharedUserDefault()->setStringForKey("lastLifeIncreaseTime", UtilityHelper::convertLongToString( lastLifeIncreaseTime ) );
  this->m_lastLifeIncreaseTime = lastLifeIncreaseTime;
}

void GameContext::registerDigitFontNormal(int d, int width, std::string c)
{ 
  m_digitFontLargeWidths[d] = width; 
  m_digitsFontNormal[d] = c;
  if ( m_maxDigitWidthNormal < width )
    m_maxDigitWidthNormal = width;
}
void GameContext::registerDigitFontLarge(int d, int width, std::string c) 
{ 
  m_digitFontLargeWidths[d] = width; 
  m_digitsFontLarge[d] = c; 
  if ( m_maxDigitWidthLarge < width )
    m_maxDigitWidthLarge = width;
}