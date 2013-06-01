#include "WildcardPopup.h"

void WildcardPopup::onEnter()
{
  ModalControl::onEnter();

  if (!this->m_isLayoutInitialized)
  {
    CCPoint center = VisibleRect::center();

    m_padding = 4;
    float leftX, rightX;
    float topY, bottomY;

    int replaySequenceReleasingFrames[] = { 21 };
    int replaySequencePressingFrames[] = { 21 };
    ImageButton* replaySequence = ImageButton::create(
      this
      , callfuncO_selector(WildcardPopup::replaySequenceCallback)
      , NULL
      , m_gameContext
      , this->m_gameContext->getImageMapPListPath()
      , this->m_gameContext->getImageMapPngPath()
      , -1
      , 21
      , replaySequencePressingFrames, 1
      , replaySequenceReleasingFrames, 1
      , 21
      , 21
      , TOUCH_PRIORITY_MODAL_ITEM);
    CCSize size = replaySequence->getSpriteFrameSize(21);

    leftX = center.x - size.width - m_padding;
    replaySequence->setPosition(ccp(leftX, center.y));
    leftX = leftX - size.width/2 - m_padding;

    topY = center.y + size.height/2;
    bottomY = center.y - size.height/2;

    int nextButtonHelpReleasingFrames[] = { 22 };
    int nextButtonHelpPressingFrames[] = { 22 };
    ImageButton* nextButtonHelp = ImageButton::create(
      this
      , callfuncO_selector(WildcardPopup::showNextSequenceItemCallback)
      , NULL
      , m_gameContext
      , this->m_gameContext->getImageMapPListPath()
      , this->m_gameContext->getImageMapPngPath()
      , -1
      , 22
      , nextButtonHelpPressingFrames, 1
      , nextButtonHelpReleasingFrames, 1
      , 22
      , 22
      , TOUCH_PRIORITY_MODAL_ITEM);
    nextButtonHelp->setPosition(ccp(center.x, center.y));
    
    int replayFromCurrentReleasingFrames[] = { 23 };
    int replayFromCurrentPressingFrames[] = { 23 };
    ImageButton* replayFromCurrent = ImageButton::create(
      this
      , callfuncO_selector(WildcardPopup::replayFromCurrentCallback)
      , NULL
      , m_gameContext
      , this->m_gameContext->getImageMapPListPath()
      , this->m_gameContext->getImageMapPngPath()
      , -1
      , 23
      , replayFromCurrentPressingFrames, 1
      , replayFromCurrentReleasingFrames, 1
      , 23
      , 23
      , TOUCH_PRIORITY_MODAL_ITEM);
        
    size = replaySequence->getSpriteFrameSize(23);
    rightX = center.x + size.width + m_padding;
    replayFromCurrent->setPosition(ccp(rightX, center.y));
    rightX = rightX + size.width/2 + m_padding;
    
    CCLabelBMFont* coinsTextLabel = CCLabelBMFont::create("Coins:", m_gameContext->getFontNormalPath().c_str());
    CCSize fontSize = coinsTextLabel->getContentSize();

    coinsTextLabel->setPosition(ccp(leftX + m_padding + fontSize.width/2, topY + fontSize.height/2 + m_padding));
    this->addChild(coinsTextLabel);
            
    char str[10];
    sprintf(str, "%i", m_gameContext->getTotalCoins());

    m_coinsLabel = CCLabelBMFont::create(str, m_gameContext->getFontNormalPath().c_str());
    fontSize = m_coinsLabel->getContentSize();
    m_coinsLabel->setPosition(ccp(rightX - m_padding - fontSize.width/2, coinsTextLabel->getPositionY()));
    this->addChild(m_coinsLabel);
    
    leftX -= m_padding;
    rightX += m_padding;
    topY = coinsTextLabel->getPositionY() + fontSize.height/2 + m_padding*2;
    bottomY = bottomY - m_padding*2;

    m_dialogRectLeftBottom.setPoint(leftX, bottomY);
    m_dialogRectRightTop.setPoint(rightX, topY);

    m_visibleRectLeftBottom = VisibleRect::leftBottom();
    m_visibleRectRightTop = VisibleRect::rightTop();

    m_backgroundColor.a = .7;
    m_backgroundColor.r = 0;
    m_backgroundColor.g = 0;
    m_backgroundColor.b = 0;
    
    m_dialogColor.a = 1;
    m_dialogColor.r = 0;
    m_dialogColor.g = 0;
    m_dialogColor.b = 0;
  }
}

void WildcardPopup::refresh()
{
  char str[10];
  sprintf(str, "%i", m_gameContext->getTotalCoins());
  m_coinsLabel->setString(str);  
  m_coinsLabel->setPositionX(m_dialogRectRightTop.x - m_padding*2 - m_coinsLabel->getContentSize().width/2);
}

void WildcardPopup::draw()
{  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  ccDrawSolidRect(m_visibleRectLeftBottom, m_visibleRectRightTop, m_backgroundColor);
  ccDrawSolidRect(m_dialogRectLeftBottom, m_dialogRectRightTop, m_dialogColor);
  
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

void WildcardPopup::replaySequenceCallback(CCObject* pSender)
{
  int totalCoins = this->m_gameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_REPLAY_SEQUENCE)
  {
    totalCoins -= COINS_COST_REPLAY_SEQUENCE;
    this->m_gameContext->setTotalCoins(totalCoins);

    char str[10];
    sprintf(str, "%i", totalCoins);
    m_coinsLabel->setString(str);

    // callback
    if(m_pTarget != 0 && this->m_fnpReplaySequenceCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpReplaySequenceCallbackDelegate)(this);
  }
}
void WildcardPopup::showNextSequenceItemCallback(CCObject* pSender)
{
  int totalCoins = this->m_gameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_SHOW_NEXT_ITEM)
  {
    totalCoins -= COINS_COST_SHOW_NEXT_ITEM;
    this->m_gameContext->setTotalCoins(totalCoins);
    
    char str[10];
    sprintf(str, "%i", totalCoins);
    m_coinsLabel->setString(str);

    // callback
    if(m_pTarget != 0 && this->m_fnpShowNextSequenceItemCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpShowNextSequenceItemCallbackDelegate)(this);
  }
}
void WildcardPopup::replayFromCurrentCallback(CCObject* pSender)
{
  int totalCoins = this->m_gameContext->getTotalCoins();
  if (totalCoins >= COINS_COST_SAVE_TRY)
  {
    totalCoins -= COINS_COST_SAVE_TRY;
    this->m_gameContext->setTotalCoins(totalCoins);
    
    char str[10];
    sprintf(str, "%i", totalCoins);
    m_coinsLabel->setString(str);

    // callback
    if(m_pTarget != 0 && this->m_fnpSaveTryCallbackDelegate != 0)
        (m_pTarget->*this->m_fnpSaveTryCallbackDelegate)(this);
  }
}

void WildcardPopup::closeCallback(CCObject* pSender)
{
  // callback
  if(m_pTarget != 0 && this->m_fnpCloseCallbackDelegate != 0)
      (m_pTarget->*this->m_fnpCloseCallbackDelegate)(this);
}