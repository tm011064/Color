#ifndef __UTILITYHELPER_H__
#define __UTILITYHELPER_H__

#include "cocos2d.h"

class UtilityHelper
{
public:
  static float getTimeDelta(cocos2d::cc_timeval a, cocos2d::cc_timeval b)
  {
    return MAX(0, (a.tv_sec - b.tv_sec) + (a.tv_usec - b.tv_usec) / 1000000.0f);
  }
  static float isLessThan(cocos2d::cc_timeval a, cocos2d::cc_timeval b)
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
};

#endif /* __UTILITYHELPER_H__ */
