#include "ft_printf.h"

int g_count;

void ft_putchar(char c)
{
	write(1, &c, 1);
	g_count++;
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char *ft_itoa_base(unsigned long nbr, int base)
{
	int len;
	unsigned long tmp_nbr;
	char *str;

	tmp_nbr = nbr;
	len = 0;
	if (nbr == 0)
		len++;
	while (tmp_nbr > 0)
	{
		tmp_nbr /= base;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = nbr % base;
		if (nbr % base > 9)
			str[len - 1] += 'a' - 10;
		else
			str[len - 1] += '0';
		nbr /= base;
		len--;
	}
	return (str);
}

void ft_putdigit(long nbr)
{
	char *str;
	int i;
	int is_neg;

	is_neg = 0;
	if (nbr < 0)
	{
		nbr *= (-1);
		is_neg = 1;
	}
	str = ft_itoa_base(nbr, 10);
	if (is_neg)
		ft_putchar('-');
	i = 0;
	while (i < ft_strlen(str))
	{
		ft_putchar(str[i]);
		i++;
	}
	free(str);
}

void ft_puthex(unsigned long nbr)
{
	int i;
	char *str;

	str = ft_itoa_base(nbr, 16);
	i = 0;
	while (i < ft_strlen(str))
	{
		ft_putchar(str[i]);
		i++;
	}
	free(str);
}

void ft_putstr(char *str)
{
	int i;
	int len;

	len = 0;
	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

int ft_printf(const char *fmt_str, ... )
{
	g_count = 0;
	int i;

	va_list ap;
	va_start(ap, fmt_str);
	i = 0;
	while (fmt_str[i] != '\0')
	{
		if (fmt_str[i] == '%')
		{
			i++;
			if (fmt_str[i] == 's')
				ft_putstr(va_arg(ap, char *));
			else if (fmt_str[i] == 'd')
				ft_putdigit(va_arg(ap, int));
			else if (fmt_str[i] == 'x')
				ft_puthex(va_arg(ap, unsigned int));
		}
		else
			ft_putchar(fmt_str[i]);
		i++;
	}
	va_end(ap);
	return (g_count);
}

// int main(void)
// {
// 	int count;
// 	char *zero = "zero";

// 	count = printf("This is just a %s, not %s\n", "string", NULL);
// 	printf("%d\n", count);
// 	count = ft_printf("This is just a %s, not %s\n", "string", NULL);
// 	printf("%d\n", count);


// 	count = printf("This is just a %s %d\n", "number", -12345);
// 	printf("%d\n", count);
// 	count = ft_printf("This is just a %s %d\n", "string", -12345);
// 	printf("%d\n", count);

// 	count = printf("This is just a %s %x for %d and this is %s %d and %d \n", "hex", INT_MAX, INT_MAX, zero, 0 , 0);
// 	printf("%d\n", count);
// 	count = ft_printf("This is just a %s %x for %d and this is %s %d and %d \n", "hex", INT_MAX, INT_MAX, zero, 0 , 0);
// 	printf("%d\n", count);
// }