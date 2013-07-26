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
      
  static CCArray* createOneButton(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
    , CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode);

  static CCArray* createTwoButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
    , CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode);
  
  static CCArray* createThreeButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
    , CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode);
    
  static CCArray* createFourButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
    , CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode);
    
  static CCArray* createFourButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
    , CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode
    , ccColor3B buttonColor1, ccColor3B buttonColor2, ccColor3B buttonColor3, ccColor3B buttonColor4);

private:
  static CCArray* createGameButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
    , CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode
    , ccColor3B buttonColor1, ccColor3B buttonColor2, ccColor3B buttonColor3, ccColor3B buttonColor4
    , int totalDisabledButtons);

};
#endif  // __LAYOUTCONTROLLER_H__