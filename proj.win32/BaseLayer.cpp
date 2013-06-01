#include "BaseLayer.h"

using namespace cocos2d;

BaseLayer::BaseLayer(CCObject* callbackTarget, SEL_CallFunc backKeyCallback)
  : m_backKeyCallback(backKeyCallback)
  , m_callbackTarget(callbackTarget)
{

}
BaseLayer::~BaseLayer()
{

}

bool BaseLayer::init() 
{
  this->setKeypadEnabled(true);
  return CCLayer::init();
}

void BaseLayer::keyBackClicked() 
{  
  if(m_callbackTarget != 0 && this->m_backKeyCallback != 0)
      (m_callbackTarget->*this->m_backKeyCallback)();
}