#include "minitalk.h"

void	ft_putchar_fd(char c, int i);

int	ft_atoi(const char *nptr)
{
	int	ret;
	int	sign;
	int	i;

	ret = 0;
	sign = 1;
	i = 0;
	while (nptr[i] >= 9 && nptr[i] <= 13 || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		ret = ret * 10 + (nptr[i] - 48);
		i++;
	}
	return (ret * sign);
}
