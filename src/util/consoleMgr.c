#include "consoleMgr.h"
#include <libdragon.h>

/* PRIVATE state — not visible outside this file */
static bool console_initialized = false;

void console_mgr_init(void) {
    if (console_initialized) {
        return; /* already initialized, do nothing */
    }

    /* libdragon console init */
    console_init();
    console_initialized = true;
}

void console_mgr_close(void) {
    if (!console_initialized) {
        return; /* already closed, do nothing */
    }
    /* libdragon console close */
    console_close();
    console_initialized = false;
}

bool console_is_initialized(void) {
    return console_initialized;
}