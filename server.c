#include "minitalk.h"

void	send_message(int signum)
{
	static char	c = 0xFF;
	static int	i;

	if (signum == SIGUSR1)
		c = c ^ 128 >> i;
       	else if (signum == SIGUSR2)
		c = c | 128 >> i;
	if(++i == 8)
	{
		ft_putchar_fd(c, 1);
		i = 0;
		c = 0xFF;
	}
}

int	main(void)
{
	signal(SIGUSR1, send_message);
	signal(SIGUSR2, send_message);
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
