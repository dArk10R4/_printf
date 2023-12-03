#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
/**
 * _pow10 - pow10
 * @n: arg
 *
 * Return: power
 */
unsigned int _pow10(unsigned int n)
{
    unsigned int pw = 1, i = 0;

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
 * 
 * Return: number of characters printed
 */
int handle_int(va_list *arg)
{
    return (print_int(va_arg(*arg, int)));
}