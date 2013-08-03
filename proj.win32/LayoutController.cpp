#include "LayoutController.h"
#include <cstdlib>

CCArray* LayoutController::createGameButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor
  , CCNode *pTarget
  , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
  , GameButtonTouchMode gameButtonTouchMode, GameButtonSoundMode gameButtonSoundMode
  , ccColor3B buttonColor1, ccColor3B buttonColor2, ccColor3B buttonColor3, ccColor3B buttonColor4
  , int totalDisabledButtons)
{
  CCPoint top = VisibleRect::top();
  CCPoint right = VisibleRect::right();
  CCPoint center = VisibleRect::center();
  CCPoint left = VisibleRect::left();
        
  CCRect visibleRect = VisibleRect::getVisibleRect();        

  std::string soundKeyPrefix;
  switch (gameButtonSoundMode)
  {
  case DRUMS: soundKeyPrefix = "buttonsound_normal_"; break;
  case OSCIL: soundKeyPrefix = "buttonsound_long_"; break;
  }

  GameButton* b4 = GameButton::createQuarterButton( buttonColor1, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath(soundKeyPrefix + "1")
    , gameButtonTouchMode
    , gameContext);
  GameButton* b3 = GameButton::createQuarterButton( buttonColor2, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath(soundKeyPrefix + "2")
    , gameButtonTouchMode
    , gameContext);
  GameButton* b2 = GameButton::createQuarterButton( buttonColor3, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath(soundKeyPrefix + "3")
    , gameButtonTouchMode
    , gameContext);
  GameButton* b1 = GameButton::createQuarterButton( buttonColor4, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath(soundKeyPrefix + "4")
    , gameButtonTouchMode
    , gameContext);
      
  CCSize size = b1->getContentSize();
      
  float availableWidth = visibleRect.size.width / 2;
  float filledWidth = availableWidth * BUTTON_QUARTER_SCALE;
        
  float buttonScale = filledWidth / size.width;

  float offset = (availableWidth - filledWidth + size.width * buttonScale) / 2;

  b4->setPosition(ccp(anchor.x - offset, anchor.y + offset));
  b3->setPosition(ccp(anchor.x - offset, anchor.y - offset));
  b1->setPosition(ccp(anchor.x + offset, anchor.y + offset));
  b2->setPosition(ccp(anchor.x + offset, anchor.y - offset));
            
  b1->setRotation(90);
  b2->setRotation(180);
  b3->setRotation(-90);
      
  b4->setScale(buttonScale);
  b3->setScale(buttonScale);
  b1->setScale(buttonScale);
  b2->setScale(buttonScale);
        
  CCArray* buttons = new CCArray;
  buttons->addObject(b1);
  buttons->addObject(b2);
  buttons->addObject(b3);
  buttons->addObject(b4);
    
  std::srand(time(NULL));
  int index;
  GameButton* button;
  while (totalDisabledButtons > 0)
  {
    index = rand() % buttons->capacity();
    button = (GameButton*)buttons->objectAtIndex(index);
    if (button->getIsEnabled())
    {
      button->setColor(BUTTON_COLOR_BLACK);
      button->setOriginalColor(BUTTON_COLOR_BLACK);
      button->setIsEnabled(false);
      totalDisabledButtons--;
    }
  }
  button = NULL;
  
  b1->release();
  b2->release();
  b3->release();
  b4->release();

  return buttons;
}

CCArray* LayoutController::createOneButton(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode, GameButtonSoundMode gameButtonSoundMode)
{
  return LayoutController::createGameButtons(gameContext, debugDraw, anchor, pTarget
    , touchEndedDelegate, preLoadDelegate, blinkEndedDelegate
    , gameButtonTouchMode, gameButtonSoundMode
    , BUTTON_COLOR_RED, BUTTON_COLOR_GREEN, BUTTON_COLOR_YELLOW, BUTTON_COLOR_BLUE
    , 3);
}
CCArray* LayoutController::createTwoButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode, GameButtonSoundMode gameButtonSoundMode)
{
  return LayoutController::createGameButtons(gameContext, debugDraw, anchor, pTarget
    , touchEndedDelegate, preLoadDelegate, blinkEndedDelegate
    , gameButtonTouchMode, gameButtonSoundMode
    , BUTTON_COLOR_RED, BUTTON_COLOR_GREEN, BUTTON_COLOR_YELLOW, BUTTON_COLOR_BLUE
    , 2);
}
CCArray* LayoutController::createThreeButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode, GameButtonSoundMode gameButtonSoundMode)
{
  return LayoutController::createGameButtons(gameContext, debugDraw, anchor, pTarget
    , touchEndedDelegate, preLoadDelegate, blinkEndedDelegate
    , gameButtonTouchMode, gameButtonSoundMode
    , BUTTON_COLOR_RED, BUTTON_COLOR_GREEN, BUTTON_COLOR_YELLOW, BUTTON_COLOR_BLUE
    , 1);
}
CCArray* LayoutController::createFourButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode, GameButtonSoundMode gameButtonSoundMode)
{
  return LayoutController::createGameButtons(gameContext, debugDraw, anchor, pTarget
    , touchEndedDelegate, preLoadDelegate, blinkEndedDelegate
    , gameButtonTouchMode, gameButtonSoundMode
    , BUTTON_COLOR_RED, BUTTON_COLOR_GREEN, BUTTON_COLOR_YELLOW, BUTTON_COLOR_BLUE
    , 0);
}

CCArray* LayoutController::createFourButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate
    , GameButtonTouchMode gameButtonTouchMode, GameButtonSoundMode gameButtonSoundMode
    , ccColor3B buttonColor1, ccColor3B buttonColor2, ccColor3B buttonColor3, ccColor3B buttonColor4)
{  
  return LayoutController::createGameButtons(gameContext, debugDraw, anchor, pTarget
    , touchEndedDelegate, preLoadDelegate, blinkEndedDelegate
    , gameButtonTouchMode, gameButtonSoundMode
    , buttonColor1, buttonColor2, buttonColor3, buttonColor4
    , 0);
}