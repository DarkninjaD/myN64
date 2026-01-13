#include "displayMgr.h"
#include <libdragon.h>

/* PRIVATE state — not visible outside this file */
static bool display_initialized = false;

void display_mgr_init(resolution_t res, bitdepth_t bit, uint32_t num_buffers, gamma_t gamma, filter_options_t filters) {
    if (display_initialized) {
        return; /* already initialized, do nothing */
    }

    /* libdragon display init */
    display_init(res, bit, num_buffers, gamma,filters);
    display_initialized = true;
}

void display_mgr_close(void) {
    if (!display_initialized) {
        return; /* already closed, do nothing */
    }
    /* libdragon display close */
    display_close();
    display_initialized = false;
}

bool display_is_initialized(void) {
    return display_initialized;
}