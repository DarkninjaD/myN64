#ifndef DISPLAY_MGR_H
#define DISPLAY_MGR_H

#include <stdbool.h>
#include <libdragon.h>

void display_mgr_init(resolution_t res, bitdepth_t bit, uint32_t num_buffers, gamma_t gamma, filter_options_t filters);

void display_mgr_close(void);

bool display_is_initialized(void);

#endif