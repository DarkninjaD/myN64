# 🗺️ Testing Strategy Guide

Welcome! This guide explains how to write deterministic unit tests for the N64 codebase.
Due to debugging code directly on MIPS architecture hardware or emulators is difficult, we isolate our core game logic and test it natively on our host PCs using Ceedling.

---

## 📃 The Testing Plan

The most effective way to handle this architecture mismatch is to keep your core engine logic decoupled from `libdragon` hardware calls.

- **The Logic Layer:** state machines, math routines, and data structures should only manipulate standard C variables, structs, and enums.
- **The Render Layer:** The Main game loop checks the structural data and states, then executes the actual `libdragon` draw routines or controller register checks.

By drawing this clear boundary is necessary, to allow the core logic to be tested entirely on the PC.

---

## 💥 When world collide

If a source file _must_ directly include a `libdragon` header file to compile, you can easily bypass the missing file error using Ceedling's pathing priority.

Because Ceedling explicitly searches the support directory during host test builds, your local `gcc` compiler will find this fake header, see that it contains no code, and compile your logic smoothly.

## 🏛️ Anatomy of a Test File

Every test file lives in the `test/` directory, must be named with a `test_` prefix (e.g., `test_screenMng.c`), and follows a strict four-part lifecycle: **Setup, Teardown, Execution, and Mocking**.

### 1. Pre-Test Lifecycle (`setUp` and `tearDown`)

Every test file _must_ define these two functions. Ceedling automatically executes them around every single individual test block.

- `void setUp(void)`: Initialize or reset state variables here to guarantee a clean slate for the next test.
- `void tearDown(void)`: Clean up memory, close files, or reset global pointers here.

### 2. Assertions

We use Unity's assertion macro library to validate logic. Always pass the **Expected** value first, followed by the **Actual** value:

- `TEST_ASSERT_EQUAL_INT(expected, actual);`
- `TEST_ASSERT_TRUE(condition);`
- `TEST_ASSERT_EQUAL_STRING(expected, actual);`

---

### 🛠️ Code Example: Assertions & Lifecycle

Below is a standard unit test for our Screen Manager state machine (`src/ScreenMng/screenMng.c`).

```c
#include "unity.h"
#include "screenMng.h"

// This runs BEFORE test_Init and BEFORE test_LoadNext
void setUp(void) {
    screenMngInit();
}

// This runs AFTER test_Init and AFTER test_LoadNext
void tearDown(void) {
    // No heap memory to free in this module, leaving blank
}

void test_InitShouldSetCorrectDefaultStates(void) {
    // Given the setup reset the state machine...
    screen_state_e* current = screenMngCurrentState();

    // Then verify the initial values are correct
    TEST_ASSERT_EQUAL_INT(NO_SCREEN, *current);
}

void test_LoadNextShouldTransitionState(void) {
    // When a transition occurs...
    screenMngLoadNext();
    screen_state_e* current = screenMngCurrentState();

    // Then verify the state properly advanced
    TEST_ASSERT_EQUAL_INT(INIT, *current);
}
```

## 🎭 Isolating Dependencies with Mocking (CMock)

In N64 development, modules frequently talk to each other (e.g., your Screen Manager might tell an audio manager to change background music). When testing the Screen Manager, we _don't_ want to run actual audio code.

By adding `mock_` to an include statement, Ceedling automatically generates a fake version of that header file and creates `_Expect` functions for you.

### Mocking Example

Assume we have an audio module header `audioMng.h` with a function `void audioMngPlaySound(int soundId);`. Here is how we mock it:

```c
#include "unity.h"
#include "screenMng.h"

// Instruct CMock to intercept all calls to the audio manager
#include "mock_audioMng.h"

void setUp(void) {
    screenMngInit();
}

void tearDown(void) {}

void test_EnteringMainMenuPlaysMusic(void) {
    // 1. Tell the mock engine to EXPECT audioMngPlaySound to be called exactly once
    //    with the argument MAIN_MENU_BGM.
    audioMngPlaySound_Expect(MAIN_MENU_BGM);

    // 2. Fire the code under test that triggers the audio call internally
    screenMngSetNext(MAIN_MENU);
    screenMngLoadNext();

    // If screenMng fails to call audioMngPlaySound, or calls it with the wrong ID,
    // Ceedling will immediately fail this test.
}

```
