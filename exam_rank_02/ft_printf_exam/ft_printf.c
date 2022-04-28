#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int g_count;
int g_mwidth;
int g_precision;

void ft_putchar(char c)
{
	write(1, &c, 1);
	g_count += 1;
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
	char *str;
	unsigned long tmp_nbr;

	tmp_nbr = nbr;
	len = 0;

	if (nbr == 0)
		len++;
	while (tmp_nbr > 0)
	{
		tmp_nbr /= base;
		len++;
	}
	str = malloc(len + 1);
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
	int i;
	int len;
	int is_neg;
	char *str;

	i = 0;
	len = 0;
	is_neg = 0;
	if (nbr < 0)
	{
		nbr *= (-1);
		is_neg = 1;
	}
	str = ft_itoa_base(nbr, 10);
	if (nbr == 0 && g_precision == 0)
	{
		free(str);
		str = "";
	}
	len = ft_strlen(str);
	if (g_precision != -1 && g_precision > len)
		len = g_precision;
	if (is_neg == 1 && g_mwidth > 0)
		g_mwidth--;
	while (g_mwidth > len)
	{
		ft_putchar(' ');
		g_mwidth--;
	}
	if (is_neg)
		ft_putchar('-');
	while (len > ft_strlen(str))
	{
		ft_putchar('0');
		len--;
	}
	while (i < ft_strlen(str))
	{
		ft_putchar(str[i]);
		i++;
	}
	if (!(nbr == 0 && g_precision == 0))
		free(str);
}

void ft_puthex(unsigned long to_hex)
{
	int i;
	int len;
	char *str;

	i = 0;
	len = 0;
	str = ft_itoa_base(to_hex, 16);
	if (to_hex == 0 && g_precision == 0)
	{
		free(str);
		str = "";
	}
	len = ft_strlen(str);
	if (g_precision != -1 && g_precision > len)
		len = g_precision;
	while (g_mwidth > len)
	{
		ft_putchar(' ');
		g_mwidth--;
	}
	while (len > ft_strlen(str))
	{
		ft_putchar('0');
		len--;
	}
	while (i < ft_strlen(str))
	{
		ft_putchar(str[i]);
		i++;
	}
	if (!(to_hex == 0 && g_precision == 0))
		free(str);
}

void ft_putstr(char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (str == NULL)
		str = "(null)";
	if (g_precision == 0)
		str = "";
	len = ft_strlen(str);
	if (g_precision != -1 && g_precision < len)
		len = g_precision;
	while (g_mwidth > len)
	{
		ft_putchar(' ');
		g_mwidth--;
	}
	while (i < len)
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
			/*сбросить флаги*/
			g_mwidth = 0;
			g_precision = -1;
			while (fmt_str[i] >= '0' && fmt_str[i] <= '9')
			{
				g_mwidth = (g_mwidth * 10) + (fmt_str[i] - '0'); /*повышаем разрядность на десять*/
				i++;
			}
			if (fmt_str[i] == '.')
			{
				i++;
				g_precision = 0;
				while (fmt_str[i] >= '0' && fmt_str[i] <= '9')
				{
					g_precision = (g_precision * 10) + (fmt_str[i] - '0');
					i++;
				}
			}
			if (fmt_str[i] == 's')
				ft_putstr(va_arg(ap, char *));
			if (fmt_str[i] == 'd')
				ft_putdigit(va_arg(ap, int));
			if (fmt_str[i] == 'x')
				ft_puthex(va_arg(ap, unsigned int));
		}
		else
			ft_putchar(fmt_str[i]);
		i++;
	}
	va_end(ap);
	return (g_count);
}
/*
#include <stdio.h>
#include <limits.h>

int main (void)
{
    int count; 

    // count = printf("%23.s\n", NULL); //...
    // printf("   printf_c: %d\n", count);
    // count = ft_printf("%23.s\n", NULL);
    // printf("ft_printf_c: %d\n", count);

    // count = printf("THIS IS DIGIT: \t [%.d]\n", 7483648);   //
    // printf("   printf_c: %d\n", count);
    // count = ft_printf("THIS IS DIGIT: \t [%.d]\n", 7483648);   //
    // printf("ft_printf_c: %d\n", count);

	// count = ft_printf(" %d %x %d %d %d %d %d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);   //
	// printf("ft_printf_c: %d\n", count);
	// count = printf(" %d %x %d %d %d %d %d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);   //
	// printf("   printf_c: %d\n", count);

	count = printf("Magic [%.2s] is [%10d] and [%.1s] hex is [%.3x] \n", "OFkwfw fwfoqwf", INT_MIN, "marvelous", -214748); //Magic number is ___42%
	printf("   printf_c: %d\n", count);
	ft_printf("-------------------------------------\n");
    count = ft_printf("Magic [%.2s] is [%10d] and [%.1s] hex is [%.3x] \n", "OFkwfw fwfoqwf", INT_MIN, "marvelous", -214748); //Magic number is ___42%
	printf("ft_printf_c: %d\n", count);

    // count = printf("%.s", "");
    // printf("   printf_c: %d\n", count);
	// ft_printf("-------------------------------------\n");
    // count = ft_printf("%.s", "");
    // printf("ft_printf_c: %d\n", count);

    // count = printf("%8.5d", 34);
	// printf("   printf_c: %d\n", count);
	// count = ft_printf("%8.5d", 34);
	// printf("ft_printf_c: %d\n", count);

    // char *str = ft_itoa_base(556, 10);
    // char *str1 = ft_itoa_base(0x2ab2c, 16);
    // printf("%d %x\n", 556, 556);
    // printf("%s\n", str);
    // printf("%s\n", str1);
    // free(str);
    // free(str1);

    return (0);
}*/