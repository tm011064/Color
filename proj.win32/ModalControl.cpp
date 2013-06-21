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