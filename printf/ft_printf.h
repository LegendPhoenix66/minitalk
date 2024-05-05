#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "libft/libft.h"
#include <stdarg.h>

// Function pointer type for print functions
typedef void (*print_func)(va_list args, int *count);

// Function prototypes
int ft_printf(const char *format, ...);
char *ft_utoa(unsigned int n);
char *ft_utohex(unsigned int n, int uppercase);
char *ft_ptohex(void *ptr);

#endif // FT_PRINTF_H
