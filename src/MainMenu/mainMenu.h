#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <libdragon.h>

typedef enum {
  NO_BUTTON_SELECTED = -1,
  START_BUTTON,
  SAVE_BUTTON,
  SETTING_BUTTON,
  EXIT_BUTTON,
  BUTTON_COUNT,
} menu_button_t;

void menuHandlerInit();

void menuInput(joypad_inputs_t pOne);

menu_button_t menuInputTest(joypad_buttons_t pOne);

void menuRender();

#endif
