#ifndef __GAMESCORETIMEPANEL_H__
#define __GAMESCORETIMEPANEL_H__

#include "GameEngineIncludes.h"

using namespace cocos2d;

class GameScoreTimePanel : public BaseNode
{  
private:

  GameContext* m_pGameContext; 
  bool m_isLayoutInitialized;
  bool m_showAverageDuration;
  float m_padding;
  float m_borderThickness;

  CCLabelBMFont* m_pointsLabel;
  CCLabelBMFont* m_pointsLabelDescription;
  CCLabelBMFont* m_timingLabel;
  CCLabelBMFont* m_timingLabelDescription;
  CCLabelBMFont* m_durationLabel;
  CCLabelBMFont* m_durationLabelDescription;
  CCLabelBMFont* m_scoreLabel;
  CCLabelBMFont* m_scoreLabelDescription;

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
  static GameScoreTimePanel* create(GameContext* gameContext, float width, bool showAverageDuration
    , ccColor4F separatorColor);
  ~GameScoreTimePanel() { }
  
  void refresh();
  void show();
  virtual void onEnter();
  virtual void draw();

protected:
  GameScoreTimePanel(GameContext* gameContext, float width, bool showAverageDuration, ccColor4F separatorColor)
    : m_pGameContext(gameContext)
    , m_pointsLabel(NULL)
    , m_pointsLabelDescription(NULL)
    , m_coinsEarnedLabel(NULL)
    , m_isLayoutInitialized(false)
    , m_textIndentLeft(-width/2.0f)
    , m_textIndentRight(width/2.0f)
    , m_separatorColor(separatorColor)
    , m_timingLabel(NULL)
    , m_timingLabelDescription(NULL)
    , m_durationLabel(NULL)
    , m_durationLabelDescription(NULL)
    , m_scoreLabel(NULL)
    , m_scoreLabelDescription(NULL)
    , m_showAverageDuration(showAverageDuration)
  { 
    
  }

};
#endif  // __GAMESCORETIMEPANEL_H__