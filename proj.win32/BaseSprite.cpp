#include "BaseSprite.h"
#include "VisibleRect.h"
#include "Types.h"
#include "Stopwatch.h"
#include "GameContext.h"

BaseSprite::BaseSprite(CCNode *pTarget, SEL_CallFuncO touchEndedDelegate, SEL_CallFuncO preLoadDelegate)
://m_fnpSelectorDelegate(0)
 m_pTarget(pTarget)
,m_isPlistLoaded(false)
,m_elaspeTime(0.0)
,m_incrementValue(0)
,m_isAnimationRunning(false)
,m_debugDraw(0)
,m_isLoaded(false)
,m_fnpTouchEndedDelegate(touchEndedDelegate)
,m_fnpPreLoadDelegate(preLoadDelegate)
,m_currentAnimationDefinition(NULL)
, m_alphaMap(0)
, m_alphaMapCols(0)
, m_alphaMapRows(0)
, m_touchPriority(0)
, m_totalFrames(0)
{ }

BaseSprite::~BaseSprite()
{
  // TODO (Roman): is that correct?
  m_currentAnimationDefinition = NULL;

  if (m_alphaMap)
  {
    for (int i = 0; i < m_alphaMapCols; i++)
      free((void *)m_alphaMap[i]);

    free((void *)m_alphaMap);
  }
}

void BaseSprite::setAnimationFrames(CCArray *frames)
{
  this->setAnimationFrames(frames, 0);
}

void BaseSprite::setAnimationFrames(CCArray *frames, int displayTextureIndex)
{
  m_isPlistLoaded = true;

  CC_ASSERT( frames );
  m_animationFrames = frames;

  CCSpriteFrame* spriteFrame = (CCSpriteFrame *)m_animationFrames->objectAtIndex(displayTextureIndex);
  
  CC_ASSERT( spriteFrame );
  setDisplayFrame(spriteFrame);

  spriteFrame = NULL;
}

void BaseSprite::increaseCurrentIndex()
{
  if(m_animationMode && (this->m_currentAnimationDefinition->endIndex - m_currentIndex) != 0)
      m_incrementValue += (this->m_currentAnimationDefinition->endIndex - m_currentIndex) / abs(this->m_currentAnimationDefinition->endIndex - m_currentIndex);
  else if((0 - m_currentIndex) != 0)
      m_incrementValue += (0 - m_currentIndex) / abs(0 - m_currentIndex);
}

void BaseSprite::setDisplayFrameAtIndex(int index)
{
  setDisplayFrame((CCSpriteFrame *)m_animationFrames->objectAtIndex(index));
}


CCSize BaseSprite::getSpriteFrameSize(int index)
{
  CCSpriteFrame* spriteFrame = (CCSpriteFrame *)m_animationFrames->objectAtIndex(index);
  CCSize size = spriteFrame->getOriginalSize();
  size.setSize(size.width * this->getScaleX(), size.height * this->getScaleY());
  return size;
}

void BaseSprite::update(float dt)
{   
  m_elaspeTime += dt;
  while (m_elaspeTime >= m_frameRate) 
  {
    m_elaspeTime -= m_frameRate;
    m_currentIndex += m_incrementValue;
    
    setDisplayFrame((CCSpriteFrame *)m_animationFrames->objectAtIndex(
      this->m_currentAnimationDefinition->plistIndexes.at(m_currentIndex)));

    //Forward Animation....
    if (m_currentIndex == this->m_currentAnimationDefinition->endIndex) 
    {
        if(m_needToRunReverseAnimation)
        {
            m_animationMode = false;
            increaseCurrentIndex();
            return;
        }
            
        m_runningLoop++;
        if(m_runningLoop == this->m_currentAnimationDefinition->totalLoops)
        {
            stopAnimation();
            //Raising Callback.
            if(m_pTarget != 0 && this->m_currentAnimationDefinition->fnpSelectorDelegate != 0)
                (m_pTarget->*this->m_currentAnimationDefinition->fnpSelectorDelegate)(this);
                
            //Remove Object by Itself.
            if(m_needToDeleteItself)
                removeObjectItself();
            return;
        }
        else
        {
            m_currentIndex = 0;
        }
    }    
    else if(m_currentIndex == 0)
    {//Reverse Animation...
        m_runningLoop++;
        if(m_runningLoop == this->m_currentAnimationDefinition->totalLoops)
        {
            stopAnimation();
            //Raising Callback.
            if(m_pTarget != 0 && this->m_currentAnimationDefinition->fnpSelectorDelegate != 0)
                (m_pTarget->*this->m_currentAnimationDefinition->fnpSelectorDelegate)(this);
                
            //Remove Object by Itself.
            if(m_needToDeleteItself)
                removeObjectItself();
            return;
        }
        else
        {
            m_animationMode = true;
            increaseCurrentIndex();
        }
    }
  }
}

void BaseSprite::stopAnimation()
{
  m_isAnimationRunning = false;
  this->unscheduleUpdate();
}

void BaseSprite::removeObjectItself()
{
    this->removeFromParentAndCleanup(true);
    delete (this);
}

void BaseSprite::loadUpdate(float delta)
{  
  for(std::map<int, AnimationDefinition>::iterator ii=m_animationDefinitions.begin(); ii!=m_animationDefinitions.end(); ++ii)
  {
    for(std::vector<int>::iterator jj = (*ii).second.plistIndexes.begin(); jj != (*ii).second.plistIndexes.end(); ++jj)
    {
      this->setDisplayFrame((CCSpriteFrame *)m_animationFrames->objectAtIndex((*jj)));
      this->visit();
    }
  }

  this->m_isLoaded = true;

  if (m_pTarget && m_fnpPreLoadDelegate)
    (m_pTarget->*m_fnpPreLoadDelegate)(this);
    
  this->unschedule(schedule_selector(BaseSprite::loadUpdate));
}

void BaseSprite::load()
{ 
  this->schedule(schedule_selector(BaseSprite::loadUpdate));  
}

void BaseSprite::registerStillFrame(int animationIndex, int plistIndex, SEL_CallFuncO fnpSelectorDelegate, bool needToDeleteItself)
{
  AnimationDefinition animationDefinition;

  //animationDefinition.plistIndexes = new std::vector<int>();
  animationDefinition.plistIndexes.push_back(plistIndex);
  animationDefinition.endIndex = 0;
  animationDefinition.totalLoops = 1;
  animationDefinition.fnpSelectorDelegate = fnpSelectorDelegate;
  animationDefinition.framesPerSecond = 30; // not needed actually
  animationDefinition.needToRunReverseAnimation = false;
  animationDefinition.needToDeleteItself = needToDeleteItself;

  this->m_animationDefinitions[animationIndex] = animationDefinition;

  this->m_totalFrames += 1;
}

void BaseSprite::registerAnimation(int animationIndex, int plistStartIndex, int plistEndIndex, int totalLoops
    , SEL_CallFuncO fnpSelectorDelegate
    , int framesPerSecond, bool needToRunReverseAnimation, bool needToDeleteItself)
{
  AnimationDefinition animationDefinition;
  
  //animationDefinition.plistIndexes = new std::vector<int>();
  for (int i = plistStartIndex; i <= plistEndIndex; i++)
     animationDefinition.plistIndexes.push_back(i);

  animationDefinition.endIndex =  animationDefinition.plistIndexes.size() - 1;
  animationDefinition.totalLoops = totalLoops;
  animationDefinition.fnpSelectorDelegate = fnpSelectorDelegate;
  animationDefinition.framesPerSecond = framesPerSecond;
  animationDefinition.needToRunReverseAnimation = needToRunReverseAnimation;
  animationDefinition.needToDeleteItself = needToDeleteItself;  
  
  this->m_animationDefinitions[animationIndex] = animationDefinition;

  this->m_totalFrames += animationDefinition.plistIndexes.size();
}

void BaseSprite::registerAnimation(int animationIndex, int indexes[], int totalIndexes, int totalLoops
    , SEL_CallFuncO fnpSelectorDelegate
    , int framesPerSecond, bool needToRunReverseAnimation, bool needToDeleteItself)
{ 
  AnimationDefinition animationDefinition;
  
  //animationDefinition.plistIndexes = new std::vector<int>();
  for (int i = 0; i < totalIndexes; i++)
     animationDefinition.plistIndexes.push_back(indexes[i]);

  animationDefinition.endIndex = totalIndexes - 1;
  animationDefinition.totalLoops = totalLoops;
  animationDefinition.fnpSelectorDelegate = fnpSelectorDelegate;
  animationDefinition.framesPerSecond = framesPerSecond;
  animationDefinition.needToRunReverseAnimation = needToRunReverseAnimation;
  animationDefinition.needToDeleteItself = needToDeleteItself;  
  
  this->m_animationDefinitions[animationIndex] = animationDefinition;

  this->m_totalFrames += totalIndexes;
}

void BaseSprite::playAnimation(int animationIndex)
{ 
  if(m_isAnimationRunning)
  {
      stopAnimation();
      m_elaspeTime = 0.0f;
  }
  
  this->m_currentAnimationDefinition = &m_animationDefinitions[animationIndex];

  //Assign values.
  m_isAnimationRunning = true;    
      
  //m_totalLoops = totalLoops;  

  //m_fnpSelectorDelegate = fnpSelectorDelegate;
  if(this->m_currentAnimationDefinition->framesPerSecond != -1)
    m_frameRate = calculateFrameRate(this->m_currentAnimationDefinition->framesPerSecond);
    
  //Initilize values....
  m_needToRunReverseAnimation = this->m_currentAnimationDefinition->needToRunReverseAnimation;
  m_animationMode = true;
  m_currentIndex = 0;
  m_runningLoop = 0;
  m_incrementValue = 0;
  m_needToDeleteItself = this->m_currentAnimationDefinition->needToDeleteItself;

  increaseCurrentIndex();
  this->scheduleUpdateWithPriority(-1);
  resumeAnimation();
}

void BaseSprite::onEnter()
{  
#if IS_DEBUG
  if (!m_debugDraw)
  {
    m_debugDraw = DebugDraw::create(); 
    this->addChild(m_debugDraw, 1000); 
  }
#endif

  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->m_touchPriority, true);
  CCSprite::onEnter();
}

void BaseSprite::onExit()
{
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->removeDelegate(this);
  CCSprite::onExit();
}    

Circle BaseSprite::getVisibleBoundingCircle()
{
  CCSize size = this->getContentSize();  
  CCPoint pos = this->getPosition();  

  Circle circle;

  circle.location = pos;
  circle.radius = ccpDistance(ccp(pos.x - size.width * this->getScale() / 2, pos.y - size.height * this->getScale() / 2), pos); 

  return circle;
}

CCRect BaseSprite::getVisibleBoundingBox()
{
  CCSize size = this->getContentSize();
  
  float posX, posY;
  this->getPosition(&posX, &posY);
   
  float scaledWidth = size.width * this->getScale();
  float scaledHeight = size.height * this->getScale();

  return CCRectMake(posX - scaledWidth / 2, posY - scaledHeight / 2, scaledWidth, scaledHeight);
}
Circle BaseSprite::getBoundingCircle()
{
  CCSize size = this->getContentSize();  
  CCPoint pos = this->getPosition();  

  Circle circle;

  circle.location = pos;
  circle.radius = ccpDistance(ccp(pos.x - size.width / 2, pos.y - size.height / 2), pos); 

  return circle;
}
CCRect BaseSprite::getBoundingBox()
{
  CCSize size = this->getContentSize();
  float posX, posY;
  this->getPosition(&posX, &posY);
  return CCRectMake(posX - size.width / 2, posY - size.height / 2, size.width, size.height);
}

bool BaseSprite::containsTouchLocation(CCTouch* touch)
{
  return getBoundingBox().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool BaseSprite::isTransparent(int x, int y)
{  
  if (m_alphaMap)
  { 
    // TODO (Roman): anchor rotation???
    // the alpha map's dimensions are [ROWS][COLUMNS]
    return !m_alphaMap[y][x];
  }

  // no alpha map, so we are never transparent
  return false;
}

void BaseSprite::refreshAlphaMap(CCSize originalSize, ResolutionPolicy resolutionPolicy)
{
  if (m_alphaMapStillFrameIndex < 0)
    return; // not defined, this means there is no alpha map for this sprite

  // first, undo all the rotation and scales so we can get the original image which will easily be converted to node space
  float rotation = this->getRotation();
  float scale = this->getScale();
  CCPoint position = this->getPosition();
  CCPoint anchor = this->getAnchorPoint();
  
  float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();  
  CCSize resolutionSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize();

  CCDirector::sharedDirector()->setContentScaleFactor(1.0f);
  CCEGLView::sharedOpenGLView()->setDesignResolutionSize(originalSize.width, originalSize.height, kResolutionShowAll);

  this->setAnchorPoint(ccp(0.5f, 0.5f));
  this->setRotation(0);
  this->setScale(1);
  this->setPosition(VisibleRect::center());
 
  this->setDisplayFrameAtIndex(this->m_alphaMapStillFrameIndex);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // after scaling and rotating, visit to see you the image is rendered
  this->visit();
  
  CCRect rect = this->getVisibleBoundingBox();
    
  ccColor4B* buffer = (ccColor4B *)malloc( sizeof(ccColor4B) * rect.size.width * rect.size.height );
  
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);

  glReadPixels(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
 
  ccColor4B color;
  bool **transparencyMap = (bool **)malloc( sizeof(bool) * rect.size.height * rect.size.width);

  int counter = rect.size.width * rect.size.height - 1;
  for (int i = rect.size.height - 1; i >= 0; i--)
  {
    transparencyMap[i] = (bool *)malloc( sizeof(bool) * rect.size.width);
    for (int j = rect.size.width - 1; j >= 0 ; j--)
    {      
      color = buffer[counter--];      
      transparencyMap[i][j] = color.r != 0 || color.g != 0 || color.b != 0;
    }
  }  

#if 0
  this->m_debugDraw->appendLine(ccp(rect.size.width/2, 0), ccp(rect.size.width/2, rect.size.height), 100, 100, 100);
  this->m_debugDraw->appendLine(ccp(0, rect.size.height/2), ccp(rect.size.width, rect.size.height/2), 100, 100, 100);
  this->m_debugDraw->appendRect(ccp(0,0), ccp(rect.size.width, rect.size.height)
      , 255, 255, 0);
#endif

#if 0
  this->m_debugDraw->appendCircle(ccp(anchor.x * rect.size.width, anchor.y * rect.size.height), 2, 255, 120, 120);
  this->m_debugDraw->appendCircle(ccp(anchor.x * rect.size.width, anchor.y * rect.size.height), 10, 120, 120, 120);
#endif

#if 0
  int step = 1;
  CCPoint p = this->getPosition();
  ccColor3B color3b = this->getColor();
  for (int i = 0; i < rect.size.width; i+=step)
  {
    for (int j = 0; j < rect.size.height; j+=step)
    {
      if (transparencyMap[j][i] == true)
      {
        m_debugDraw->appendPoint(ccp(i, j), color3b.r, color3b.g, color3b.b);
      }
      else
      {
        m_debugDraw->appendPoint(ccp(i, j), 200, 200, 200);
      }
    }
  }
#endif

  CC_SAFE_FREE(buffer);

  if (m_alphaMap)
  {
    for (int i = 0; i < m_alphaMapCols; i++)
      free((void *)m_alphaMap[i]);

    free((void *)m_alphaMap);
  }

  // set member variables
  m_alphaMapCols = rect.size.width;
  m_alphaMapRows = rect.size.height;
  m_alphaMap = transparencyMap;
  
  CCDirector::sharedDirector()->setContentScaleFactor(scaleFactor);
  CCEGLView::sharedOpenGLView()->setDesignResolutionSize(resolutionSize.width, resolutionSize.height, resolutionPolicy);
  
  // redo rotation and scale
  this->setAnchorPoint(anchor);
  this->setPosition(position);
  this->setRotation(rotation);
  this->setScale(scale);
}