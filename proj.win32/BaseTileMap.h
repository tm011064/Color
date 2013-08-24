#ifndef _BASETILEMAP_H
#define _BASETILEMAP_H

#include "cocos2d.h"


typedef struct 
{
  std::string identifier;
  std::string key;
  std::string value;
} TripleTag;

using namespace cocos2d;

class BaseTileMap
{
  std::map<std::string, std::vector<CCSpriteFrame*> > m_animationGroups;
  std::map<std::string, CCSpriteFrame*> m_spriteFrameNameLookup;
  TripleTag ParseTripleTag(std::string text);

public:
  //
  BaseTileMap();
  BaseTileMap(const char *pList, const char *textureFileName);
  ~BaseTileMap();

  void RegisterImage(const char *filePath, const char *key);
  void RegisterTextureFileName(const char *pList, const char *textureFileName);
  CCSpriteFrame* getTile(std::string name);
  CCSpriteFrame* getTile(std::string animationGroupName, int index);
  std::vector<CCSpriteFrame*>* getTiles(std::string animationGroupName);
};

#endif