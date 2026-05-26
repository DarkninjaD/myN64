#include <string.h>
#include <libdragon.h>
#include <debug.h>
#include "Util/consoleMgr.h"
#include "IntroCredits/introScreen.h"
#include "MainMenu/mainMenu.h"
#include "ScreenMng/screenMng.h"
#include "Util/fontAssets.h"
#include "Logo/logo.h"

int main(void) {

  screen_state_t* screen_state = screenMngInit();
  // Adds the modal to add controller support
  asset_init_compression(2);
  asset_init_compression(3);
  wav64_init_compression(3);
  joypad_init();
  rdpq_init();
  timer_init();
  audio_init(32000, 3);
  mixer_init(32);
  // pull thing from cart
  dfs_init(DFS_DEFAULT_LOCATION);

  /*
  -------------------------------------------------
  Asset load //TODO - This should be pulled into it's own file.
  -------------------------------------------------
  */
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


  /*
  -------------------------------------------------
  Main Menu screen //TODO - maybe a bit of clean up bellow before the while loop.
  -------------------------------------------------
  */
  //display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);

  //static sprite_t *spaceship;
  //spaceship = sprite_load("rom:/spaceship.sprite");

  //joypad_inputs_t playerOne;
  joypad_buttons_t playerOneBtn;

  //menuHandlerInit();

  // TODO - some comments would be nice.

  while(1) {
    //surface_t *disp = display_get();
    //joypad_poll();
    //playerOne = joypad_get_inputs(JOYPAD_PORT_1);
    //playerOneBtn = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    //rdpq_attach_clear(disp, NULL);

    switch(screen_state->currentScreenState) {
      case NO_SCREEN:
        screenMngLoadNext();
        break;
      case INIT:
        //introScreen();
        n64brew_logo();
        libdragon_logo();
        //screenMngSetNext(MAIN_MENU);
        break;
      case MAIN_MENU:
        menuRender();
        menuInputTest(playerOneBtn);
        break;
      case GAME_PLAY:
        // Draw gameplay loop here
        rdpq_text_print(NULL, FONT_SQUAREWAVE, 20, 20, "GAMEPLAY LOADED");
        break;
    }
    //rdpq_detach_show();
  }
}
