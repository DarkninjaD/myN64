#include "screenMng.h"

static screen_state_t screenState;

screen_state_t* screenMngInit() {
  screenState.currentScreenState = NO_SCREEN;
  screenState.nextScreenState = INIT;
  return &screenState;
};

void screenMngLoad();

void screenMngCurrentState() {

}
