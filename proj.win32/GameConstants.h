#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

#include "cocos2d.h"
#include "Types.h"

static const float BLINK_SPEED_NORMAL = .55f;
static const float BLINK_SPEED_STEP = .0125f;
static const float BLINK_SPEED_THRESHOLD = .25f;

static const float CORRECT_BUTTON_SCORE_THREE_BUTTONS = 300.0f;
static const float CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_TIME_BONUS = 70.0f;
static const float THREE_BUTTON_CLICK_TIME_THRESHOLD = 2.0f;
static const float CORRECT_BUTTON_SCORE_THREE_BUTTONS_LEVEL_BONUS = 700.0f;
static const float CORRECT_BUTTON_SCORE_THREE_BUTTONS_MAX_LEVEL_TIME_BONUS = 700.0f;

static const float CORRECT_BUTTON_SCORE_FOUR_BUTTONS = 500.0f;
static const float CORRECT_BUTTON_SCORE_FOUR_BUTTONS_MAX_TIME_BONUS = 100.0f;
static const float FOUR_BUTTON_CLICK_TIME_THRESHOLD = 2.0f;
static const float CORRECT_BUTTON_SCORE_FOUR_BUTTONS_LEVEL_BONUS = 1000.0f;
static const float CORRECT_BUTTON_SCORE_FOUR_BUTTONS_MAX_LEVEL_TIME_BONUS = 1000.0f;

static const float CORRECT_BUTTON_SCORE_FIVE_BUTTONS = 700.0f;
static const float CORRECT_BUTTON_SCORE_FIVE_BUTTONS_MAX_TIME_BONUS = 130.0f;
static const float FIVE_BUTTON_CLICK_TIME_THRESHOLD = 2.0f;
static const float CORRECT_BUTTON_SCORE_FIVE_BUTTONS_LEVEL_BONUS = 1300.0f;
static const float CORRECT_BUTTON_SCORE_FIVE_BUTTONS_MAX_LEVEL_TIME_BONUS = 1300.0f;

static const cocos2d::ccColor4B BACKGROUND_COLOR={0,0,0,1};

static const cocos2d::ccColor3B BUTTON_COLOR_YELLOW = {255, 255, 0};
static const cocos2d::ccColor3B BUTTON_COLOR_BLUE   = {0  , 80 , 255};
static const cocos2d::ccColor3B BUTTON_COLOR_RED    = {255, 0  , 0};
static const cocos2d::ccColor3B BUTTON_COLOR_GREEN  = {0  , 255, 0};
static const cocos2d::ccColor3B BUTTON_COLOR_PURPLE  = {255, 0, 255};

static const cocos2d::ccColor3B TEXT_BUTTON_BORDER_COLOR_ON  = {255, 255, 255};
static const cocos2d::ccColor3B TEXT_BUTTON_BORDER_COLOR_OFF = {255, 255, 255};
static const cocos2d::ccColor4F TEXT_BUTTON_BACKGROUND_COLOR_ON = {.1, .1, .1, 1};
static const cocos2d::ccColor4F TEXT_BUTTON_BACKGROUND_COLOR_OFF  = {0, 0, 0, 1};
static const cocos2d::ccColor3B TEXT_BUTTON_CONTENT_COLOR_ON  = {255, 255, 255};
static const cocos2d::ccColor3B TEXT_BUTTON_CONTENT_COLOR_OFF = {255, 255, 255};

static ResourceDefinition SIZE_240x320    =  { cocos2d::CCSizeMake(240, 320),   "s240x320"   };
static ResourceDefinition SIZE_360x480    =  { cocos2d::CCSizeMake(360, 480),   "s360x480"   };
static ResourceDefinition SIZE_720x960    =  { cocos2d::CCSizeMake(720, 960),   "s720x960"   };
static ResourceDefinition SIZE_960x1280   =  { cocos2d::CCSizeMake(960, 1280),  "s960x1280"   };
static ResourceDefinition SIZE_1536x2048  =  { cocos2d::CCSizeMake(1536, 2048), "s1536x2048"   };

static const char* FONT_MENU_LARGE = "MyriadProLarge.fnt";
static const char* FONT_MENU_NORMAL = "MyriadProNormal.fnt";
static const int FONT_SPACE_WIDTH = 8;

static const float BUTTON_QUARTER_SCALE = .98f;
static const float BUTTON_THIRD_SCALE = .92f;
static const float BUTTON_FIFTH_SCALE = .93f;


//#define ROUND_POINT(point) point.setPoint(std::floorf(point.x + .5), std::floorf(point.y + .5))
#define ccpRounded(__X__,__Y__) cocos2d::CCPointMake( std::floorf( (float)(__X__) + .5f), std::floorf((float)(__Y__) + .5f))
#define round(__X__) std::floorf( (float)(__X__) + .5f)

#define GAME_VERSION 1
#define IS_DEBUG 1

#define TOUCH_PRIORITY_MODAL_PANEL   -2147483646 
#define TOUCH_PRIORITY_MODAL_ITEM    -2147483647
#define TOUCH_PRIORITY_NORMAL         0
#define MODAL_ZORDER                  2147483647

// TODO (Roman): proper values
#define COINS_COST_REPLAY_SEQUENCE    1
#define COINS_COST_SAVE_TRY           1
#define COINS_COST_SHOW_NEXT_ITEM     1

#define STORYMODE_TOTAL_CHALLENGE_ROWS_PER_PAGE       3
#define STORYMODE_TOTAL_CHALLENGE_COLUMNS_PER_PAGE    3
#define STORYMODE_TOTAL_PAGES                         3

#endif  // __GAME_CONSTANTS_H__