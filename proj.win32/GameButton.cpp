#include "GameButton.h"
#include "VisibleRect.h"
#include "BaseScene.h"
#include "NavigationManager.h"
#include "SimpleAudioEngine.h"

GameButton* GameButton::createThirdButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate, std::string soundPath, GameContext* gameContext)
{
  GameButton* gameButton = new GameButton(pTarget, touchEndedDelegate, preLoadDelegate, gameContext, soundPath);
  gameButton->init();    // Must call init for latest version cocos2d-x

  pTarget->addChild(gameButton);
  
  gameButton->setAnimationFrames(gameContext->getSpriteFrameCache()->getSpriteFramesForKey(
      NavigationManager::getPath(gameContext, "buttonmap.plist")
      , NavigationManager::getPath(gameContext, "buttonmap.png")));    

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
GameButton* GameButton::createQuarterButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate, std::string soundPath, GameContext* gameContext)
{
  GameButton* gameButton = new GameButton(pTarget, touchEndedDelegate, preLoadDelegate, gameContext, soundPath);
  gameButton->init();    // Must call init for latest version cocos2d-x

  pTarget->addChild(gameButton);
  
  gameButton->setAnimationFrames(gameContext->getSpriteFrameCache()->getSpriteFramesForKey(
      NavigationManager::getPath(gameContext, "buttonmap.plist")
      , NavigationManager::getPath(gameContext, "buttonmap.png"))); 

  gameButton->setColor(color);
  
  gameButton->setAlphaMapStillFrameIndex(11);
  gameButton->registerStillFrame(IDLE, 11, 0, false);  
  int pressingFrames[] = { 11,13,15,17,21 };
  gameButton->registerAnimation(PRESSING, pressingFrames, 5, 1, 0, 30, false, false);  
  int releasingFrames[] = { 18,16,13,11 };
  gameButton->registerAnimation(RELEASING, releasingFrames, 4, 1, 0, 30, false, false);  
  gameButton->registerStillFrame(PRESSED, 21, 0, false);  
  int blinkFrames[] = { 13,16,19,21,20,17,15,14,13,12,11 };
  gameButton->registerAnimation(BLINK, blinkFrames, 11, 1, blinkEndedDelegate, 30, false, false);

  return gameButton;
}

GameButton* GameButton::createFifthButton(const ccColor3B& color, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate, std::string soundPath, GameContext* gameContext)
{
  GameButton* gameButton = new GameButton(pTarget, touchEndedDelegate, preLoadDelegate, gameContext, soundPath);
  gameButton->init();    // Must call init for latest version cocos2d-x

  pTarget->addChild(gameButton);
  
  gameButton->setAnimationFrames(gameContext->getSpriteFrameCache()->getSpriteFramesForKey(
      NavigationManager::getPath(gameContext, "buttonmap.plist")
      , NavigationManager::getPath(gameContext, "buttonmap.png")));   

  gameButton->setColor(color);
  
  gameButton->setAlphaMapStillFrameIndex(22);
  gameButton->registerStillFrame(IDLE, 22, 0, false);  
  int pressingFrames[] = { 22,24,26,28,32 };
  gameButton->registerAnimation(PRESSING, pressingFrames, 5, 1, 0, 30, false, false);  
  int releasingFrames[] = { 29,27,24,22 };
  gameButton->registerAnimation(RELEASING, releasingFrames, 4, 1, 0, 30, false, false);  
  gameButton->registerStillFrame(PRESSED, 32, 0, false);  
  int blinkFrames[] = { 24,27,30,32,31,28,26,25,24,23,22 };
  gameButton->registerAnimation(BLINK, blinkFrames, 11, 1, blinkEndedDelegate, 30, false, false);

  return gameButton;
}

void GameButton::playAnimation(int animationIndex)
{
  switch (animationIndex)
  {
  case BLINK: 
  case RELEASING:
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(this->m_soundPath.c_str());    
  break;
  }
  BaseSprite::playAnimation(animationIndex);
}

void GameButton::setButtonState(ButtonState buttonState)
{ 
  ButtonState oldButtonState = this->m_buttonState;
  this->m_buttonState = buttonState;

  switch (buttonState)
  {
  case GRABBED:
    if (oldButtonState == UNGRABBED)
    {     
      this->playAnimation(PRESSING);      
    }
    break;
  case UNGRABBED:
    if (oldButtonState == GRABBED)
    {
      this->playAnimation(RELEASING);
    }
    break;
  }

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
    if (((BaseScene*)this->getParent())->getSceneState() != AWAITING_INPUT)
      return false;

    if (containsTouchLocation(touch))
    {      
      setButtonState(GRABBED);
      return true;     
    }
    else
    {
      setButtonState(UNGRABBED);
    }

    return false;
}
void GameButton::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    if (containsTouchLocation(touch))
    {      
      setButtonState(GRABBED);
    }
    else
    {
      setButtonState(UNGRABBED);
    }
}
void GameButton::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    if (containsTouchLocation(touch))
    {      
      // TODO (Roman): wait for animation end
      if(m_pTarget != 0 && m_fnpTouchEndedDelegate != 0)
          (m_pTarget->*m_fnpTouchEndedDelegate)(this);      
    }

    setButtonState(UNGRABBED);
} 