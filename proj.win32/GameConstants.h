#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

#include "cocos2d.h"
#include "Types.h"

static const float BLINK_SPEED_NORMAL = .55f;
static const float BLINK_SPEED_STEP = .0195f;
static const float BLINK_SPEED_THRESHOLD = .25f;

static const float CORRECT_BUTTON_SCORE_TWO_BUTTONS = 300.0f;
static const float CORRECT_BUTTON_SCORE_TWO_BUTTONS_MAX_TIME_BONUS = 70.0f;
static const float TWO_BUTTON_CLICK_TIME_THRESHOLD = 2.0f;
static const float CORRECT_BUTTON_SCORE_TWO_BUTTONS_LEVEL_BONUS = 700.0f;
static const float CORRECT_BUTTON_SCORE_TWO_BUTTONS_MAX_LEVEL_TIME_BONUS = 700.0f;
static const float COINS_EARNED_TWO_BUTTONS_MULTIPLIER = .15f;

static const float CORRECT_BUTTON_SCORE_THREE_BUTTONS = 500.0f;
static const float CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_TIME_BONUS = 100.0f;
static const float THREE_BUTTON_CLICK_TIME_THRESHOLD = 2.0f;
static const float CORRECT_BUTTON_SCORE_THREE_BUTTONS_LEVEL_BONUS = 1000.0f;
static const float CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_LEVEL_TIME_BONUS = 1000.0f;
static const float COINS_EARNED_THREE_BUTTONS_MULTIPLIER = .3f;

static const float CORRECT_BUTTON_SCORE_FOUR_BUTTONS = 700.0f;
static const float CORRECT_BUTTON_SCORE_FOUR_BUTTONS_MAX_TIME_BONUS = 130.0f;
static const float FOUR_BUTTON_CLICK_TIME_THRESHOLD = 2.0f;
static const float CORRECT_BUTTON_SCORE_FOUR_BUTTONS_LEVEL_BONUS = 1300.0f;
static const float CORRECT_BUTTON_SCORE_FOUR_BUTTONS_MAX_LEVEL_TIME_BONUS = 1300.0f;
static const float COINS_EARNED_FOUR_BUTTONS_MULTIPLIER = .5f;

static const cocos2d::ccColor4B BACKGROUND_COLOR={.0f,.0f,.0f,1.0f};

static const cocos2d::ccColor3B BUTTON_COLOR_BLACK = {50.0f, 50.0f, 50.0f};
static const cocos2d::ccColor3B BUTTON_COLOR_YELLOW = {255.0f, 255.0f, 0.0f};
static const cocos2d::ccColor3B BUTTON_COLOR_BLUE   = {0.0f, 80.0f, 255.0f};
static const cocos2d::ccColor3B BUTTON_COLOR_RED    = {255.0f, 50.0f, 0.0f};
static const cocos2d::ccColor3B BUTTON_COLOR_GREEN  = {0.0f, 255.0f, 50.0f};
static const cocos2d::ccColor3B BUTTON_COLOR_PURPLE  = {255.0f, 0.0f, 255.0f};

static const cocos2d::ccColor4F WILDCARD_BUTTON_BORDER_COLOR_ON  = {1.0f, 1.0f, 1.0f, 1.0f};
static const cocos2d::ccColor4F WILDCARD_BUTTON_BORDER_COLOR_OFF  = {1.0f, 1.0f, 1.0f, 1.0f};
static const cocos2d::ccColor4F WILDCARD_BUTTON_BACKGROUND_COLOR_ON  = {.1f, .1f, .1f, 1.0f};
static const cocos2d::ccColor4F WILDCARD_BUTTON_BACKGROUND_COLOR_OFF  = {0.0f, 0.0f, 0.0f, 1.0f};
static const cocos2d::ccColor4F WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_ON  = {.1f, .1f, .1f, 1.0f};
static const cocos2d::ccColor4F WILDCARD_BUTTON_COIN_BACKGROUND_COLOR_OFF  = {.133f, .133f, .133f, 1.0f};

static const cocos2d::ccColor3B TEXT_BUTTON_BORDER_COLOR_ON  = {255.0f, 255.0f, 255.0f};
static const cocos2d::ccColor3B TEXT_BUTTON_BORDER_COLOR_OFF = {255.0f, 255.0f, 255.0f};
static const cocos2d::ccColor4F TEXT_BUTTON_BACKGROUND_COLOR_ON = {.1f, .1f, .1f, 1.0f};
static const cocos2d::ccColor4F TEXT_BUTTON_BACKGROUND_COLOR_OFF  = {0.0f, 0.0f, 0.0f, 1.0f};
static const cocos2d::ccColor3B TEXT_BUTTON_CONTENT_COLOR_ON  = {255.0f, 255.0f, 255.0f};
static const cocos2d::ccColor3B TEXT_BUTTON_CONTENT_COLOR_OFF = {255.0f, 255.0f, 255.0f};

static ResourceDefinition SIZE_240x320    =  { cocos2d::CCSizeMake(240, 320),   "s240x320"   };
static ResourceDefinition SIZE_360x480    =  { cocos2d::CCSizeMake(360, 480),   "s360x480"   };
static ResourceDefinition SIZE_720x960    =  { cocos2d::CCSizeMake(720, 960),   "s720x960"   };
static ResourceDefinition SIZE_960x1280   =  { cocos2d::CCSizeMake(960, 1280),  "s960x1280"   };
static ResourceDefinition SIZE_1536x2048  =  { cocos2d::CCSizeMake(1536, 2048), "s1536x2048"   };

static const char* FONT_MENU_LARGE = "RussoOneLarge.fnt";
static const char* FONT_MENU_NORMAL = "RussoOneNormal.fnt";
/*
static const char* FONT_MENU_LARGE = "SquareFontLarge.fnt";
static const char* FONT_MENU_NORMAL = "SquareFont.fnt";
*/
static const int FONT_SPACE_WIDTH = 8;

static const float BUTTON_QUARTER_SCALE = .98f;
static const float BUTTON_THIRD_SCALE = .92f;
static const float BUTTON_FIFTH_SCALE = .93f;

static inline float floor_float(float f)
{
	int i = (int)f;
	return (float)((f < 0.0f && f != i) ? i - 1 : i);
}

#define ccpRounded(__X__,__Y__) cocos2d::CCPointMake( floor_float( (float)(__X__) + .5f), floor_float((float)(__Y__) + .5f))
#define round(__X__) floor_float( (float)(__X__) + .5f)

#define GAME_VERSION 1
#define IS_DEBUG 1

#define TOUCH_PRIORITY_MODAL_PANEL   -2147483646 
#define TOUCH_PRIORITY_MODAL_ITEM    -2147483647
#define TOUCH_PRIORITY_NORMAL         0
#define MODAL_ZORDER                  2147483647

// TODO (Roman): proper values
#define COINS_COST_REPLAY_SEQUENCE    50
#define COINS_COST_SHOW_NEXT_ITEM     100
#define COINS_COST_SHOW_REMAINING     200

#define STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE       3
#define STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE    3
#define STORYMODE_TOTAL_PAGES                         3

#endif  // __GAME_CONSTANTS_H__