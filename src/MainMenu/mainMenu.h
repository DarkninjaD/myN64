#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <libdragon.h>
/**
 * @brief the different button
 */
// TODO - This is kinda weird is it the action or is it the button?
typedef enum MenuButtons {
  NO_BUTTON_SELECTED = -1,
  START_BUTTON,
  SAVE_BUTTON,
  SETTING_BUTTON,
  EXIT_BUTTON,
  BUTTON_COUNT,
} menu_button_e;

/**
 *  @brief Sets up the init state and loads assets of the main menu.
 */
void menuHandlerInit();

/**
 *  @deprecated use to menuInputTest
 *  @brief
 */
void menuInput(joypad_inputs_t pOne);

/**
 *  @brief handle input from user on main menu.
 */
menu_button_e menuInputTest(joypad_buttons_t pOne);

/**
 *  @brief Creates the frame for main menu to be displayed.
 */
void menuRender();

#endif
