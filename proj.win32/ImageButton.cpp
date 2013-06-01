#include "ImageButton.h"
#include "VisibleRect.h"
#include "BaseScene.h"
#include "NavigationManager.h"

ImageButton* ImageButton::create(CCNode *pTarget, SEL_CallFuncO touchEndedDelegate
  , SEL_CallFuncO preLoadDelegate, GameContext* gameContext
  , std::string pList, std::string textureFileName
  , int alphaMapStillFrameIndex // set to -1 if no alpha map is needed
  , int idleFrameIndex
  , int pressingFrames[], int totalPressingFrames
  , int releasingFrames[], int totalReleasingFrames
  , int pressedFrame
  , int disabledFrame
  , int touchPriority
  )
{
  ImageButton* imageButton = new ImageButton(pTarget, touchEndedDelegate, preLoadDelegate, gameContext);

  imageButton->setTouchPriority(touchPriority);
  imageButton->init();    // Must call init for latest version cocos2d-x
  
  pTarget->addChild(imageButton);
  
  imageButton->setAnimationFrames(gameContext->getSpriteFrameCache()->getSpriteFramesForKey(pList, textureFileName)); 
    
  if (alphaMapStillFrameIndex >= 0)
    imageButton->setAlphaMapStillFrameIndex(alphaMapStillFrameIndex);

  imageButton->registerStillFrame(IDLE, idleFrameIndex, 0, false);    
  imageButton->registerAnimation(PRESSING, pressingFrames, totalPressingFrames, 1, 0, 30, false, false);  
  imageButton->registerAnimation(RELEASING, releasingFrames, totalReleasingFrames, 1, 0, 30, false, false);  
  imageButton->registerStillFrame(PRESSED, pressedFrame, 0, false);
  imageButton->registerStillFrame(DISABLED, disabledFrame, 0, false);

  imageButton->playAnimation(IDLE);
    
  return imageButton;
}

void ImageButton::setButtonState(ButtonState buttonState)
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

void ImageButton::setIsEnabled(bool isEnabled)
{
  this->m_isEnabled = isEnabled;
  if (isEnabled)
  {
    this->playAnimation(IDLE);
  }
  else
  {
    this->playAnimation(DISABLED);
  }
}

bool ImageButton::containsTouchLocation(CCTouch* touch)
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

bool ImageButton::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
  if (this->m_bVisible && this->m_isEnabled && containsTouchLocation(touch))
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
void ImageButton::ccTouchMoved(CCTouch* touch, CCEvent* event)
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
void ImageButton::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    if (containsTouchLocation(touch))
    {      
      // TODO (Roman): wait for animation end
      if(m_pTarget != 0 && m_fnpTouchEndedDelegate != 0)
          (m_pTarget->*m_fnpTouchEndedDelegate)(this);
    }

    setButtonState(UNGRABBED);
} 