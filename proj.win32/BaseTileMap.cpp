#include "BaseTileMap.h"

BaseTileMap::BaseTileMap()
{

}
BaseTileMap::BaseTileMap(const char *pList, const char *textureFileName)
{   
  this->RegisterTextureFileName(pList, textureFileName);
}

BaseTileMap::~BaseTileMap(void)
{

}

std::vector<std::string> BaseTileMap::split(std::string text, char delim, int rep) 
{
  std::vector<std::string> flds;

  std::string buf = "";
  int i = 0
    , length = text.length();
  while (i < length) 
  {
      if (text[i] != delim)
          buf += text[i];
      else if (rep == 1) {
          flds.push_back(buf);
          buf = "";
      } else if (buf.length() > 0) {
          flds.push_back(buf);
          buf = "";
      }
      i++;
    }
    if (!buf.empty())
        flds.push_back(buf);
    return flds;
}

TripleTag BaseTileMap::ParseTripleTag(std::string text)
{
  TripleTag tag;

  int index = text.find_first_of(':');
  int index2 = text.find_last_of('=');
    
  tag.identifier = text.substr(0, index);
  tag.key = text.substr(index + 1, index2 - index - 1);
  tag.value = text.substr(index2 + 1, text.length() - index2 - 1);

  return tag;
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
  std::vector<std::string> keyValuePairs;
  std::vector<std::string>::iterator it;
  
  std::string spriteFrameName;
  CCSpriteFrame* frame;
  TripleTag tag;
  int index;
  std::map<std::string, std::vector<CCSpriteFrame*> >::iterator it2; 

  CCDICT_FOREACH(framesDict, pElement)
  {
      spriteFrameName = pElement->getStrKey();
      frame = cache->spriteFrameByName( spriteFrameName.c_str() );

      if (!keyValuePairs.empty()) keyValuePairs.clear();
      keyValuePairs = split(spriteFrameName, ';', 0);      
      for(it=keyValuePairs.begin();it!=keyValuePairs.end();++it)
      {
        tag = ParseTripleTag(*it);

        if (tag.identifier == "x")
        {// default
          if (tag.key == "n")
          {// name            
            m_spriteFrameNameLookup[tag.value] = frame;
          }
        }
        else if (tag.identifier == "g")
        {// animation group
          it2 = m_animationGroups.find(tag.key);
          index = atoi(tag.value.c_str());
          if ( it2 == m_animationGroups.end() )
          {
            std::vector<CCSpriteFrame*> frames; 
            if (frames.size() < index + 1)
              frames.resize(index + 1);
            
            frames[index] = frame;
            m_animationGroups[tag.key] = frames;
          }
          else
          {
            if (it2->second.size() < index + 1)
              it2->second.resize(index + 1);
            
            it2->second[index] = frame;
          }
        }

      }
  }
}

CCSpriteFrame* BaseTileMap::getTile(std::string name)
{
  return m_spriteFrameNameLookup[name];
}
CCSpriteFrame* BaseTileMap::getTile(std::string animationGroupName, int index)
{
  return m_animationGroups[animationGroupName][index];
}
std::vector<CCSpriteFrame*>* BaseTileMap::getTiles(std::string animationGroupName)
{
  return &m_animationGroups[animationGroupName];
}