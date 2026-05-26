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
  Asset load //TODO - the asset are loaded in and out per screen.
  -------------------------------------------------
  */
  // Font
 // rdpq_font_t *fnt0 = rdpq_font_load("rom:/sixtyfour.font64");
 // rdpq_font_t *fnt1 = rdpq_font_load("rom:/revalia.font64");
 // rdpq_font_t *fnt2 = rdpq_font_load("rom:/squarewave.font64");

 // rdpq_text_register_font(FONT_SIXTYFOUR, fnt0);
 // rdpq_text_register_font(FONT_REVALIA, fnt1);
 // rdpq_text_register_font(FONT_SQUAREWAVE, fnt2);

 // rdpq_font_style(fnt0, 0 , &(rdpq_fontstyle_t) {
 //   .color = RGBA32(0x82, 0x30, 0x38, 0xFF),
 //   .outline_color = RGBA32 (255,255,255,255),
 // });

 // rdpq_font_style(fnt1, 0 , &(rdpq_fontstyle_t) {
 //   .color = RGBA32(0x82, 0x30, 0x38, 0xFF),
 //   .outline_color = RGBA32 (255,255,255,255),
 // });

 // rdpq_font_style(fnt2, 0 , &(rdpq_fontstyle_t) {
 //   .color = RGBA32(0x82, 0x30, 0x38, 0xFF),
 //   .outline_color = RGBA32 (255,255,255,255),
 // });


  /*
  -------------------------------------------------
  Main Menu screen //TODO - maybe a bit of clean up bellow before the while loop.
  -------------------------------------------------
  */



  // TODO - some comments would be nice.

  while(1) {

    //TODO- double switch is... bad

    switch(screen_state->currentScreenState) {
      case NO_SCREEN:
        screenMngLoadNext();
        break;
      case LOGO:
        // TODO - add button press to continue.
        n64brew_logo();
        libdragon_logo();
        tiny3d_logo();
        //introScreen();
        screenMngSetNext(MAIN_MENU);
        screenMngLoadNext();
        break;
      case TITLE_SCREEN:
      break;
      case MAIN_MENU:
        menu_button_e nextScreen = menuRender();

        switch (nextScreen)
        {
        case START_BUTTON:
          screenMngSetNext(GAME_PLAY);
          break;
        case SAVE_BUTTON:
          /* code */
          screenMngSetNext(GAME_PLAY);
          break;
        case SETTING_BUTTON:
          /* code */
          screenMngSetNext(GAME_PLAY);
          break;
        case EXIT_BUTTON:
          /* code */
          screenMngSetNext(GAME_PLAY);
          break;
        case BUTTON_COUNT:
          /* code */
          break;
        default:
          break;
        }

        screenMngLoadNext(GAME_PLAY);
        break;
      case GAME_PLAY:
        // Draw gameplay loop here
        rdpq_text_print(NULL, FONT_SQUAREWAVE, 20, 20, "GAMEPLAY LOADED");
        break;
      case SCREEN_STATE_COUNT: // not being used
        break;
    }
    //rdpq_detach_show();
  }
}
