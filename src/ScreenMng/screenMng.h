
#ifndef SCREEN_MNG_H
#define SCREEN_MNG_H
#include <libdragon.h>

enum SCREEN_STATE {
  NO_SCREEN,
  INIT,
  INTRO,
  MAIN_MENU,
  GAME_INIT,
  GAME_PLAY,
  GAME_CUTSCEEN,
  GAME_PAUSED,
  GAME_END,
  SCORE_SCREEN,
  DEBUG,
  SCREEN_STATE_COUNT
};

typedef struct{
  int currentScreenState;
  int nextScreenState;
} screen_state_t ;

screen_state_t* screenMngInit();
void screenMngLoad();

#endif
