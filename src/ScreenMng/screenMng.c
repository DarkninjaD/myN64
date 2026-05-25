#include "screenMng.h"

static screen_state_t screenState;

screen_state_t* screenMngInit() {
  screenState.currentScreenState = NO_SCREEN;
  screenState.nextScreenState = INIT;
  return &screenState;
};

void screenMngLoadNext() {
  screenState.currentScreenState = screenState.nextScreenState;
  screenState.nextScreenState = NO_SCREEN;
};

screen_state_e* screenMngCurrentState() {
  return &screenState.currentScreenState;
}

screen_state_t* screenMngSetNext(screen_state_e nextScreen) {
  if (screenState.nextScreenState == NO_SCREEN) {
    screenState.nextScreenState = MAIN_MENU;
  }
  return &screenState;
}
