
#ifndef SCREEN_MNG_H
#define SCREEN_MNG_H

/**
 *  @brief Screen Type enum that declares the diffent screens in the State Machine.
 *
 */
typedef enum ScreenType {
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

/**
 *  @brief the struct of Screen Manger State Machine.
 *
 */
typedef struct ScreenState {
  int currentScreenState;
  int nextScreenState;
} screen_state_t ;

/**
 *  @brief Sets initial for Screen Mangers State Machine.
 *
 *  @return screen_state_t*
 */
screen_state_t* screenMngInit();

/**
 *  @brief returns the current state of the Screen Manger State Machine.
 *
 *  @return screen_state_e*
 */
screen_state_e* screenMngCurrentState();

/**
 *  @brief call the Screen Mangers State Machine and set the next state only if NO_SCREEN is set for next.
 *
 *  @return screen_state_t*
 */
screen_state_t* screenMngSetNext(screen_state_e nextScreenState);

/**
 *  @brief calls the Screen Manger State Machine to load the next screen and set's
 * next screen to NO_SCREEN. allowing for ScreenMngSetNext() to set next screen.
 *
 */
void screenMngLoadNext();

#endif
