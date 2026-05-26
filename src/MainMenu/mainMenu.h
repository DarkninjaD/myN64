#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <libdragon.h>

// TODO - This is kinda weird is it the action or is it the button?
/**
 * @brief the different button
 */
typedef enum MenuButtons {
  START_BUTTON,
  SAVE_BUTTON,
  SETTING_BUTTON,
  EXIT_BUTTON,
  BUTTON_COUNT,
} menu_button_e;

// TODO - do I move the doc to the internal class?
/**
 *  @brief Sets up the init state and loads assets of the main menu.
 */
//void menuHandlerInit();

/**
 *  @deprecated use to menuInputTest
 *  @brief
 */
//void menuInput(joypad_inputs_t pOne);

/**
 *  @brief Creates the frame for main menu to be displayed.
 */
menu_button_e menuRender();

#endif
