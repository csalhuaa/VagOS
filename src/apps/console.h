#ifndef M_CONSOLE_H
#define M_CONSOLE_H

#include "../util/printf.h"
#include "../util/string.h"

void user_printf(const char* str);

void system_printf(const char* str);

void user_input(const char* str);

void system_input(const char* str);

#endif 