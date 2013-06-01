#include "LayoutController.h"

CCArray* LayoutController::createThreeButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate)
{
  CCPoint top = VisibleRect::top();
  CCPoint right = VisibleRect::right();
  CCPoint center = VisibleRect::center();
  CCPoint left = VisibleRect::left();
      
  CCRect visibleRect = VisibleRect::getVisibleRect();
            
  GameButton* b3 = GameButton::createThirdButton( BUTTON_COLOR_GREEN, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s1.wav"
    , gameContext);
  GameButton* b2 = GameButton::createThirdButton( BUTTON_COLOR_RED, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s2.wav"
    , gameContext);
  GameButton* b1 = GameButton::createThirdButton( BUTTON_COLOR_YELLOW, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s3.wav"
    , gameContext);
      
  CCSize size = b1->getContentSize();
      
  float availableWidth = visibleRect.size.width / 2;
  float filledWidth = availableWidth * BUTTON_THIRD_SCALE;
    
#if 0
  debugDraw->appendLine(ccp(VisibleRect::bottom().x, 0), ccp(VisibleRect::top().x, VisibleRect::top().y), 100, 100, 100);
  debugDraw->appendLine(ccp(0, anchor.y), ccp(VisibleRect::right().x, anchor.y), 100, 100, 100);
#endif

#if 0
  float length = 200;

  float angle1 = 90.0f;
  float angle2 = angle1 + 120.0f;
  float angle3 = angle1 - 120.0f;
    
  debugDraw->appendLine(ccp(anchor.x, anchor.y)
    , ccp(anchor.x + length * std::cos(CC_DEGREES_TO_RADIANS(angle1))
        , anchor.y + length * std::sin(CC_DEGREES_TO_RADIANS(angle1))), 0, 255, 0);
  debugDraw->appendLine(ccp(anchor.x, anchor.y)
    , ccp(anchor.x + length * std::cos(CC_DEGREES_TO_RADIANS(angle2))
        , anchor.y + length * std::sin(CC_DEGREES_TO_RADIANS(angle2))), 0, 255, 0);
  debugDraw->appendLine(ccp(anchor.x, anchor.y)
    , ccp(anchor.x + length * std::cos(CC_DEGREES_TO_RADIANS(angle3))
        , anchor.y + length * std::sin(CC_DEGREES_TO_RADIANS(angle3))), 0, 255, 0);

  debugDraw->appendCircle(anchor.x, anchor.y, visibleRect.size.width * BUTTON_THIRD_SCALE / 2, 0, 255, 0);
  debugDraw->appendCircle(anchor.x, anchor.y, visibleRect.size.width * BUTTON_THIRD_SCALE / 2 * .25, 0, 255, 0);

#endif

  float buttonScale = filledWidth / size.width;
    
  float offsetX = (size.width * buttonScale)   * .53;

  float offsetY1 = (size.height * buttonScale) * .21;
  float offsetY2 = (size.width * buttonScale)  * .63;
    
  CCPoint buttonAnchor = ccp(.5026281,.52); // TODO (Roman): magic number
    
  b1->setAnchorPoint(buttonAnchor);
  b2->setAnchorPoint(buttonAnchor);
  b3->setAnchorPoint(buttonAnchor);

  b1->setPosition(ccp(anchor.x - offsetX, anchor.y + offsetY1));
  b2->setPosition(ccp(anchor.x, anchor.y - offsetY2)); 
  b3->setPosition(ccp(anchor.x + offsetX, anchor.y + offsetY1));
            
  b2->setRotation(240);
  b3->setRotation(120);
      
  b3->setScale(buttonScale);
  b1->setScale(buttonScale);
  b2->setScale(buttonScale);
        
  CCArray* buttons = new CCArray;
  buttons->addObject(b1);
  buttons->addObject(b2);
  buttons->addObject(b3);
            
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
        
  CCArray* buttons = new CCArray;
  buttons->addObject(b1);
  buttons->addObject(b2);
  buttons->addObject(b3);
  buttons->addObject(b4);
            
  return buttons;
}

CCArray* LayoutController::createFiveButtons(GameContext* gameContext, DebugDraw* debugDraw, CCPoint anchor, CCNode *pTarget
    , SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate, SEL_CallFuncO blinkEndedDelegate)
{
  CCPoint top = VisibleRect::top();
  CCPoint right = VisibleRect::right();
  CCPoint center = VisibleRect::center();
  CCPoint left = VisibleRect::left();

  CCRect visibleRect = VisibleRect::getVisibleRect();
    
  GameButton* b5 = GameButton::createFifthButton( BUTTON_COLOR_PURPLE, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s1.wav"
    , gameContext);
  GameButton* b4 = GameButton::createFifthButton( BUTTON_COLOR_RED, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s2.wav"
    , gameContext);
  GameButton* b3 = GameButton::createFifthButton( BUTTON_COLOR_GREEN, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s3.wav"
    , gameContext);
  GameButton* b2 = GameButton::createFifthButton( BUTTON_COLOR_YELLOW, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s4.wav"
    , gameContext);
  GameButton* b1 = GameButton::createFifthButton( BUTTON_COLOR_BLUE, pTarget
    , touchEndedDelegate
    , preLoadDelegate
    , blinkEndedDelegate
    , gameContext->getSoundPath() + "button_s5.wav"
    , gameContext);
      
  CCSize size = b1->getContentSize();
      
  float availableWidth = visibleRect.size.width / 2;
  float filledWidth = availableWidth * BUTTON_FIFTH_SCALE;

#if 0
  debugDraw->appendLine(ccp(VisibleRect::bottom().x, 0), ccp(VisibleRect::top().x, VisibleRect::top().y), 100, 100, 100);
  debugDraw->appendLine(ccp(0, anchor.y), ccp(VisibleRect::right().x, anchor.y), 100, 100, 100);
#endif

#if 0
  float length = 200;

  float angle1 = 54.0f;
  float angle2 = angle1 + 72.0f;
  float angle3 = angle2 + 72.0f;
  float angle4 = angle3 + 72.0f;
  float angle5 = angle4 + 72.0f;

  debugDraw->appendLine(ccp(anchor.x, anchor.y)
    , ccp(anchor.x + length * std::cos(CC_DEGREES_TO_RADIANS(angle1))
        , anchor.y + length * std::sin(CC_DEGREES_TO_RADIANS(angle1))), 0, 255, 0);
  debugDraw->appendLine(ccp(anchor.x, anchor.y)
    , ccp(anchor.x + length * std::cos(CC_DEGREES_TO_RADIANS(angle2))
        , anchor.y + length * std::sin(CC_DEGREES_TO_RADIANS(angle2))), 0, 255, 0);
  debugDraw->appendLine(ccp(anchor.x, anchor.y)
    , ccp(anchor.x + length * std::cos(CC_DEGREES_TO_RADIANS(angle3))
        , anchor.y + length * std::sin(CC_DEGREES_TO_RADIANS(angle3))), 0, 255, 0);
  debugDraw->appendLine(ccp(anchor.x, anchor.y)
    , ccp(anchor.x + length * std::cos(CC_DEGREES_TO_RADIANS(angle4))
        , anchor.y + length * std::sin(CC_DEGREES_TO_RADIANS(angle4))), 0, 255, 0);
  debugDraw->appendLine(ccp(anchor.x, anchor.y)
    , ccp(anchor.x + length * std::cos(CC_DEGREES_TO_RADIANS(angle5))
        , anchor.y + length * std::sin(CC_DEGREES_TO_RADIANS(angle5))), 0, 255, 0);

  debugDraw->appendCircle(anchor.x, anchor.y, visibleRect.size.width * BUTTON_FIFTH_SCALE / 2, 0, 255, 0);
  debugDraw->appendCircle(anchor.x, anchor.y, visibleRect.size.width * BUTTON_FIFTH_SCALE / 2 * .25, 0, 255, 0);

#endif

  float buttonScale = filledWidth / size.width;

  float offsetX1 = (size.width * buttonScale) * -.0043;
  float offsetX2 = (size.width * buttonScale) *  .6321;
  float offsetX3 = (size.width * buttonScale) *  .3870;
  float offsetX4 = (size.width * buttonScale) * -.3870;
  float offsetX5 = (size.width * buttonScale) * -.6321;
    
  float offsetY1 = (size.height * buttonScale) *  .4515;
  float offsetY2 = (size.height * buttonScale) *  .1411;
  float offsetY3 = (size.height * buttonScale) * -.3645;
  float offsetY4 = (size.height * buttonScale) * -.3645;
  float offsetY5 = (size.height * buttonScale) *  .1411;

  CCPoint buttonAnchor = ccp(.59343, .47); // TODO (Roman): magic number
    
  b1->setAnchorPoint(buttonAnchor);
  b2->setAnchorPoint(buttonAnchor);
  b3->setAnchorPoint(buttonAnchor);
  b4->setAnchorPoint(buttonAnchor);
  b5->setAnchorPoint(buttonAnchor);

  b1->setPosition(ccp(anchor.x + offsetX1, anchor.y + offsetY1));
  b2->setPosition(ccp(anchor.x + offsetX2, anchor.y + offsetY2));
  b3->setPosition(ccp(anchor.x + offsetX3, anchor.y + offsetY3));
  b4->setPosition(ccp(anchor.x + offsetX4, anchor.y + offsetY4));
  b5->setPosition(ccp(anchor.x + offsetX5, anchor.y + offsetY5));
            
  b1->setRotation(36);
  b2->setRotation(108);
  b3->setRotation(180);
  b4->setRotation(252);
  b5->setRotation(324);
      
  b1->setScale(buttonScale);
  b2->setScale(buttonScale);
  b3->setScale(buttonScale);
  b4->setScale(buttonScale);
  b5->setScale(buttonScale);
        
  CCArray* buttons = new CCArray;
  buttons->addObject(b1);
  buttons->addObject(b2);
  buttons->addObject(b3);
  buttons->addObject(b4);
  buttons->addObject(b5);    
    
  return buttons;
}