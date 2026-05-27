#include <libdragon.h>
#include "mainMenu.h"
#include <t3d/t3d.h>
#include "../Util/fontAssets.h"

// TODO- better names: they are not selected at this point
static rdpq_blitparms_t unselectedButtonParams = {.scale_x = .5, .scale_y = .5};
static rdpq_blitparms_t selectedButtonParams = {.scale_x = .6, .scale_y = .5};

static int screen_width;
static int screen_height;
static sprite_t *btn_game;


typedef enum MenuActions {
  NO_ACTION,
  SELECT,
  BACK,
  UP,
  DOWN,
  ACTION_COUNT
} menu_action_e;

typedef struct {
  menu_button_e overItemIndex;
  menu_action_e action;
} menu_state_t;

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
    // no action needs to be done as it's handled higher up
    break;
  case UP:
    if (menuState.overItemIndex > 0) menuState.overItemIndex--;
    menuState.action = NO_ACTION;
    break;
  case DOWN:
    if (menuState.overItemIndex < BUTTON_COUNT-1) menuState.overItemIndex++;
    menuState.action = NO_ACTION;
    break;
  case BACK:
    // do a back
    break;
  default:
    break;
  }

}

void menuButtonFactory(sprite_t* sprite, float xCord, float yCord, char* message, menu_button_e button_e) {

  // set mode
  rdpq_set_mode_standard();

  // Button Background
  if(button_e == menuState.overItemIndex) {
    rdpq_sprite_blit(sprite, xCord, yCord, &selectedButtonParams);
  } else {
    rdpq_sprite_blit(sprite, xCord, yCord, &unselectedButtonParams);
  }
  // max is 7 chars
  rdpq_text_print(NULL,3,xCord+5,yCord+13, message);
}

void menuInput(joypad_buttons_t pOne) {
  if(pOne.a || pOne.start) {
    menuState.action = SELECT;
    fprintf(stderr, "it was select\n");
  }
  if(pOne.d_up) {
    menuState.action = UP;
  }
  if(pOne.d_down) {
    menuState.action = DOWN;
  }
  menuHandleInput();
}

void cleanUp() {}

menu_button_e menuRender() {

  display_init(RESOLUTION_640x480, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_DISABLED);

  // Font
  rdpq_font_t *fnt0 = rdpq_font_load("rom:/sixtyfour.font64");
  rdpq_font_t *fnt1 = rdpq_font_load("rom:/revalia.font64");
  rdpq_font_t *fnt2 = rdpq_font_load("rom:/squarewave.font64");

  rdpq_text_register_font(FONT_SIXTYFOUR, fnt0);
  rdpq_text_register_font(FONT_REVALIA, fnt1);
  rdpq_text_register_font(FONT_SQUAREWAVE, fnt2);

  rdpq_font_style(fnt0, 0 , &(rdpq_fontstyle_t) {
    .color = RGBA32(0x82, 0x30, 0x38, 0xFF),
    .outline_color = RGBA32 (255,255,255,255),
  });

  rdpq_font_style(fnt1, 0 , &(rdpq_fontstyle_t) {
    .color = RGBA32(0x82, 0x30, 0x38, 0xFF),
    .outline_color = RGBA32 (255,255,255,255),
  });

  rdpq_font_style(fnt2, 0 , &(rdpq_fontstyle_t) {
    .color = RGBA32(0x82, 0x30, 0x38, 0xFF),
    .outline_color = RGBA32 (255,255,255,255),
  });

    menuHandlerInit();

    while(menuState.action != SELECT) {
      joypad_poll();
      joypad_buttons_t playerOneBtn = joypad_get_buttons_pressed(JOYPAD_PORT_1);

      surface_t *disp = display_get();
      rdpq_attach_clear(disp, NULL);

      menuInput(playerOneBtn);

      menuButtonFactory(btn_game, screen_width /2 - 50, screen_height/2 +10, " Start", START_BUTTON);
      menuButtonFactory(btn_game, screen_width /2 - 50, screen_height/2 +30, " Saves", SAVE_BUTTON);
      menuButtonFactory(btn_game, screen_width /2 - 50, screen_height/2 +50, " Setting", SETTING_BUTTON);
      menuButtonFactory(btn_game, screen_width /2 - 50, screen_height/2 +70, " Exit", EXIT_BUTTON);

      rdpq_detach_show();
    }
    rspq_wait();
    cleanUp();
    display_close();
    return menuState.overItemIndex;
}
