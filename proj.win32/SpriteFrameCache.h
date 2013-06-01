#ifndef __SPRITE_FRAME_CACHE_H__
#define __SPRITE_FRAME_CACHE_H__

#include "cocos2d.h"

using namespace cocos2d;

class SpriteFrameCache
{
private:
  CCSpriteFrameCache* m_cache;
  CCDictionary* m_spriteFrameLookup;

public:
  SpriteFrameCache(void);
  ~SpriteFrameCache(void);

  void init();
  CCArray* getSpriteFramesForKey(std::string pList, std::string textureFileName);
};

#endif  // __SPRITE_FRAME_CACHE_H__