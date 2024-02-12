#include "minitalk.h"

void	ft_char_to_bits(int pid, unsigned char c)
{
	int	count;

	count = 7;
	while (count-- >= 0)
	{
		if(c & 0b10000000)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c << 1;
		usleep(200);
	}
}

int	main(int count, char **value)
{
	int	pid;
	int	i;

	i = 0;
	if(count == 3)
	{
		pid = ft_atoi(value[1]);
		while(value[2][i])
		{
			ft_char_to_bits(pid, value[2][i]);
			i++;
		}
		return (0);
	}
	else
	{
		ft_putstr_fd("Usage: ./client <pid> [message].\n", 1);
		return (-1);
	}
	return (0);
}
