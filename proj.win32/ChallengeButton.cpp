#include "ChallengeButton.h"
#include "NavigationManager.h"
#include "VisibleRect.h"
#include "Types.h"
#include "UtilityHelper.h"

 ChallengeButton* ChallengeButton::create(int challengeIndex, ChallengeSceneType challengeSceneType, int totalStars, GameContext* gameContext, SEL_CallFuncO fnpClickDelegate, CCNode *pTarget)
 {
   ChallengeButton* challengeButton = new ChallengeButton(challengeIndex, challengeSceneType, totalStars
     , gameContext, fnpClickDelegate, pTarget);
   challengeButton->autorelease();
   return challengeButton;
 }

void ChallengeButton::onEnter()
{  
  CCNode::onEnter();
  
  if (!this->m_isLayoutInitialized)
  {  
    this->m_isLayoutInitialized = true;
    
    CCSprite* sprite;
    if (m_totalStars < 0)
    {
      sprite = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("challengeButton_L"));
      this->addChild(sprite);

      m_size = sprite->getContentSize();
    }
    else
    {      
      int releasingFrames[] = { 0 };
      int pressingFrames[] = { 0 };
    
      std::string challengeButtonIconName;
      switch (m_challengeSceneType)
      {
      case REACH_LEVEL: challengeButtonIconName = "challengeButton_memory"; break;
      case REPEAT_ONE_OFF: challengeButtonIconName = "challengeButton_speed"; break;
      case EXACT_LENGTH: challengeButtonIconName = "challengeButton_balance"; break;
      case RHYTHM: challengeButtonIconName = "challengeButton_rhythm"; break;
      }

      // TODO (Roman): text on index...

      m_imageButton = ImageButton::create(this
        , callfuncO_selector(ChallengeButton::onClick)
        , NULL
        , m_pGameContext
        , challengeButtonIconName
        , -1
        , 0
        , pressingFrames, 1
        , releasingFrames, 1
        , 0
        , 0
        , TOUCH_PRIORITY_NORMAL);
      this->addChild(m_imageButton);
      m_size = m_imageButton->getContentSize();

      CCLabelBMFont* label = CCLabelBMFont::create(UtilityHelper::convertToString(m_challengeIndex + 1).c_str()
        , m_pGameContext->getFontNormalPath().c_str());
      label->setPosition(ccp(m_size.width/2 - m_size.width*.22 - label->getContentSize().width/2
        , m_size.height/2 - m_size.height*.16 - label->getContentSize().height/2));
      this->addChild(label);

      switch ( m_totalStars )
      {
      case 1:
        sprite = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("star_golden_small"));
        sprite->setPosition(ccp(0, -m_size.height*.17));
        this->addChild(sprite);
        break;
      case 2:
        sprite = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("star_golden_small"));
        sprite->setPosition(ccp(-sprite->getContentSize().width*.4, -m_size.height*.158));
        sprite->setRotation(-8.0f);
        this->addChild(sprite);
        sprite = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("star_golden_small"));
        sprite->setPosition(ccp(sprite->getContentSize().width*.4, -m_size.height*.17));
        sprite->setRotation(6.4f);
        this->addChild(sprite);
        break;
      case 3:
        sprite = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("star_golden_small"));
        sprite->setPosition(ccp(-sprite->getContentSize().width*.8, -m_size.height*.17 - sprite->getContentSize().height*.12));
        sprite->setRotation(-22.0f);
        this->addChild(sprite);
        sprite = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("star_golden_small"));
        sprite->setPosition(ccp(0, -m_size.height*.17));
        this->addChild(sprite);
        sprite = CCSprite::createWithSpriteFrame(m_pGameContext->getImageMap()->getTile("star_golden_small"));
        sprite->setPosition(ccp(sprite->getContentSize().width*.8, -m_size.height*.17 - sprite->getContentSize().height*.174));
        sprite->setRotation(18.4f);
        this->addChild(sprite);
        break;
      }
    }

  }
}
void ChallengeButton::onClick(CCObject* pSender)
{
  if (m_pTarget && m_fnpClickDelegate)
    (m_pTarget->*m_fnpClickDelegate)(this);
}
void ChallengeButton::setVisible(bool var)
{
  CCNode::setVisible(var);
  if (m_imageButton != NULL)
  {
    m_imageButton->setVisible(var);
  }
}