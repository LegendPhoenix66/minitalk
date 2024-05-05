#include "libft.h"
#include "ft_printf.h"
#include <stdarg.h>

void	print_char(va_list args, int *count)
{
	char	value;

	value = va_arg(args, int);
	ft_putchar_fd(value, 1);
	(*count)++;
}

void print_string(va_list args, int* count) {
    char *value = va_arg(args, char *);
    if (value == NULL) {
        value = "(null)";
    }
    ft_putstr_fd(value, 1);
    (*count) += ft_strlen(value);
}

void	print_int(va_list args, int* count) {
	int value = va_arg(args, int);
	char *str = ft_itoa(value);  // Convert integer to string
	ft_putstr_fd(str, 1);
	(*count) += ft_strlen(str);
	free(str);  // Don't forget to free the allocated memory
}

void	print_uint(va_list args, int* count) {
	unsigned int value = va_arg(args, unsigned int);
	char *str = ft_utoa(value);  // Convert unsigned integer to string
	ft_putstr_fd(str, 1);
	(*count) += ft_strlen(str);
	free(str);
}

void	print_hex(va_list args, int* count) {
    unsigned int value = va_arg(args, unsigned int);
    char *str = ft_utohex(value, 0);  // Convert unsigned integer to hexadecimal string
    ft_putstr_fd(str, 1);
    (*count) += ft_strlen(str);
    free(str);
}

void	print_hex_upper(va_list args, int* count) {
    unsigned int value = va_arg(args, unsigned int);
    char *str = ft_utohex(value, 1);  // Convert unsigned integer to hexadecimal string
    ft_putstr_fd(str, 1);
    (*count) += ft_strlen(str);
    free(str);
}

void	print_pointer(va_list args, int* count) {
	void *value = va_arg(args, void *);
	char *str = ft_ptohex(value);  // Convert pointer to hexadecimal string
	ft_putstr_fd(str, 1);
	(*count) += ft_strlen(str);
	free(str);
}

typedef void	(*print_func)(va_list, int *);

print_func	get_print_func(char specifier)
{
    static print_func funcs[] = {
        ['c'] = print_char,
        ['s'] = print_string,
        ['d'] = print_int,
        ['i'] = print_int,
        ['u'] = print_uint,
        ['x'] = print_hex,
        ['X'] = print_hex_upper,
        ['p'] = print_pointer,
        // Add other specifiers here...
    };
    unsigned char u_specifier = (unsigned char)specifier;
    return ((u_specifier < sizeof(funcs) / sizeof(*funcs)) ? funcs[u_specifier] : NULL);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			count;
	const char	*p = format;
	print_func	func;

	va_start(args, format);
	count = 0;
	while (*p != '\0')
	{
		if (*p == '%')
		{
			func = get_print_func(*++p);
			if (func)
			{
				func(args, &count);
			}
			else
			{
				ft_putchar_fd(*p, 1);
				count++;
			}
		}
		else
		{
			ft_putchar_fd(*p, 1);
			count++;
		}
		p++;
	}
	va_end(args);
	return (count); // Return the number of characters printed
}
