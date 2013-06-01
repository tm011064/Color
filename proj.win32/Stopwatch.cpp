#include "Stopwatch.h"
#include "stdlib.h"
#include "time.h"
#include "cocos2d.h"

Stopwatch::Stopwatch(void)
  : m_elapsed(0)
  , m_isRunning(false)
{
}


Stopwatch::~Stopwatch(void)
{
}

void Stopwatch::start()
{
  if ( m_isRunning )
    return;
     
  CCTime::gettimeofdayCocos2d(&this->m_lastStart, NULL);
}
void Stopwatch::stop()
{
  struct cc_timeval now;
  CCTime::gettimeofdayCocos2d(&now, NULL);
  
  this->m_elapsed += MAX(0, (now.tv_sec - this->m_lastStart.tv_sec) + (now.tv_usec - this->m_lastStart.tv_usec) / 1000000.0f); 
  this->m_isRunning = false;
}
void Stopwatch::restart()
{
  this->m_elapsed = 0;
  this->m_isRunning = false;

  start();
}
float Stopwatch::getElapsed()
{
  return this->m_elapsed;
}
std::string Stopwatch::getElapsedText()
{  
  std::ostringstream ss;
  ss << "Elapsed time: " << (this->m_elapsed * 1000.0f) << " ms.";
  std::string s(ss.str());

  return s;
}
