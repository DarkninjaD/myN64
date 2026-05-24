#include "introScreen.h"
#include <libdragon.h>
#include "../Util/consoleMgr.h"
#include "../ScreenMng/screenMng.h"
#include "../Util/fontAssets.h"

void introScreen () {
  //TODO - We load our IDKProductions due to the refactor.
  //  idk if it's the best idea to have the screenMngLoadNext() happen here or at the main level...

  if(joypad_is_connected(JOYPAD_PORT_1) && JOYPAD_STYLE_N64 == joypad_get_style(JOYPAD_PORT_1) ) {
    rdpq_text_print(NULL, FONT_SQUAREWAVE, 20, 20, "press start");
    joypad_inputs_t inputs;
      joypad_poll();
      inputs = joypad_get_inputs(JOYPAD_PORT_1);
       if(inputs.btn.start) {
        screenMngLoadNext();
       }
  }
  else {
    rdpq_text_print(NULL, FONT_SQUAREWAVE, 20, 20, "Missing Controller");
  }
}