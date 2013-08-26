#include "UtilityHelper.h"


std::string UtilityHelper::convertToString(float f, int decimals)
{
  if (decimals == 0)
    return UtilityHelper::convertToString((int)f);

  char numstr[154];
  const char* format = std::string("%." + UtilityHelper::convertToString(decimals) + "f").c_str();
  sprintf(numstr, format, f);
  return std::string(numstr);
}
std::string UtilityHelper::convertToString(int i)
{
  char numstr[22];
  sprintf(numstr, "%i", i);
  return std::string(numstr);
}

cocos2d::cc_timeval UtilityHelper::getTimeValFromSeconds(float time)
{  
  cocos2d::cc_timeval tv;
  tv.tv_sec = (long)time;
  tv.tv_usec = (time - tv.tv_sec) * 1000000.0f;
  return tv;
}

cocos2d::cc_timeval UtilityHelper::addSeconds(cocos2d::cc_timeval tv, float time)
{
  cocos2d::cc_timeval newTimeval;
  newTimeval.tv_sec = tv.tv_sec + (long)time;
  float usec = tv.tv_usec / 1000000.0f + time - (long)time;
  if (usec >= 1)
  {
    newTimeval.tv_usec = (usec - 1.0f) * 1000000.0f;
    newTimeval.tv_sec += 1;
  }
  else
  {
    newTimeval.tv_usec = usec * 1000000.0f;
  }

  return newTimeval;
}
cocos2d::cc_timeval UtilityHelper::substract(cocos2d::cc_timeval a, cocos2d::cc_timeval b)
{
  cocos2d::cc_timeval newTimeval;

  newTimeval.tv_sec = a.tv_sec - b.tv_sec;
  float usec = (a.tv_usec - b.tv_usec) / 1000000.0f;
  if (usec < .0f)
  {
    newTimeval.tv_usec = (1.0f + usec) * 1000000.0f;
    newTimeval.tv_sec -= 1;
  }
  else
  {
    newTimeval.tv_usec = usec * 1000000.0f;
  }

  return newTimeval;
}

std::vector<std::string> UtilityHelper::split(std::string text, char delim, int rep) 
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