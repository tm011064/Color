#ifndef __CHALLENGEBUTTON_H__
#define __CHALLENGEBUTTON_H__

#include "cocos2d.h"
#include "BaseSprite.h"
#include "GameConstants.h"
#include "Types.h"
#include "GameContext.h"
#include "ImageButton.h" 

using namespace cocos2d;

class ChallengeButton : public cocos2d::CCNode
{
private:
  
  CCSize m_size;
  CCNode* m_pTarget;
  bool m_isLayoutInitialized;
  
  GameContext* m_pGameContext; 
  SEL_CallFuncO m_fnpClickDelegate;
  ImageButton* m_imageButton;

  int m_challengeIndex;
  int m_totalStars;
  ChallengeSceneType m_challengeSceneType;

  void onClick(CCObject* pSender);

public:  
  static ChallengeButton* create(int challengeIndex, ChallengeSceneType challengeSceneType, int totalStars, GameContext* gameContext, SEL_CallFuncO fnpClickDelegate, CCNode *pTarget);
  ~ChallengeButton() { }
  
  CCSize getSize() { return m_size; }
  virtual void onEnter();
  virtual void setVisible(bool var);

protected:  
 ChallengeButton(int challengeIndex, ChallengeSceneType challengeSceneType, int totalStars, GameContext* gameContext, SEL_CallFuncO fnpClickDelegate, CCNode *pTarget)
  : m_pGameContext(gameContext)
  , m_fnpClickDelegate(fnpClickDelegate)
  , m_pTarget(pTarget)
  , m_isLayoutInitialized(false)
  , m_totalStars(totalStars)
  , m_challengeSceneType(challengeSceneType)
  , m_imageButton(NULL)
  , m_challengeIndex(challengeIndex)
 {

 }
};

#endif  // __CHALLENGEBUTTON_H__