#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__

#include "cocos2d.h"

using namespace cocos2d;

class Stopwatch
{
private:
  struct cc_timeval m_lastStart;
  bool m_isRunning;
  float m_elapsed;

public:
  Stopwatch(void);
  ~Stopwatch(void);

  void start();
  void stop();
  void restart();

  float getElapsed();
  std::string getElapsedText();
};

#endif  // __STOPWATCH_H__