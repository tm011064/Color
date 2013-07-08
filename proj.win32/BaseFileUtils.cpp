#include "BaseFileUtils.h"

std::vector<std::string> BaseFileUtils::getNumberedKeys(const char *key)
{
  std::vector<std::string> list;
  
  CCArray* keys = this->m_pFilenameLookupDict->allKeys();
  
  std::string keyString = std::string(key);
  CCObject* o;
  std::string s;

  CCARRAY_FOREACH(keys, o)
  {    
    s = std::string(((CCString*)o)->getCString());
    if (s.length() >= keyString.length()
      && s.substr(0, keyString.length()) == keyString)
    {
      list.push_back(s);
    }
  }
  o = NULL;
  keys = NULL;

  return list;
}
std::vector<std::string> BaseFileUtils::getNumberedResourceFiles(const char *key)
{
  std::vector<std::string> list;
  
  CCArray* keys = this->m_pFilenameLookupDict->allKeys();
  
  std::string keyString = std::string(key);
  CCObject* o;
  std::string s;

  CCARRAY_FOREACH(keys, o)
  {    
    s = std::string(((CCString*)o)->getCString());
    if (s.length() >= keyString.length()
      && s.substr(0, keyString.length()) == keyString)
    {
      list.push_back(((CCString*)this->m_pFilenameLookupDict->objectForKey(s))->getCString());
    }
  }
  o = NULL;
  keys = NULL;

  return list;
}

std::string BaseFileUtils::valueForKey(std::string key)
{
  CCString* s = (CCString*)this->m_pFilenameLookupDict->objectForKey(key);
  if ( s != NULL )
  {
    return s->getCString();
  }
}