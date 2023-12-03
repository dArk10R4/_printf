#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include "main.h"



/**
 * default_handler - default handler
 * @a: dummy
 *
 * Return: 0
 */
int default_handler(va_list *a)
{
	(void)a;
	return (0);
}



/**
 * handle_prcnt - handles % sign
 * @a: dummy
 *
 * Return: number of char printed
 */
int handle_prcnt(va_list *a)
{
	(void)(a);
	return (write(1, "%", 1));
}

/**
 * handle_type - handles a type
 * @c: list of arguments
 * @printer: prnt *
 *
 * Return: number of characters printed
 */

int handle_type(char c, prnt *printer)
{
	switch (c)
	{
	case 'd':
	case 'i':
		printer->printer = handle_int;
		return (2);
	case 'c':
		printer->printer = handle_char;
		return (2);
	case 's':
		printer->printer = handle_str;
		return (2);
	case '%':
		printer->printer = handle_prcnt;
		return (2);
	default:
		printer->printer = default_handler;
	}

	return (0);
}

/**
 * _printf - prints anything
 * @format: list of types of arguments passed to the function
 *
 * Return: number of characters printed
 */

int _printf(const char *format, ...)
{
	va_list args;
	int len, c_c = 0, pass, i, start = 0;
	prnt _printer;

	_printer.printer = handle_int;

	if (format == NULL)
		return (-1);

	len = strlen(format);
	va_start(args, format);

	for (i = 0; i < len; i++)
	{
		if (format[i] == '%')
		{
			if (i + 1 < len)
			{
				write(1, format + start, i - start);
				pass = handle_type(format[i + 1], &_printer);
				start = i + pass;
				i++;
				c_c += _printer.printer(&args) - pass + 1;
			}
			else
			{
				c_c--;
				write(1, format + start, i - start);
				start = i + 1;
			}
		}

		c_c++;
	}
	write(1, format + start, i - start);
	va_end(args);
	return (c_c == 0 ? -1 : c_c);
}
