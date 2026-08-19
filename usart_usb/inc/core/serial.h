#ifndef SERIAL_H
#define SERIAL_H

#include "common-defines.h"

void serial_setup(void);
void serial_putc(char);
void serial_puts(const char*);

void serial_println(const char*);
void serial_print_int(int32_t);
void serial_print_labeled(const char*, int32_t);


#endif