#ifndef __UTILITYHELPER_H__
#define __UTILITYHELPER_H__

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

#include "cocos2d.h"

class UtilityHelper
{
public:

  static bool startsWith(std::string str, std::string pattern)
  {
    return pattern.length() <= str.length() 
        && equal(pattern.begin(), pattern.end(), str.begin());
  }

  static float getTimeDelta(cocos2d::cc_timeval a, cocos2d::cc_timeval b)
  {
    return MAX(0, (a.tv_sec - b.tv_sec) + (a.tv_usec - b.tv_usec) / 1000000.0f);
  }
  static bool isLessThan(cocos2d::cc_timeval a, cocos2d::cc_timeval b)
  {
    return (a.tv_sec == b.tv_sec) 
      ? a.tv_usec < b.tv_usec
      : a.tv_sec < b.tv_sec;
  }  
  static float getSeconds(cocos2d::cc_timeval tv)
  {
    return tv.tv_sec + tv.tv_usec / 1000000.0f; 
  }
  static cocos2d::cc_timeval substract(cocos2d::cc_timeval a, cocos2d::cc_timeval b);
  static cocos2d::cc_timeval getTimeValFromSeconds(float time);
  static cocos2d::cc_timeval addSeconds(cocos2d::cc_timeval tv, float time);

  static std::string &ltrim(std::string &s) 
  {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
  }
  static std::string &rtrim(std::string &s) 
  {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
  }
  static std::string &trim(std::string &s) { return ltrim(rtrim(s)); }

  static std::vector<std::string> split(std::string text, char delim, int rep);

  static std::string convertToString(float f, int decimals);
  static std::string convertToString(int i);
  static std::string convertLongToString(long l);
};

#endif /* __UTILITYHELPER_H__ */
