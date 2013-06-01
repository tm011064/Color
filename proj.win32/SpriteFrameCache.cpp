#include "SpriteFrameCache.h"


SpriteFrameCache::SpriteFrameCache(void)
{
}


SpriteFrameCache::~SpriteFrameCache(void)
{
  // TODO (roman): memory management!!!
  // this all seems to be covered by autorelease, but double check
}

void SpriteFrameCache::init()
{
  this->m_cache = CCSpriteFrameCache::sharedSpriteFrameCache();
  this->m_spriteFrameLookup = CCDictionary::create();
}

CCArray* SpriteFrameCache::getSpriteFramesForKey(std::string pList, std::string textureFileName)
{
  std::string key = pList + "_" + textureFileName;
  CCObject* obj = this->m_spriteFrameLookup->objectForKey(key);
  if (obj)
  {
    return (CCArray*)(obj);
  }
  else
  {
    this->m_cache->addSpriteFramesWithFile(pList.c_str(), textureFileName.c_str());
  
    CCDictionary *dict = CCDictionary::createWithContentsOfFile(pList.c_str());
    CCDictionary *framesDict = (CCDictionary*)dict->objectForKey(std::string("frames"));

    CCDictElement* pElement = NULL;
    CCArray* frames = new CCArray;
    CCDICT_FOREACH(framesDict, pElement)
    {
        CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
        std::string spriteFrameName = pElement->getStrKey();
        frames->addObject(this->m_cache->spriteFrameByName( spriteFrameName.c_str() ));
    }

    this->m_spriteFrameLookup->setObject(frames, key);
    return frames;
  }
}