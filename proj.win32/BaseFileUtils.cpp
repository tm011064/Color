#include "BaseFileUtils.h"

std::vector<std::string> BaseFileUtils::getNumberedResourceFiles(const char *key)
{
  std::vector<std::string> list;
  
  CCArray* keys = this->m_pFilenameLookupDict->allKeys();

  std::string keyString = std::string(key);
  CCObject* o;
  
  CCARRAY_FOREACH(keys, o)
  {    
    std::string s = std::string(((CCString*)o)->getCString());
    if (s.length() >= keyString.length()
      && s.substr(0, keyString.length()) == keyString)
    {
      list.push_back(((CCString*)this->m_pFilenameLookupDict->objectForKey(s))->getCString());
    }
  }

  return list;
}