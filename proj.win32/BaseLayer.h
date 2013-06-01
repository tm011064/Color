#ifndef __BASELAYER_SCENE_H__
#define __BASELAYER_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class BaseLayer : public cocos2d::CCLayer
{  
private:
  SEL_CallFunc m_backKeyCallback;
  CCObject* m_callbackTarget;

public:
  BaseLayer(CCObject* callbackTarget, SEL_CallFunc backKeyCallback);
  ~BaseLayer();

  virtual void keyBackClicked();
  virtual bool init();
};
#endif  // __BASELAYER_SCENE_H__