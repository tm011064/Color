#ifndef __GAMESCOREPOINTSPANEL_H__
#define __GAMESCOREPOINTSPANEL_H__

#include "GameEngineIncludes.h"

using namespace cocos2d;

class GameScorePointsPanel : public BaseNode
{  
private:

  GameContext* m_pGameContext; 
  bool m_isLayoutInitialized;
  float m_padding;
  float m_borderThickness;

  CCLabelBMFont* m_pointsLabel;
  CCLabelBMFont* m_pointsLabelDescription;
  CCLabelBMFont* m_levelBonusLabel;
  CCLabelBMFont* m_levelBonusLabelDescription;
  CCLabelBMFont* m_timeBonusLabel;
  CCLabelBMFont* m_timeBonusLabelDescription;

  CCLabelBMFont* m_totalPointsLabel;
  CCLabelBMFont* m_coinsEarnedLabel;
  
  float m_elaspeTimePoints;
  float m_elaspeTimeCoins;
  float m_targetTime;

  CCPoint m_separatorLineLeftBottom;
  CCPoint m_separatorLineRightTop;
  ccColor4F m_separatorColor;

  float m_textIndentLeft;
  float m_textIndentRight;

  void updatePointsDisplay(float dt);
  void updateCoinsDisplay(float dt);

public:
  static GameScorePointsPanel* create(GameContext* gameContext, float width, ccColor4F separatorColor);
  ~GameScorePointsPanel() { }
  
  void refresh();
  void show();
  virtual void onEnter();
  virtual void draw();

protected:
  GameScorePointsPanel(GameContext* gameContext, float width, ccColor4F separatorColor)
    : m_pGameContext(gameContext)
    , m_pointsLabel(NULL)
    , m_pointsLabelDescription(NULL)
    , m_levelBonusLabel(NULL)
    , m_levelBonusLabelDescription(NULL)
    , m_timeBonusLabel(NULL)
    , m_timeBonusLabelDescription(NULL)
    , m_totalPointsLabel(NULL)
    , m_coinsEarnedLabel(NULL)
    , m_isLayoutInitialized(false)
    , m_textIndentLeft(-width/2.0f)
    , m_textIndentRight(width/2.0f)
    , m_separatorColor(separatorColor)
  { 
    
  }

};
#endif  // __GAMESCOREPOINTSPANEL_H__