#include "BaseTileMap.h"

BaseTileMap::BaseTileMap()
{
  m_tiles = new CCArray;  
}
BaseTileMap::BaseTileMap(const char *pList, const char *textureFileName)
{  
  m_tiles = new CCArray;  
  this->RegisterTextureFileName(pList, textureFileName);
}

BaseTileMap::~BaseTileMap(void)
{
  CC_SAFE_DELETE(m_tiles);
}

void BaseTileMap::RegisterTextureFileName(const char *pList, const char *textureFileName)
{
  // IMPORTANT:
  // The sprite frames will be cached AND RETAINED, and they won't be released unless you call
  //     CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames);
  CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
  cache->addSpriteFramesWithFile(pList, textureFileName);

  CCDictionary *dict = CCDictionary::createWithContentsOfFile(pList);
  CCDictionary *framesDict = (CCDictionary*)dict->objectForKey(std::string("frames"));

  CCDictElement* pElement = NULL;
  CCDICT_FOREACH(framesDict, pElement)
  {
      CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
      std::string spriteFrameName = pElement->getStrKey();
      CCSpriteFrame* frame = cache->spriteFrameByName( spriteFrameName.c_str() );
      m_tiles->addObject(frame);
  }
}

CCSpriteFrame* BaseTileMap::getTile(int index)
{
  return (CCSpriteFrame *)m_tiles->objectAtIndex(index);
}
CCArray* BaseTileMap::getAllTiles()
{
  return this->m_tiles;
}
