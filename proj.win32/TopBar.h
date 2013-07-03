#ifndef __TOPBAR_H__
#define __TOPBAR_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"

using namespace cocos2d;

class TopBar : public cocos2d::CCNode
{
private:
  
  CCLabelBMFont* m_levelLabel;
  CCLabelBMFont* m_scoreLabel;

  GameContext* m_gameContext; 
  bool m_isLayoutInitialized;

  CCPoint m_rectOrigin;
  CCPoint m_rectDestination;
  CCPoint m_borderOrigin;
  CCPoint m_borderDestination;

  float m_levelRightPosX;
  float m_scoreRightPosX;

  ccColor4F m_rectColor;
  ccColor4F m_borderColor;

public:  
  TopBar(GameContext* gameContext)
    : m_gameContext(gameContext)
    , m_isLayoutInitialized(false)
  {

  }
  ~TopBar()
  {
    this->m_gameContext = NULL;
  }
  
  CCRect getBoundingBox() { return CCRectMake(m_borderOrigin.x, m_borderOrigin.y, m_rectDestination.x - m_borderOrigin.x, m_rectDestination.y - m_borderOrigin.y); }
  
  virtual void onEnter();
  virtual void draw();

  void setLevel(int level);
  void setScore(long score);
};

#endif  // __TOPBAR_H__