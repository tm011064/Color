#include "ModalControl.h"

using namespace cocos2d;

void ModalControl::onEnter()
{
    CCNode::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, TOUCH_PRIORITY_MODAL_PANEL, true);
} 

void ModalControl::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

bool ModalControl::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
  // we swallow everything if visible
  return this->m_bVisible;
}

void ModalControl::show()
{  
  CCObject* o;
  CCARRAY_FOREACH(this->getChildren(), o)
  {    
    CCNode* node = dynamic_cast<CCNode*>(o);
    if (node != NULL)
      node->setVisible(true);
  }
  this->setVisible(true);
} 
void ModalControl::hide()
{
  CCObject* o;
  CCARRAY_FOREACH(this->getChildren(), o)
  {    
    CCNode* node = dynamic_cast<CCNode*>(o);
    if (node != NULL)
      node->setVisible(false);
  }
  this->setVisible(false);
} 