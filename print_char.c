#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
/**
 * print_char - prints a char
 * @c: char to print
 * 
 * Return: 1
 */
int print_char(char c)
{
    return (write(1, &c, 1));
}
/**
 * handle_char - handles char
 * @args - list
 * 
 * Return: 1
 */
int handle_char(va_list *args)
{
    return (print_char(va_arg(*args, int)));
}