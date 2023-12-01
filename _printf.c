#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

/**
 * struct print_special - prints
 * @printer - function to print
 */

typedef struct print_special
{
    int (*printer)(va_list *);
} prnt;

/**
 * pow10 - pow10
 * @n: arg
 * 
 * Return: power
*/
unsigned _pow10(unsigned int n)
{
    unsigned pw = 1, i = 0;

    for (; i < n; i++)
        pw *= 10;
    
    return (pw);
}

/**
 * print_int - prints an integer
 * @arg: list of arguments
 *
 * Return: number of characters printed
 */
int print_int(int arg)
{
    unsigned int a = arg, tmp, len = 0, c_c = 0, i;
    char *curr;

    if (arg == 0)
    {
        return (write(1, "0", 1));
    }

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

    curr = malloc(len * sizeof(char));

    if (!curr)
        return (0);

    for (i = 0; i < len; i++)
    {
        curr[i] = (int)(a / abs((int)_pow10(len - 1 - i)) % 10) + '0';
        /*printf("reqem is %d i is %i\n", ((int)(a / _pow10(len - 1 - i)) % 10), i);*/
    }


    c_c += write(1, curr, len);

    free(curr);

    return (c_c);
}

/**
 * handle_int - handles an integer
 * @arg: list of arguments
 * Return: number of characters printed
 */
int  handle_int(va_list *arg)
{
    return (print_int(va_arg(*arg, int)));
}

/**
 * default_handler - default handler
 * @a: arg
 */
int default_handler()
{
    return (0);
}

/**
 * print_char - prints a char
 * @c: char to print
 */
int print_char(char c)
{
    return (write(1, &c, 1));
}
/**
 * handle_char - handles char
 * @args - list
 */
int handle_char(va_list *args)
{
    return (print_char(va_arg(*args, int)));
}

/**
 * print_string - prints string
 * @s: string
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
 */
int handle_str(va_list *args)
{
    return (print_string(va_arg(*args, char *)));
}

/**
 * handle_prcnt - handles % sign
 * 
 * Return: number of char printed
*/
int handle_prcnt()
{
    return (write(1, "%", 1));
}

/**
 * handle_type - handles a type
 * @c: list of arguments
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
 * Return: number of characters printed
 */

int _printf(const char *format, ...)
{
    va_list args;
    int i;
    int len, c_c = 0, pass;
    int start = 0;
    prnt _printer;

    _printer.printer = handle_int;

    if (format == NULL)
        return (-1);

    len = strlen(format);

    va_start(args, format);

    for (i = 0; i < len; i++)
    {
        if (format[i] == '%' && i + 1 < len)
        {
        
            write(1, format + start, i - start);
            pass = handle_type(format[i + 1], &_printer);
            start = i + pass;
            i++;
            c_c += _printer.printer(&args) - pass + 1;

        }
        if (format[i] == '%' && (i + 1 == len || format[i + 1] == ' ') )
        {
            c_c--;
            write(1, format + start, i - start);
            start = i + 1;
        }
        c_c++;
    }
    write(1, format + start, i - start);
    va_end(args);
    return (c_c);
}
