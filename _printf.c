#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

/**
 * struct print_special - Function pointer structure for handling print types
 * @printer: Function pointer for printing
 */
typedef struct print_special
{
    int (*printer)(va_list *);
} prnt;

/**
 * _pow10 - Calculate 10 to the power of n
 * @n: Exponent
 *
 * Return: Result of 10 to the power of n
 */
unsigned int _pow10(unsigned int n)
{
    unsigned int pw = 1, i = 0;

    for (; i < n; i++)
        pw *= 10;

    return (pw);
}

/**
 * print_int - Print an integer
 * @arg: List of arguments
 *
 * Return: Number of characters printed
 */
int print_int(int arg)
{
    unsigned int a = arg, tmp, len = 0, c_c = 0, i;
    char *curr;

    if (arg == 0)
        return (write(1, "0", 1));

    if (arg < 0)
    {
        write(1, "-", 1);
        a = -a;
        c_c++;
    }
    tmp = a;

    while (tmp > 0)
    {
        tmp /= 10;
        len++;
    }

    curr = malloc((len + 1) * sizeof(char));

    if (!curr)
        return (0);

    for (i = 0; i < len; i++)
    {
        curr[i] = (int)(a / abs((int)_pow10(len - 1 - i)) % 10) + '0';
    }

    curr[len] = '\0'; /* Null-terminate the string */

    c_c += write(1, curr, len);

    free(curr);

    return (c_c);
}

/**
 * handle_int - Handle an integer argument
 * @arg: List of arguments
 *
 * Return: Number of characters printed
 */
int handle_int(va_list *arg)
{
    return (print_int(va_arg(*arg, int)));
}

/**
 * default_handler - Default handler
 *
 * Return: Always returns 0
 */
int default_handler(va_list *arg)
{
    (void)arg; /* Unused parameter */
    return (0);
}

/**
 * print_char - Print a single character
 * @c: Character to print
 *
 * Return: Number of characters printed
 */
int print_char(char c)
{
    return (write(1, &c, 1));
}

/**
 * handle_char - Handle a character argument
 * @args: List of arguments
 *
 * Return: Number of characters printed
 */
int handle_char(va_list *args)
{
    return (print_char(va_arg(*args, int)));
}

/**
 * print_string - Print a string
 * @str: String to print
 *
 * Return: Number of characters printed
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
 * handle_str - Handle a string argument
 * @args: List of arguments
 *
 * Return: Number of characters printed
 */
int handle_str(va_list *args)
{
    return (print_string(va_arg(*args, char *)));
}

/**
 * handle_prcnt - Handle the '%' sign
 *
 * Return: Number of characters printed
 */
int handle_prcnt(va_list *args)
{
    (void)args; /* Unused parameter */
    return (write(1, "%", 1));
}

/**
 * handle_type - Handle a format specifier
 * @c: Format specifier
 * @printer: Pointer to the structure containing the function pointer
 *
 * Return: Number of characters to skip (including the format specifier)
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

    return (1); /* Return 1 to account for the character after '%' */
}

/**
 * _printf - Custom printf function
 * @format: Format string with optional format specifiers
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
    va_list args;
    int i, len, c_c = 0, pass;
    int start = 0;
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

