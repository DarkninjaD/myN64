#include <string.h>
#include <libdragon.h>
#include "Util/consoleMgr.h"
#include "IntroCredits/introCredits.h"
#include "MainMenu/mainMenu.h"
#include "ScreenMng/screenMng.h"

enum {
  FONT_SIXTYFOUR = 1,
  FONT_REVALIA = 2,
  FONT_SQUAREWAVE = 3,
};
/*
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

typedef struct {
  int currentScreenState;
  int nextScreenState;
} screen_state_t;
  
*/
int main(void) {
  
  screen_state_t* test = screenMngInit();

  /*
  -------------------------------------------------
  System init
  -------------------------------------------------
  */
  console_mgr_init();
  intro_title_produced_by();
  // Adds the modal to add controller support
  joypad_init();
  rdpq_init();
  // pull thing from cart
  dfs_init(DFS_DEFAULT_LOCATION);

  /*
  -------------------------------------------------
  Asset load
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
  Intro screen
  -------------------------------------------------
  */

  // check that and n64 type controller is in port 1
  if(joypad_is_connected(JOYPAD_PORT_1) && JOYPAD_STYLE_N64 == joypad_get_style(JOYPAD_PORT_1) ) {
    puts("       Press start to continue ");
    joypad_inputs_t inputs;
    // main loop
    bool intro_scene = true;
    while(intro_scene) {
      joypad_poll();
      inputs = joypad_get_inputs(JOYPAD_PORT_1);
      if(inputs.btn.start) {
        intro_scene = false;
        console_mgr_close();
      }
    }
  }
  else {
    printf("Please add controller to port 1");
  }

  /*
  -------------------------------------------------
  Main Menu screen
  -------------------------------------------------
  */
  display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);

  static sprite_t *spaceship;
  spaceship = sprite_load("rom:/spaceship.sprite");

  //joypad_inputs_t playerOne;
  joypad_buttons_t playerOneBtn;

  menuHandlerInit();


  while(1) {
    surface_t *disp = display_get();
    joypad_poll();
    //playerOne = joypad_get_inputs(JOYPAD_PORT_1);
    playerOneBtn = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    rdpq_attach_clear(disp, NULL);
    menuRender();
    //menuInput(playerOne);
    menuInputTest(playerOneBtn);
    rdpq_detach_show();
  }
  /*
  -------------------------------------------------
  Main Game screen
  -------------------------------------------------
  */
}
