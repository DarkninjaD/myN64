#include "unity.h"
#include "screenMng.h"

// This runs BEFORE each individual test
void setUp(void) {
    screenMngInit();
}

// This runs AFTER each individual test
void tearDown(void) {
    // No heap memory to free in this module
}

void test_InitShouldSetCorrectDefaultStates(void) {
    screen_state_e* current = screenMngCurrentState();
    TEST_ASSERT_EQUAL_INT(NO_SCREEN, *current);
}

void test_LoadNextShouldTransitionState(void) {
    screenMngLoadNext();
    screen_state_e* current = screenMngCurrentState();
    TEST_ASSERT_EQUAL_INT(LOGO, *current);
}
