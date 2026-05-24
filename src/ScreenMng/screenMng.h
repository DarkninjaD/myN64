
#ifndef SCREEN_MNG_H
#define SCREEN_MNG_H

typedef enum {
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
} screen_state_e;

typedef struct{
  int currentScreenState;
  int nextScreenState;
} screen_state_t ;

screen_state_t* screenMngInit();
screen_state_t* screenMngCurrentState();
screen_state_t* screenMngSetNext(screen_state_e nextScreenState);
void screenMngLoadNext();

#endif
