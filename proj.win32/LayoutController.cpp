#include "LayoutController.h"
#include <cstdlib>

CCArray* LayoutController::createTwoButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate)
{
  CCPoint top = VisibleRect::top();
  CCPoint right = VisibleRect::right();
  CCPoint center = VisibleRect::center();
  CCPoint left = VisibleRect::left();
        
  CCRect visibleRect = VisibleRect::getVisibleRect();        

  GameButton* b4 = GameButton::createQuarterButton( BUTTON_COLOR_RED, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s1.wav"
    , gameContext);
  GameButton* b3 = GameButton::createQuarterButton( BUTTON_COLOR_GREEN, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s2.wav"
    , gameContext);
  GameButton* b2 = GameButton::createQuarterButton( BUTTON_COLOR_YELLOW, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s3.wav"
    , gameContext);
  GameButton* b1 = GameButton::createQuarterButton( BUTTON_COLOR_BLUE, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s4.wav"
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
  int index, counter = 2;
  GameButton* button;
  while (counter > 0)
  {
    index = rand() % buttons->capacity();
    button = (GameButton*)buttons->objectAtIndex(index);
    if (button->getIsEnabled())
    {
      button->setColor(BUTTON_COLOR_BLACK);
      button->setOriginalColor(BUTTON_COLOR_BLACK);
      button->setIsEnabled(false);
      counter--;
    }
  }
  button = NULL;
  
  b1->release();
  b2->release();
  b3->release();
  b4->release();

  return buttons;
}

CCArray* LayoutController::createThreeButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate)
{
  CCPoint top = VisibleRect::top();
  CCPoint right = VisibleRect::right();
  CCPoint center = VisibleRect::center();
  CCPoint left = VisibleRect::left();
        
  CCRect visibleRect = VisibleRect::getVisibleRect();        

  GameButton* b4 = GameButton::createQuarterButton( BUTTON_COLOR_RED, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s1.wav"
    , gameContext);
  GameButton* b3 = GameButton::createQuarterButton( BUTTON_COLOR_GREEN, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s2.wav"
    , gameContext);
  GameButton* b2 = GameButton::createQuarterButton( BUTTON_COLOR_YELLOW, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s3.wav"
    , gameContext);
  GameButton* b1 = GameButton::createQuarterButton( BUTTON_COLOR_BLUE, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s4.wav"
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
  GameButton* button = (GameButton*)buttons->objectAtIndex(rand() % buttons->capacity());
  button->setColor(BUTTON_COLOR_BLACK);
  button->setOriginalColor(BUTTON_COLOR_BLACK);
  button->setIsEnabled(false);
  
  b1->release();
  b2->release();
  b3->release();
  b4->release();

  return buttons;
}

CCArray* LayoutController::createFourButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate)
{
  CCPoint top = VisibleRect::top();
  CCPoint right = VisibleRect::right();
  CCPoint center = VisibleRect::center();
  CCPoint left = VisibleRect::left();
        
  CCRect visibleRect = VisibleRect::getVisibleRect();        

  GameButton* b4 = GameButton::createQuarterButton( BUTTON_COLOR_RED, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s1.wav"
    , gameContext);
  GameButton* b3 = GameButton::createQuarterButton( BUTTON_COLOR_GREEN, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s2.wav"
    , gameContext);
  GameButton* b2 = GameButton::createQuarterButton( BUTTON_COLOR_YELLOW, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s3.wav"
    , gameContext);
  GameButton* b1 = GameButton::createQuarterButton( BUTTON_COLOR_BLUE, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s4.wav"
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
        
  CCArray* buttons = CCArray::create();
  buttons->retain();
  
  buttons->addObject(b1);
  buttons->addObject(b2);
  buttons->addObject(b3);
  buttons->addObject(b4);
  
  b1->release();
  b2->release();
  b3->release();
  b4->release();
  
  return buttons;
}