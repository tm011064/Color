#include "RhythmChallengeScene.h"
#include "LayoutController.h"
#include "SimpleAudioEngine.h"
#include <fstream>

using namespace cocos2d;

RhythmChallengeScene* RhythmChallengeScene::create(GameContext* gameContext, bool showSplashScreen, int challengeIndex
  , RhythmBlinkSequenceDefinition rhythmBlinkSequenceDefinition
  , ChallengePointScoreDefinition challengePointScoreDefinition)
{
  RhythmChallengeScene* scene = new RhythmChallengeScene(gameContext, showSplashScreen, challengeIndex
    , rhythmBlinkSequenceDefinition
    , RHYTHM, challengePointScoreDefinition);
  scene->init();

  return scene;
}

RhythmBlinkSequenceDefinition RhythmChallengeScene::loadRhythmBlinkSequenceDefinition(std::string filePath)
{
  CCLOG("Start parsing rhythm definitions file");
  RhythmBlinkSequenceDefinition rhythmBlinkSequenceDefinition;

  rhythmBlinkSequenceDefinition.totalSequences = 0;
  unsigned long fileSize = 0;
  unsigned char* fileContent = CCFileUtils::sharedFileUtils()->getFileData( filePath.c_str(), "r", &fileSize );
  
  cocos2d::CCString *text = cocos2d::CCString::createWithData( fileContent, fileSize );
  std::istringstream fileStringStream( text->getCString() );
  
  std::string line;
  bool isInOptionDefinitons = false;
  bool isInSequenceDefiniton = false;
  std::vector<std::string> splitted;
  std::vector<RhythmBlink> rhythmBlinks;
  std::vector<RhythmBlinkSequence> rhythmBlinkSequences;

  while ( std::getline( fileStringStream, line ) )
  {
    UtilityHelper::ltrim(line);

    if ( isInSequenceDefiniton )
    {
      if (UtilityHelper::startsWith(line, "se;"))
      {
        isInSequenceDefiniton = false;

        RhythmBlinkSequence rhythmBlinkSequence;
        rhythmBlinkSequence.averageUserOffset = .0f;
        rhythmBlinkSequence.totalBlinks = rhythmBlinks.size();
        for (int i = 0; i < rhythmBlinkSequence.totalBlinks; ++i)
          rhythmBlinkSequence.rhythmBlinks.push_back(rhythmBlinks[i]);

        rhythmBlinkSequenceDefinition.rhythmBlinkSequences.push_back(rhythmBlinkSequence);
        rhythmBlinkSequenceDefinition.totalSequences++;
      }
      else
      {
        splitted = UtilityHelper::split(line, ' ', 0);
        if (splitted.size() == 3)
        {
          if (splitted[0] == "b")
          {
            RhythmBlink rhythmBlink;
            rhythmBlink.buttonIndex = atoi( splitted[1].c_str() );
            rhythmBlink.blinkTime = atof( splitted[2].c_str() );

            rhythmBlinks.push_back( rhythmBlink );
          }
        }
      }
    }
    else if ( isInOptionDefinitons )
    {
      if (UtilityHelper::startsWith(line, "oe;"))
      {
        isInOptionDefinitons = false;
      }
      else
      {
        splitted = UtilityHelper::split(line, '=', 0);
        if (splitted.size() == 2)
        {
          if (splitted[0] == "name")
            rhythmBlinkSequenceDefinition.name = splitted[1];
          else if (splitted[0] == "totalbuttons")
            rhythmBlinkSequenceDefinition.totalButtons = atoi(splitted[1].c_str());
        }
      }
    }
    else if (UtilityHelper::startsWith(line, "os;"))
    {
      isInOptionDefinitons = true;
    }
    else if (UtilityHelper::startsWith(line, "ss;"))
    {
      isInSequenceDefiniton = true;
      rhythmBlinks.clear();
    }    
  }
  
  CC_SAFE_RELEASE_NULL(text);

  CCLOG("total sequences: %i", rhythmBlinkSequenceDefinition.rhythmBlinkSequences.size());

  return rhythmBlinkSequenceDefinition;
}
void RhythmChallengeScene::onLoadLayout()
{  
  switch (this->m_totalEnabledButtons)
  {
  case 1:
    this->m_buttons = LayoutController::createOneButton(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( RhythmChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( RhythmChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( RhythmChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_BEGAN, DRUMS);      
    break;

  case 2:
    this->m_buttons = LayoutController::createTwoButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( RhythmChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( RhythmChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( RhythmChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_BEGAN, DRUMS);      
    break;

  case 3:
        
    this->m_buttons = LayoutController::createThreeButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( RhythmChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( RhythmChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( RhythmChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_BEGAN, DRUMS);      
    break;

  case 4:
    this->m_buttons = LayoutController::createFourButtons(this->m_pGameContext, this->m_debugDraw, this->m_anchor, this
      , callfuncO_selector( RhythmChallengeScene::buttonTouchEndedCallback )
      , callfuncO_selector( RhythmChallengeScene::buttonLoadedCallback )
      , callfuncO_selector( RhythmChallengeScene::buttonBlinkCallback )
      , FIRE_ON_TOUCH_BEGAN, DRUMS);      
    break;
  }     

  // TODO (Roman): back key on all occasions
  this->m_totalVisibleButtons = this->m_buttons->count();

  std::vector< GameButton* > enabledButtons;
  CCObject* o;
  CCARRAY_FOREACH(this->m_buttons, o)
  {
    this->addChild((GameButton*)o);
    if (((GameButton*)o)->getIsEnabled())
      enabledButtons.push_back((GameButton*)o);
  }  
    
  std::vector< RhythmBlinkSequence >::iterator it1;
  std::vector< RhythmBlink >::iterator it2;
  for(it1=this->m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences.begin();it1!=this->m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences.end();++it1)
  {
    for(it2=it1->rhythmBlinks.begin();it2!=it1->rhythmBlinks.end();++it2)
    {
      it2->button = enabledButtons[it2->buttonIndex];
    }
  }
}

void RhythmChallengeScene::onLoadDescriptionPopup()
{  
  ccColor4F bgColor = { 23.0f/255.0f, 23.0f/255.0f, 23.0f/255.0f, 1.0f };
  ccColor4F bgDialogColor = { 165.0f/255.0f, 65.0f/255.0f, 43.0f/255.0f, 1.0f };
  ccColor4F bgDialogBorderColor = { 1.0f, 1.0f, 1.0f, 1.0f };
  
  /********** DESCRIPTION POPUP **********/
  m_descriptionPopup = DescriptionPopup::create(
    this->m_pGameContext
    , callfuncO_selector(RhythmChallengeScene::newGameCallback)
    , this
    , "Rhythm\nChallenge"
    , "Target Score: " + UtilityHelper::convertToString(
        MAX(.0f, 1.0f - this->m_challengePointScoreDefinition.minimumTotalTimePercentageForOneStar) * 100.0f, 0) 
      + " / 100\n\nRepeat the button\nsequence.\nTry to get as many\nas blinks as\npossible." // TODO (Roman): text
    , this->m_pGameContext->getImageMap()->getTile("iconNote")
    , bgColor, bgDialogColor, bgDialogBorderColor);
  m_descriptionPopup->setZOrder(SPLASH_ZORDER);
  this->addChild(m_descriptionPopup);
  /********** DESCRIPTION POPUP **********/
}

void RhythmChallengeScene::onLayoutLoaded()
{  

}

void RhythmChallengeScene::startNewGame()
{  
  if (this->m_wildcardPopup->isVisible())
    this->m_wildcardPopup->hide();
  if (this->m_gameScorePopup->isVisible())
    this->m_gameScorePopup->hide();
    
  this->m_buttonSequence.clear();
  this->m_buttonSequenceIndex = 0;
  
  this->m_gameScore.starsEarned = 0;
  this->m_gameScore.level = 0;
  this->m_gameScore.totalButtonBonus = 0;
  this->m_gameScore.totalLevelBonus = 0;
  this->m_gameScore.totalPoints= 0;
  this->m_gameScore.totalTimeElapsed = 0;

  this->m_topBar->setScore(0);
  this->m_topBar->setLevel(1);
    
  // Scene specific
  this->m_currentSequenceIndex = 0;

  runSequenceAnimation();
}

void RhythmChallengeScene::sequenceBlinkCallback(CCObject* pSender)
{
  ((GameButton*)pSender)->playAnimation(BLINK);
  m_buttonSequence.push_back(((GameButton*)pSender));
}

void RhythmChallengeScene::setAwaitingInput()
{  
  m_buttonSequenceIndex = 0;
  this->m_sceneState = AWAITING_INPUT;
}

void RhythmChallengeScene::runSequenceAnimation()
{
  this->m_sceneState = RUNNING_SEQUENCE_ANIMATION;

  m_buttonSequence.clear();
  
  float delay = .6f;
  for (int i = 0; i < m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].totalBlinks; ++i)
  {
    m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[i].areUserVariablesSet = false;

    this->runAction(CCSequence::create(
                      CCDelayTime::create(delay + m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[i].blinkTime)
                      , CCCallFuncO::create(this, callfuncO_selector(RhythmChallengeScene::sequenceBlinkCallback), m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[i].button)
                      , NULL));
  }  
  this->runAction(CCSequence::create(
                    CCDelayTime::create(delay + m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].totalBlinks - 1].blinkTime)
                    , CCCallFunc::create(this, callfunc_selector(RhythmChallengeScene::setAwaitingInput))
                    , NULL));
}

int RhythmChallengeScene::updateChallengeInfo(const ChallengePointScoreDefinition* challengePointScoreDefinition)
{  
  int challengeInfo = m_pGameContext->getChallengeInfo(this->m_challengeIndex);
  this->m_gameScore.starsEarned = 0;

  if ( this->m_gameScore.averageButtonBlinkStartOffset <= challengePointScoreDefinition->minimumTotalTimePercentageForThreeStars )
  {
    this->m_gameScore.starsEarned = 3;
    if (challengeInfo < 3)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 3);
  }
  else if ( this->m_gameScore.averageButtonBlinkStartOffset <= challengePointScoreDefinition->minimumTotalTimePercentageForTwoStars )
  {       
    this->m_gameScore.starsEarned = 2;
    if (challengeInfo < 2)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 2);
  }
  else if ( this->m_gameScore.averageButtonBlinkStartOffset <= challengePointScoreDefinition->minimumTotalTimePercentageForOneStar)
  {       
    this->m_gameScore.starsEarned = 1;
    if (challengeInfo < 1)
      m_pGameContext->setChallengeInfo(this->m_challengeIndex, 1);
  }

  return this->m_gameScore.starsEarned;
}

void RhythmChallengeScene::buttonTouchEndedCallback(CCObject* pSender)
{
  m_lastButtonPressed = ((GameButton*)pSender);

  // use the areUserVariablesSet flag to determine whether we have already used this button...
  int buttonSequenceIndex = -1;
  int nextSequenceButtonIndex = -1;
  for (int i = 0; i < this->m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].totalBlinks; ++i)
  {
    if (!this->m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[i].areUserVariablesSet)
    {
      if (nextSequenceButtonIndex == -1)
        nextSequenceButtonIndex = i;
      if (this->m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[i].button == m_lastButtonPressed)
      {
        buttonSequenceIndex = i;
        break;
      }
    }
  }
  if (buttonSequenceIndex < 0)
  {
    // the button was not found, we can exit...
    m_nextSequenceButton = m_buttonSequence.at(nextSequenceButtonIndex);
    this->onIncorrectButtonPressed();
  }
  else
  {    
    this->m_lastButtonPressed->playAnimation(BLINK, false); 
    m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[buttonSequenceIndex].areUserVariablesSet = true;

    cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);

    m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[buttonSequenceIndex].userBlinkActualTime = now;
    if (buttonSequenceIndex == 0)
    {    
      m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[buttonSequenceIndex].userBlinkRelativeTime = 0;
    }
    else
    {
      m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[buttonSequenceIndex].userBlinkRelativeTime =
        UtilityHelper::getTimeDelta(now, m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[0].userBlinkActualTime);
    }
  
    m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[buttonSequenceIndex].absoluteUserBlinkOffset = 
      fabs(m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[buttonSequenceIndex].blinkTime
         - m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[buttonSequenceIndex].userBlinkRelativeTime);
    
    int totalUserButtonBlinks = 0;
    for (int i = 0; i < this->m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].totalBlinks; ++i)
    {
      if (this->m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks[i].areUserVariablesSet)
        totalUserButtonBlinks++;
    }
    
    if (totalUserButtonBlinks == m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].totalBlinks)
    {
      m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].averageUserOffset = .0f;
        
      std::vector< RhythmBlink >::iterator it;
      for(it=this->m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks.begin();it!=m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].rhythmBlinks.end();++it)
      {
        m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].averageUserOffset += it->absoluteUserBlinkOffset;
      }

      m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].averageUserOffset /= (float)m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].totalBlinks;
    
      this->m_gameScore.totalPoints += MAX(.0f, 100 - m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].averageUserOffset * 10) * m_challengePointScoreDefinition.correctButtonScore;
      m_topBar->setScore((long)this->m_gameScore.totalPoints);
      
      char str[128];
      sprintf(str, "+%.3f s", fabs(m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].averageUserOffset));
    
      int colorShade;  
      if (m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].averageUserOffset < .1f) { colorShade = 1; }
      else if (m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].averageUserOffset < .2f) { colorShade = 2; }
      else if (m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].averageUserOffset < .3f) { colorShade = 3; }
      else if (m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[m_currentSequenceIndex].averageUserOffset < .4f) { colorShade = 4; }
      else { colorShade = 5; }

      this->playConsoleLabelAnimation(str, 1.4f, 1.1f, .0f, colorShade);

      if (m_currentSequenceIndex == m_rhythmBlinkSequenceDefinition.totalSequences - 1)
      {
        // TODO (Roman): end of game      
        this->m_sceneState = RUNNING_END_OF_GAME_ANIMATION; 
        this->m_gameScore.averageButtonBlinkStartOffset = 0;
    
        for (int i = 0; i < m_rhythmBlinkSequenceDefinition.totalSequences; ++i)
        {
          this->m_gameScore.averageButtonBlinkStartOffset += fabs(m_rhythmBlinkSequenceDefinition.rhythmBlinkSequences[i].averageUserOffset);
        }
        this->m_gameScore.averageButtonBlinkStartOffset = this->m_gameScore.averageButtonBlinkStartOffset / m_rhythmBlinkSequenceDefinition.totalSequences;
        this->m_gameScore.averageButtonBlinkPercentage = MAX(.0f, 1.0f - this->m_gameScore.averageButtonBlinkStartOffset);
    
        // TODO (Roman): scoring and popup      
        this->m_gameScore.coinsEarned = round( MAX(.0f, 4.0f - this->m_gameScore.averageButtonBlinkStartOffset * 10.0f) );
      
        this->m_pGameContext->setTotalCoins(this->m_pGameContext->getTotalCoins() + m_gameScore.coinsEarned);
              
        this->updateChallengeInfo(&this->m_challengePointScoreDefinition);
        m_pGameContext->setGameScore( m_gameScore );
      
        this->playBlinkButtonsAnimation(2, .25f, .8f);
        this->scheduleOnce(schedule_selector(RhythmChallengeScene::showGameScorePopupCallback), 2.0f);
      }
      else
      {
        m_currentSequenceIndex++;
        runSequenceAnimation();
      }
    }

  }
}

void RhythmChallengeScene::onIncorrectButtonPressed()
{
  // TODO (Roman): check whether that is correct
  this->m_sceneState = RUNNING_END_OF_GAME_ANIMATION;

  this->m_gameScore.coinsEarned = round( (float)m_gameScore.level * m_challengePointScoreDefinition.coinsEarnedMultiplier );
  this->m_pGameContext->setTotalCoins(this->m_pGameContext->getTotalCoins() + m_gameScore.coinsEarned);

  m_topBar->setScore((long)this->m_gameScore.totalPoints);
  m_pGameContext->setGameScore( m_gameScore );
    
  float wrongDelay = 1.6f;
  float correctBlinkDelay = 2.3f;
  this->m_eogTotalWrongButtonBlinks = 3;
  this->m_eogElaspedTime = 0;
  this->m_eogTargetTime = .8f;
  this->m_eogTargetTimeLastButton = .55f;
  this->m_eogElapsedTimeWrongButton = -wrongDelay;
          
  m_lastButtonPressed->playAnimation(PRESSED);

  this->schedule(schedule_selector(RhythmChallengeScene::eogGrayOutButtons), 0.021f); // framerate: 1/48
  this->schedule(schedule_selector(RhythmChallengeScene::eogGrayOutLastButton), 0.021f, -1, wrongDelay); // framerate: 1/48
  this->schedule(schedule_selector(RhythmChallengeScene::eogReleaseLastButton), 0.021f, 0, wrongDelay); // framerate: 1/48
  this->schedule(schedule_selector(RhythmChallengeScene::eogBlinkCorrectButton), 0.2f, -1, correctBlinkDelay); // framerate: 1/48    
  

}
