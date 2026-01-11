#ifndef CONSOLE_MGR_H
#define CONSOLE_MGR_H

#include <stdbool.h>

void console_mgr_init(void);

void console_mgr_close(void);

bool console_is_initialized(void);

#endif