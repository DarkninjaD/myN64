#include <string.h>
#include <libdragon.h>
#include "util/consoleMgr.h"
#include "introCredits/introCredits.h"

enum {
  FONT_SIXTYFOUR = 1,
  FONT_REVALIA = 2,
  FONT_SQUAREWAVE = 3,
};

static sprite_t *btn_game;

void menu_button(surface_t *disp) {


  int screen_width = display_get_width();
  int screen_height = display_get_height();

  int box_width = screen_width * 0.8f;
  int box_height = screen_height * 0.8f;


  //rdpq_set_mode_fill();
  //rdpq_fill_rectangle();
  // rdpq_tex_multi_begin();
  rdpq_sprite_upload(TILE0, btn_game, &(rdpq_texparms_t){
      .s.repeats = 1, .t.repeats = 1,
  });
  // rdpq_tex_reuse_sub(TILE1, &(rdpq_texparms_t){
  //     .s.repeats = 1, .t.repeats = 1,
  // }, 0, 0, 16, 16);
  // rdpq_tex_multi_end();

  //rdpq_text_printn(NULL, FONT_REVALIA, 12, 12, "Hello", 8);
}

int main(void) {
  console_mgr_init();
  intro_title_produced_by();
  // Adds the modal to add controller support
  joypad_init();
  rdpq_init();
  // pull thing from cart
  dfs_init(DFS_DEFAULT_LOCATION);

  btn_game = sprite_load("rom:/btnGame.sprite");


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
    //graphics_fill_screen(disp, 0);
    //graphics_draw_box(disp, 10,10,200,200, graphics_make_color(0,0,255,255));
    //graphics_draw_sprite_trans(disp, 100, 100, spaceship);
    rdpq_attach_clear(disp, NULL);
    menu_button(disp);
    rdpq_detach_show();
    //display_show(disp);
  }
}