#ifndef _BASETILEMAP_H
#define _BASETILEMAP_H

#include "cocos2d.h"

using namespace cocos2d;

class BaseTileMap
{
  CCArray *m_tiles;

public:
  //
  BaseTileMap(const char *pList, const char *textureFileName);
  ~BaseTileMap();

  CCSpriteFrame* getTile(int index);
};

#endif