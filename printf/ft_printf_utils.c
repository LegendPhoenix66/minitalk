#include <stdlib.h>

char	*ft_utoa(unsigned int n)
{
	unsigned int	temp;
	int				len;
	char			*str;

	temp = n;
	len = 1;
	while (temp /= 10)
		len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_utohex(unsigned int n, int uppercase)
{
	unsigned int	temp;
	int				len;
	char			*str;
	int				digit;

	temp = n;
	len = 1;
	while (temp /= 16)
		len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		digit = n % 16;
		str[len] = digit < 10 ? digit + '0' : digit - 10
			+ (uppercase ? 'A' : 'a');
		n /= 16;
	}
	return (str);
}

char	*ft_ptohex(void *ptr)
{
	unsigned long long	n;
	int					len;
	char				*str;
	int					digit;

	n = (unsigned long long)ptr;
	len = n ? 1 : 2;
	while (n && (n /= 16))
		len++;
	str = malloc(len + 3);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = 'x';
	str[len + 2] = '\0';
	n = (unsigned long long)ptr;
	while (len--)
	{
		digit = n % 16;
		str[len + 2] = digit < 10 ? digit + '0' : digit - 10 + 'a';
		n /= 16;
	}
	return (str);
}
