#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * print_string - prints string
 * @str: string
 *
 * Return: len of str
 */
int print_string(char *str)
{
	int l;

	if (str == NULL)
		return (write(1, "(null)", 6));

	l = strlen(str);

	return (write(1, str, l));
}

/**
 * handle_str - handles string
 * @args: list
 *
 * Return: len
 */
int handle_str(va_list *args)
{
	return (print_string(va_arg(*args, char *)));
}
