#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
/**
 * struct print_special - prints
 * @printer - function to print
 */
int _printf(const char *format, ...);
typedef struct print_special
{
    int (*printer)(va_list *);
} prnt;
int print_int(int arg);
void handle_int(va_list *arg);
void default_handler(va_list *a);
int print_char(char c);
void handle_char(va_list *args);
int print_string(char *str);
void handle_str(va_list *args);
int handle_type(char c, prnt *printer);

#endif
