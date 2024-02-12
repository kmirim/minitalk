#include "minitalk.h"

void	ft_putchar_fd(char c, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = (long)n;
	if (num < 0)
	{
		ft_putchar_fd('-', 1);
		num *= -1;
	}
	if (num > 9)
	{
		ft_putnbr_fd(num / 10, 1);
		ft_putchar_fd((num % 10) + 48, fd);
	}
	else
		ft_putchar_fd(num + 48, fd);
}
