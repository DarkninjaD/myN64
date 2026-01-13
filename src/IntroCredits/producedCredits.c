#include "introCredits.h"
#include <libdragon.h>
#include "../Util/consoleMgr.h"

void intro_title_produced_by(void) {

  if(!console_is_initialized()) {
    console_mgr_init();
  }
  // set the color to green for some reason. it's a 16 bit color but you need to repeat to make sure it work
  // ie 0x4407 = green but we need to repeat the 4407
  // TODO - The color is changed forever here and we can't find out
  //  what the state of the color was before ether we have another wrapper
  //  that manges it's state of color or something for now dont' care.
  graphics_set_color(0x44074407,0x00000000);
  // ASCII Art made with Doom art font
    const char *art =
" ___________ _   __ ______                         _       \n"
"|_   _|  _  \\ | / / | ___ \\                       | |      \n"
"  | | | | | | |/ /  | |_/ / __ ___  ___  ___ _ __ | |_ ___ \n"
"  | | | | | |    \\  |  __/ '__/ _ \\/ __|/ _ \\ '_ \\| __/ __|\n"
" _| |_| |/ /| |\\  \\ | |  | | |  __/\\__ \\  __/ | | | |_\\__ \\\n"
" \\___/|___/ \\_| \\_/ \\_|  |_|  \\___||___/\\___|_| |_|\\__|___|\n"
"                                                           \n"
"                                                           \n";

    printf("%s", art);
}
