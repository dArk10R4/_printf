#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <stdarg.h>

/**
 * struct print_special - prints
 * @printer - function to print
 */

typedef struct print_special
{
int (*printer)(va_list *);
} prnt;

int _printf(const char *format, ...);
int print_int(int arg);
int handle_int(va_list *arg);
int print_char(char c);
int handle_char(va_list *args);
int print_string(char *str);
int handle_str(va_list *args);
int handle_type(char c, prnt *printer);

#endif
