#include "GameButton.h"
#include "VisibleRect.h"
#include "BaseScene.h"
#include "NavigationManager.h"

GameButton* GameButton::createQuarterButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , std::string soundPath, GameButtonTouchMode gameButtonTouchMode, GameContext* gameContext)
{
  GameButton* gameButton = new GameButton(pTarget, touchEndedDelegate, preLoadDelegate, gameContext, soundPath, gameButtonTouchMode);
  
  gameButton->init();    // Must call init for latest version cocos2d-x
  gameButton->autorelease();
  
  gameButton->setAnimationFrames(gameContext->getImageMap()->getTiles("gamebuttons"));
  
  gameButton->setOriginalColor(color);
  gameButton->setColor(color);
  
  gameButton->setAlphaMapStillFrameIndex(0);
  gameButton->registerStillFrame(IDLE, 0, 0, false);  
  int pressingFrames[] = { 0,2,4,6,10 };
  gameButton->registerAnimation(PRESSING, pressingFrames, 5, 1, 0, 30, false, false);  
  int releasingFrames[] = { 7,5,2,0 };
  gameButton->registerAnimation(RELEASING, releasingFrames, 4, 1, 0, 30, false, false);  
  gameButton->registerStillFrame(PRESSED, 10, 0, false);  
  int blinkFrames[] = { 2,5,8,10,9,6,4,3,2,1,0 };
  gameButton->registerAnimation(BLINK, blinkFrames, 11, 1, blinkEndedDelegate, 30, false, false);
  
  return gameButton;
}

unsigned int GameButton::playSound(bool doLoop)
{
  if (m_pGameContext->getIsSoundOn())
  {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    m_lastSoundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(this->m_soundPath.c_str(), doLoop);
  }
  else
  {
    m_lastSoundId = 0;
  }
  return m_lastSoundId;
}
void GameButton::fadeOutSound(float fadeTime)
{  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
  this->stopSound();
#else
  // straight forward linear fade
  this->schedule(schedule_selector(GameButton::reduceVolumeCallback), fadeTime*.1f);
#endif 
}
void GameButton::reduceVolumeCallback(float dt)
{
  float volume = CocosDenshion::SimpleAudioEngine::sharedEngine()->getEffectsVolume();
  if (volume <= .0f)
  {
    this->stopSound();
    this->unschedule(schedule_selector(GameButton::reduceVolumeCallback));
  }
  else
  {    
    volume -= .1f;
    if (volume < .0f)
      volume = .0f;
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
  }
}

void GameButton::playAnimation(int animationIndex)
{
  this->playAnimation(animationIndex, false);
}

void GameButton::playAnimation(int animationIndex, bool suppressSound)
{
  switch (animationIndex)
  {
  case BLINK: 
    if (!suppressSound && m_pGameContext->getIsSoundOn())
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(this->m_soundPath.c_str());    
  break;
  }
  BaseSprite::playAnimation(animationIndex);
}

bool GameButton::containsTouchLocation(CCTouch* touch)
{
  CCPoint location = touch->getLocationInView();
  location = CCDirector::sharedDirector()->convertToGL(location);

  CCPoint fromOrigin = CCNode::convertToNodeSpace(location);
  CCSize size = this->getContentSize();

  if (fromOrigin.x >= 0 && fromOrigin.x <= size.width
    && fromOrigin.y >= 0 && fromOrigin.y <= size.height)
  {// we are within the bounding circle, so check the alpha map
    return !this->isTransparent((int)(fromOrigin.x), (int)(fromOrigin.y));
  }

  return false;
}

bool GameButton::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (((BaseScene*)this->getParent())->getSceneState() != AWAITING_INPUT
        || !this->m_isEnabled)
    {
      return false;
    }

    if (containsTouchLocation(touch))
    { 
      switch (this->m_gameButtonTouchMode)
      {
      case FIRE_ON_TOUCH_BEGAN:
        this->playAnimation(BLINK, true); // we don't play the sound here as this will be played only on a correct click

        // we react on the begin event...
        if(m_pTarget != 0 && m_fnpTouchEndedDelegate != 0)
            (m_pTarget->*m_fnpTouchEndedDelegate)(this);
        break;

      case FIRE_ON_TOUCH_ENDED:
        this->playAnimation(PRESSING, true); 
        CCTime::gettimeofdayCocos2d(&this->m_touchStartedTime, NULL);
        // TODO (Roman): not looping means we need to have a max pressed time
        this->playSound(false);
        break;
      }
      
      return true;     
    }

    return false;
}
void GameButton::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
  if (m_gameButtonTouchMode == FIRE_ON_TOUCH_ENDED)
  {
    if (containsTouchLocation(touch))
    {      
      //setButtonState(GRABBED);
    }
    else
    {
      //setButtonState(UNGRABBED);
    }
  }
}
void GameButton::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
  if (m_gameButtonTouchMode == FIRE_ON_TOUCH_ENDED)
  {    
    this->fadeOutSound(.16f);

    if (containsTouchLocation(touch))
    {      
      this->playAnimation(RELEASING, true); 
      
      CCTime::gettimeofdayCocos2d(&this->m_touchEndedTime, NULL);      
      this->m_lastTouchDuration = MAX(0, (this->m_touchEndedTime.tv_sec - this->m_touchStartedTime.tv_sec) + (this->m_touchEndedTime.tv_usec - this->m_touchStartedTime.tv_usec) / 1000000.0f);
  
      if(m_pTarget != 0 && m_fnpTouchEndedDelegate != 0)
          (m_pTarget->*m_fnpTouchEndedDelegate)(this);
    }
  }
} 