#include <libdragon.h>
#include "mainMenu.h"

// TODO- better names: they are not selected at this point
static rdpq_blitparms_t unselectedButtonParams = {.scale_x = .5, .scale_y = .5};
static rdpq_blitparms_t selectedButtonParams = {.scale_x = .6, .scale_y = .5};

static int screen_width;
static int screen_height;
static sprite_t *btn_game;

typedef struct {
  int overItemIndex;
  int action;
} menu_state_t;

enum MENU_BUTTON {
  START_BUTTON,
  SAVE_BUTTON,
  SETTING_BUTTON,
  EXIT_BUTTON,
  BUTTON_COUNT,
};

enum MENU_ACTION {
  NO_ACTION,
  SELECT,
  BACK,
  UP,
  DOWN,
  ACTION_COUNT
};

static menu_state_t menuState;

void menuHandlerInit() {
  menuState.overItemIndex = START_BUTTON;
  menuState.action = NO_ACTION;
  screen_width = display_get_width();
  screen_height = display_get_height();
  btn_game = sprite_load("rom:/btnGame.sprite");
}


void menuHandleInput() {
  switch (menuState.action)
  {
  case NO_ACTION:
    break;
  case SELECT:
    break;
  case UP:
    if (menuState.overItemIndex > 0) menuState.overItemIndex--;
    break;
  case DOWN:
    if (menuState.overItemIndex < BUTTON_COUNT-1) menuState.overItemIndex++;
    break;
  default:
    break;
  }

}

void menuButton(sprite_t* sprite, float xCord, float yCord, char* message, enum MENU_BUTTON button_t) {

  // set mode
  rdpq_set_mode_standard();

  // Button Back ground
  if(button_t == menuState.overItemIndex) {
    rdpq_sprite_blit(sprite, xCord, yCord, &selectedButtonParams);
  } else {
    rdpq_sprite_blit(sprite, xCord, yCord, &unselectedButtonParams);
  }
  // max is 7 chars
  rdpq_text_print(NULL,3,xCord+5,yCord+13, message);
}

void menuInput(joypad_inputs_t pOne) {
  if(pOne.btn.a || pOne.btn.start) {
    menuState.action = SELECT;
  }
  if(pOne.btn.d_up|| pOne.stick_x > 40) {
    menuState.action = UP;
  }
  if(pOne.btn.d_down || pOne.stick_x < -40) {
    menuState.action = DOWN;
  }
  menuHandleInput();
}

void menuRender() {

    menuButton(btn_game, screen_width /2 - 50, screen_height/2 +10, " Start", START_BUTTON);
    menuButton(btn_game, screen_width /2 - 50, screen_height/2 +30, " Saves", SAVE_BUTTON);
    menuButton(btn_game, screen_width /2 - 50, screen_height/2 +50, " Setting", SETTING_BUTTON);
    menuButton(btn_game, screen_width /2 - 50, screen_height/2 +70, " Exit", EXIT_BUTTON);

}