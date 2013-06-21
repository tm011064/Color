#ifndef __BASENODE_H__
#define __BASENODE_H__

#include "cocos2d.h"

using namespace cocos2d;

class BaseNode : public cocos2d::CCNode
{  
protected:  

public:
  BaseNode() { }
  ~BaseNode() { }

  virtual void show();
  virtual void hide();
};
#endif  // __BASENODE_H__