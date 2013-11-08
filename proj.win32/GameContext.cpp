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
  createChallengePointScoreDefinitions();

  CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();

  this->m_totalCoins = userDefault->getIntegerForKey("totalCoins", 0);
      
  this->m_highscoreMemory2b = userDefault->getIntegerForKey("hsMemory2b", 0);
  this->m_highscoreMemory3b = userDefault->getIntegerForKey("hsMemory3b", 0);
  this->m_highscoreMemory4b = userDefault->getIntegerForKey("hsMemory4b", 0);

  this->m_highscoreMemory2bTotal = userDefault->getIntegerForKey("hsMemory2bTotal", 0);
  this->m_highscoreMemory3bTotal = userDefault->getIntegerForKey("hsMemory3bTotal", 0);
  this->m_highscoreMemory4bTotal = userDefault->getIntegerForKey("hsMemory4bTotal", 0);
  
  this->m_highscoreSpeed2b = userDefault->getIntegerForKey("hsSpeed2b", 0);
  this->m_highscoreSpeed3b = userDefault->getIntegerForKey("hsSpeed3b", 0);
  this->m_highscoreSpeed4b = userDefault->getIntegerForKey("hsSpeed4b", 0);

  this->m_highscoreSpeed2bTotal = userDefault->getIntegerForKey("hsSpeed2bTotal", 0);
  this->m_highscoreSpeed3bTotal = userDefault->getIntegerForKey("hsSpeed3bTotal", 0);
  this->m_highscoreSpeed4bTotal = userDefault->getIntegerForKey("hsSpeed4bTotal", 0);

  this->m_highscoreRhythm = userDefault->getIntegerForKey("hsRhythm", 0);
  this->m_highscoreBalance = userDefault->getIntegerForKey("hsBalance", 0);
  
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

void GameContext::createChallengePointScoreDefinitions()
{
  float totalCorrectButtons;
  ChallengePointScoreDefinition challengePointScoreDefinition;

  // CHALLENGE: 01
  // -------------------------------------------------------------------------------------------

  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(2);
  challengePointScoreDefinition.levelToReach = 1;
  totalCorrectButtons = (challengePointScoreDefinition.levelToReach / 2.0f) * ( 1.0f + challengePointScoreDefinition.levelToReach );

  challengePointScoreDefinition.mininimumPointsForOneStar = 0;
  challengePointScoreDefinition.mininimumPointsForTwoStars = 
    challengePointScoreDefinition.levelBonus * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
    + challengePointScoreDefinition.maxLevelTimeBonus * challengePointScoreDefinition.levelToReach * .7f
    + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - challengePointScoreDefinition.levelToReach ) * .7f; // minus level to reach cause the first click gains no bonus

  challengePointScoreDefinition.mininimumPointsForThreeStars = 
    challengePointScoreDefinition.levelBonus * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
    + challengePointScoreDefinition.maxLevelTimeBonus * challengePointScoreDefinition.levelToReach * .9f
    + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - challengePointScoreDefinition.levelToReach ) * .9f;

  challengePointScoreDefinition.challengeSceneType = REACH_LEVEL;
  m_challengePointScoreDefinitions[0] = challengePointScoreDefinition;

  // CHALLENGE: 02
  // -------------------------------------------------------------------------------------------    
  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(3);
  challengePointScoreDefinition.levelToReach = 9;
  totalCorrectButtons = (challengePointScoreDefinition.levelToReach / 2.0f) * ( 1.0f + challengePointScoreDefinition.levelToReach );
        
  challengePointScoreDefinition.mininimumPointsForOneStar = 0;
  challengePointScoreDefinition.mininimumPointsForTwoStars = 
    challengePointScoreDefinition.levelBonus * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
    + challengePointScoreDefinition.maxLevelTimeBonus * challengePointScoreDefinition.levelToReach * .7f
    + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - challengePointScoreDefinition.levelToReach ) * .7f;

  challengePointScoreDefinition.mininimumPointsForThreeStars = 
    challengePointScoreDefinition.levelBonus * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
    + challengePointScoreDefinition.maxLevelTimeBonus * challengePointScoreDefinition.levelToReach * .9f
    + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - challengePointScoreDefinition.levelToReach ) * .9f;
  
  challengePointScoreDefinition.challengeSceneType = REACH_LEVEL;
  m_challengePointScoreDefinitions[1] = challengePointScoreDefinition;

  // CHALLENGE: 03
  // -------------------------------------------------------------------------------------------      
  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(3);
  challengePointScoreDefinition.levelToReach = 2;
    
  challengePointScoreDefinition.mininimumPointsForOneStar = 0;
  challengePointScoreDefinition.mininimumPointsForTwoStars = 
    challengePointScoreDefinition.correctButtonScore * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.maxTimeBonus * (challengePointScoreDefinition.levelToReach - 1) * .72f;

  challengePointScoreDefinition.mininimumPointsForThreeStars = 
    challengePointScoreDefinition.correctButtonScore * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.maxTimeBonus * (challengePointScoreDefinition.levelToReach - 1) * .85f;

  challengePointScoreDefinition.challengeSceneType = REPEAT_ONE_OFF;
  m_challengePointScoreDefinitions[2] = challengePointScoreDefinition;

  // CHALLENGE: 04
  // -------------------------------------------------------------------------------------------
      
  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(4);
  challengePointScoreDefinition.levelToReach = 12;
  totalCorrectButtons = (challengePointScoreDefinition.levelToReach / 2.0f) * ( 1.0f + challengePointScoreDefinition.levelToReach );
    
  challengePointScoreDefinition.mininimumPointsForOneStar = 0;
  challengePointScoreDefinition.mininimumPointsForTwoStars = 
    challengePointScoreDefinition.correctButtonScore * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.maxTimeBonus * (challengePointScoreDefinition.levelToReach - 1) * .72f;

  challengePointScoreDefinition.mininimumPointsForThreeStars = 
    challengePointScoreDefinition.correctButtonScore * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.maxTimeBonus * (challengePointScoreDefinition.levelToReach - 1) * .85f;

  challengePointScoreDefinition.challengeSceneType = REPEAT_ONE_OFF;
  m_challengePointScoreDefinitions[3] = challengePointScoreDefinition;

  // CHALLENGE: 05
  // -------------------------------------------------------------------------------------------
  
  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(1);
    
  challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
  challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
  challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;

  challengePointScoreDefinition.challengeSceneType = EXACT_LENGTH;
  m_challengePointScoreDefinitions[4] = challengePointScoreDefinition;

  // CHALLENGE: 06
  // -------------------------------------------------------------------------------------------
      
  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(3);
    
  challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
  challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
  challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;

  challengePointScoreDefinition.challengeSceneType = EXACT_LENGTH;
  m_challengePointScoreDefinitions[5] = challengePointScoreDefinition;

  // CHALLENGE: 07
  // -------------------------------------------------------------------------------------------
  
  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(4);
    
  challengePointScoreDefinition.minimumTotalTimePercentageForOneStar = .75f;
  challengePointScoreDefinition.minimumTotalTimePercentageForTwoStars = .85f;
  challengePointScoreDefinition.minimumTotalTimePercentageForThreeStars = .93f;

  challengePointScoreDefinition.challengeSceneType = EXACT_LENGTH;
  m_challengePointScoreDefinitions[6] = challengePointScoreDefinition;

  // CHALLENGE: 08
  // -------------------------------------------------------------------------------------------

  challengePointScoreDefinition.challengeSceneType = RHYTHM;
  m_challengePointScoreDefinitions[7] = challengePointScoreDefinition;

  // CHALLENGE: 09
  // -------------------------------------------------------------------------------------------

  challengePointScoreDefinition.challengeSceneType = RHYTHM;
  m_challengePointScoreDefinitions[8] = challengePointScoreDefinition;

  // CHALLENGE: 10
  // -------------------------------------------------------------------------------------------
      
  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(2);
  challengePointScoreDefinition.levelToReach = 25;
  totalCorrectButtons = (challengePointScoreDefinition.levelToReach / 2.0f) * ( 1.0f + challengePointScoreDefinition.levelToReach );
        
  challengePointScoreDefinition.mininimumPointsForOneStar = 0;
  challengePointScoreDefinition.mininimumPointsForTwoStars = 
    challengePointScoreDefinition.levelBonus * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
    + challengePointScoreDefinition.maxLevelTimeBonus * challengePointScoreDefinition.levelToReach * .7f
    + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - challengePointScoreDefinition.levelToReach ) * .7f;

  challengePointScoreDefinition.mininimumPointsForThreeStars = 
    challengePointScoreDefinition.levelBonus * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
    + challengePointScoreDefinition.maxLevelTimeBonus * challengePointScoreDefinition.levelToReach * .9f
    + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - challengePointScoreDefinition.levelToReach ) * .9f;

  challengePointScoreDefinition.challengeSceneType = REACH_LEVEL;
  m_challengePointScoreDefinitions[9] = challengePointScoreDefinition;

  // CHALLENGE: 11
  // -------------------------------------------------------------------------------------------
      
  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(3);
  challengePointScoreDefinition.levelToReach = 20;
  totalCorrectButtons = (challengePointScoreDefinition.levelToReach / 2.0f) * ( 1.0f + challengePointScoreDefinition.levelToReach );
        
  challengePointScoreDefinition.mininimumPointsForOneStar = 0;
  challengePointScoreDefinition.mininimumPointsForTwoStars = 
    challengePointScoreDefinition.levelBonus * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
    + challengePointScoreDefinition.maxLevelTimeBonus * challengePointScoreDefinition.levelToReach * .7f
    + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - challengePointScoreDefinition.levelToReach ) * .7f;

  challengePointScoreDefinition.mininimumPointsForThreeStars = 
    challengePointScoreDefinition.levelBonus * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
    + challengePointScoreDefinition.maxLevelTimeBonus * challengePointScoreDefinition.levelToReach * .9f
    + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - challengePointScoreDefinition.levelToReach ) * .9f;

  challengePointScoreDefinition.challengeSceneType = REACH_LEVEL;
  m_challengePointScoreDefinitions[10] = challengePointScoreDefinition;

  // CHALLENGE: 12
  // -------------------------------------------------------------------------------------------
      
  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(4);
  challengePointScoreDefinition.levelToReach = 20;
  totalCorrectButtons = (challengePointScoreDefinition.levelToReach / 2.0f) * ( 1.0f + challengePointScoreDefinition.levelToReach );
        
  challengePointScoreDefinition.mininimumPointsForOneStar = 0;
  challengePointScoreDefinition.mininimumPointsForTwoStars = 
    challengePointScoreDefinition.levelBonus * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
    + challengePointScoreDefinition.maxLevelTimeBonus * challengePointScoreDefinition.levelToReach * .7f
    + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - challengePointScoreDefinition.levelToReach ) * .7f;

  challengePointScoreDefinition.mininimumPointsForThreeStars = 
    challengePointScoreDefinition.levelBonus * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.correctButtonScore * totalCorrectButtons
    + challengePointScoreDefinition.maxLevelTimeBonus * challengePointScoreDefinition.levelToReach * .9f
    + challengePointScoreDefinition.maxTimeBonus * ( totalCorrectButtons - challengePointScoreDefinition.levelToReach ) * .9f;

  challengePointScoreDefinition.challengeSceneType = REACH_LEVEL;
  m_challengePointScoreDefinitions[11] = challengePointScoreDefinition;

  // CHALLENGE: 13
  // -------------------------------------------------------------------------------------------
      
  challengePointScoreDefinition = this->getBaseChallengePointScoreDefinition(2);
  challengePointScoreDefinition.levelToReach = 15;
  totalCorrectButtons = (challengePointScoreDefinition.levelToReach / 2.0f) * ( 1.0f + challengePointScoreDefinition.levelToReach );
    
  challengePointScoreDefinition.mininimumPointsForOneStar = 0;
  challengePointScoreDefinition.mininimumPointsForTwoStars = 
    challengePointScoreDefinition.correctButtonScore * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.maxTimeBonus * (challengePointScoreDefinition.levelToReach - 1) * .72f;

  challengePointScoreDefinition.mininimumPointsForThreeStars = 
    challengePointScoreDefinition.correctButtonScore * challengePointScoreDefinition.levelToReach
    + challengePointScoreDefinition.maxTimeBonus * (challengePointScoreDefinition.levelToReach - 1) * .85f;

  challengePointScoreDefinition.challengeSceneType = REPEAT_ONE_OFF;
  m_challengePointScoreDefinitions[12] = challengePointScoreDefinition;

  // CHALLENGE: 14
  // -------------------------------------------------------------------------------------------

  challengePointScoreDefinition.challengeSceneType = REACH_LEVEL;
  m_challengePointScoreDefinitions[13] = challengePointScoreDefinition;

  // CHALLENGE: 15
  // -------------------------------------------------------------------------------------------

  challengePointScoreDefinition.challengeSceneType = REACH_LEVEL;
  m_challengePointScoreDefinitions[14] = challengePointScoreDefinition;

  // CHALLENGE: 16
  // -------------------------------------------------------------------------------------------

  m_challengePointScoreDefinitions[15] = challengePointScoreDefinition;
}

ChallengePointScoreDefinition GameContext::getBaseChallengePointScoreDefinition(int totalButtons)
{
  ChallengePointScoreDefinition challengePointScoreDefinition;  

  if ( totalButtons == 1 )
  {
    challengePointScoreDefinition.correctButtonScore = 100.0f;
    challengePointScoreDefinition.maxTimeBonus = 40.0f;
    challengePointScoreDefinition.clickTimeThreshold = 2.0f;
    challengePointScoreDefinition.levelBonus = 400.0f;
    challengePointScoreDefinition.maxLevelTimeBonus = 400.0f;
    challengePointScoreDefinition.coinsEarnedMultiplier = .1f;
  }
  else if ( totalButtons == 2 )
  {
    challengePointScoreDefinition.correctButtonScore = 300.0f;
    challengePointScoreDefinition.maxTimeBonus = 70.0f;
    challengePointScoreDefinition.clickTimeThreshold = 2.0f;
    challengePointScoreDefinition.levelBonus = 700.0f;
    challengePointScoreDefinition.maxLevelTimeBonus = 700.0f;
    challengePointScoreDefinition.coinsEarnedMultiplier = .15f;  
  }
  else if ( totalButtons == 3 )
  {
    challengePointScoreDefinition.correctButtonScore = 500.0f;
    challengePointScoreDefinition.maxTimeBonus = 100.0f;
    challengePointScoreDefinition.clickTimeThreshold = 2.0f;
    challengePointScoreDefinition.levelBonus = 1000.0f;
    challengePointScoreDefinition.maxLevelTimeBonus = 1000.0f;
    challengePointScoreDefinition.coinsEarnedMultiplier = .3f;    
  }
  else if ( totalButtons == 4 )
  {
    challengePointScoreDefinition.correctButtonScore = 700.0f;
    challengePointScoreDefinition.maxTimeBonus = 130.0f;
    challengePointScoreDefinition.clickTimeThreshold = 2.0f;
    challengePointScoreDefinition.levelBonus = 1300.0f;
    challengePointScoreDefinition.maxLevelTimeBonus = 1300.0f;
    challengePointScoreDefinition.coinsEarnedMultiplier = .5f;
  }

  challengePointScoreDefinition.totalButtons = totalButtons;

  return challengePointScoreDefinition;
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

void GameContext::setHighscoreMemory2b(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsMemory2b", totalPoints);
  this->m_highscoreMemory2b = totalPoints;
}
void GameContext::setHighscoreMemory3b(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsMemory3b", totalPoints);
  this->m_highscoreMemory3b = totalPoints;
}
void GameContext::setHighscoreMemory4b(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsMemory4b", totalPoints);
  this->m_highscoreMemory4b = totalPoints;
}

void GameContext::setHighscoreMemory2bTotal(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsMemory2bTotal", totalPoints);
  this->m_highscoreMemory2bTotal = totalPoints;
}
void GameContext::setHighscoreMemory3bTotal(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsMemory3bTotal", totalPoints);
  this->m_highscoreMemory3bTotal = totalPoints;
}
void GameContext::setHighscoreMemory4bTotal(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsMemory4bTotal", totalPoints);
  this->m_highscoreMemory4bTotal = totalPoints;
}

void GameContext::setHighscoreSpeed2b(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsSpeed2b", totalPoints);
  this->m_highscoreSpeed2b = totalPoints;
}
void GameContext::setHighscoreSpeed3b(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsSpeed3b", totalPoints);
  this->m_highscoreSpeed3b = totalPoints;
}
void GameContext::setHighscoreSpeed4b(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsSpeed4b", totalPoints);
  this->m_highscoreSpeed4b = totalPoints;
}

void GameContext::setHighscoreSpeed2bTotal(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsSpeed2bTotal", totalPoints);
  this->m_highscoreSpeed2bTotal = totalPoints;
}
void GameContext::setHighscoreSpeed3bTotal(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsSpeed3bTotal", totalPoints);
  this->m_highscoreSpeed3bTotal = totalPoints;
}
void GameContext::setHighscoreSpeed4bTotal(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsSpeed4bTotal", totalPoints);
  this->m_highscoreSpeed4bTotal = totalPoints;
}

void GameContext::setHighscoreRhythm(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsRhythm", totalPoints);
  this->m_highscoreRhythm = totalPoints;
}
void GameContext::setHighscoreBalance(int totalPoints)
{  
  CCUserDefault::sharedUserDefault()->setIntegerForKey("hsBalance", totalPoints);
  this->m_highscoreBalance = totalPoints;
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