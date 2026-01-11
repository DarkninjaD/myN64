#include <string.h>
#include <libdragon.h>
#include "util/consoleMgr.h"
#include "introCredits/introCredits.h"

int main(void) {
  console_mgr_init();
  intro_title_produced_by();
  // Adds the modal to add controller support
  joypad_init();
  // pull thing from cart
  dfs_init(DFS_DEFAULT_LOCATION);

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

  // set display
  display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);

  static sprite_t *spaceship;
  spaceship = sprite_load("rom:/spaceship.sprite");
  while(1) {
    surface_t *disp = display_get();
    graphics_fill_screen(disp, 0);
    graphics_draw_box(disp, 10,10,200,200, graphics_make_color(0,0,255,255));
    graphics_draw_sprite_trans(disp, 100, 100, spaceship);
    display_show(disp);
  }
}