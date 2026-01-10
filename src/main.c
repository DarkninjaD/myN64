#include <string.h>
#include <libdragon.h>

int main(void) {
  console_init();
  // set the color to green for some reason. it's a 16 bit color but you need to repeat to make sure it work
  // ie 0x4407 = green but we need to repeat the 4407
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
    // Adds the modal to add controller support
    joypad_init();
    // pull thing from cart
    dfs_init(DFS_DEFAULT_LOCATION);

    // check that and n64 type controller is in port 1
    if(joypad_is_connected(JOYPAD_PORT_1) && JOYPAD_STYLE_N64 == joypad_get_style(JOYPAD_PORT_1) ) {
      puts("       Press A to continue ");
      joypad_inputs_t inputs;
      // main loop
      bool intro_scene = true;
      while(intro_scene) {
        joypad_poll();
        inputs = joypad_get_inputs(JOYPAD_PORT_1);
        if(inputs.btn.a) {
          intro_scene = false;
          console_close();
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
      //graphics_draw_box(disp, 10,10,200,200, graphics_make_color(0,0,255,255));
      graphics_draw_sprite_trans(disp, 100, 100, spaceship);
      display_show(disp);
    }
}