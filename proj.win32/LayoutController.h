#ifndef __LAYOUTCONTROLLER_H__
#define __LAYOUTCONTROLLER_H__

#include "cocos2d.h"
#include "GameEngineIncludes.h"

using namespace cocos2d;

class LayoutController
{  
public:
    
  LayoutController() { }
  ~LayoutController() { }
    
  static CCArray* createTwoButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
    , CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate);
  
  static CCArray* createThreeButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
    , CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate);
    
  static CCArray* createFourButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
    , CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate);
          
  static CCArray* createFiveButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
    , CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate);

};
#endif  // __LAYOUTCONTROLLER_H__