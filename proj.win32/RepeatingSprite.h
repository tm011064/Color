#ifndef __REPEATINGSPRITE_H__
#define __REPEATINGSPRITE_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"

enum REPEAT_DIRECTION
{
  HORIZONTAL = 0,
  VERTICAL = 1,
  HORIZONTAL_AND_VERTICAL = 2
};

enum REPEAT_MODE
{
  NORMAL = 0,
  ALTERNATING = 1
};

using namespace cocos2d;

class RepeatingSprite : public cocos2d::CCNode
{
private:
  
  CCSpriteFrame* m_spriteFrame;
  GameContext* m_pGameContext;

  bool m_isLayoutInitialized;
  bool m_doAlternateHorizontally;
  REPEAT_DIRECTION m_direction;
  REPEAT_MODE m_mode;
  CCSize m_boundingBox;

public:  
  static RepeatingSprite* create(GameContext* gameContext, CCSpriteFrame* spriteFrame, REPEAT_DIRECTION direction, REPEAT_MODE mode
    , CCSize boundingBox);
  ~RepeatingSprite();

  virtual void onEnter();
protected:
  
  RepeatingSprite(GameContext* gameContext, CCSpriteFrame* spriteFrame, REPEAT_DIRECTION direction, REPEAT_MODE mode
    , CCSize boundingBox)
    : m_pGameContext(gameContext)
    , m_spriteFrame(spriteFrame)
    , m_isLayoutInitialized(false)
    , m_direction(direction)
    , m_mode(mode)
    , m_boundingBox(boundingBox)
  { }
};

#endif  // __REPEATINGSPRITE_H__