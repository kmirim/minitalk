#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, 1);
		s++;
	}
}

void	ft_putnbr_fd(long n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', 1);
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + 48, fd);
	}
	else 
		ft_putchar_fd(n + 48, fd);
}

static	void	convert_bit(int bit, int *finish_convert)
{
	static int	i = 10;
	static int	character;

	character += (bit << i);
	i--;
	if(i < 0)
	{
		if (character == '\0')
		{
			character = '\n';
			*finish_convert = 1;
		}
		i = 10;
		ft_putchar_fd(character, 1);
		character = 0;
	}
}
static void	handler(int signum, siginfo_t *info, void *context)
{
	int	finish;

	finish = 0;
	convert_bit(SIGUSR2 == signum, &finish);
	kill(info->si_pid, SIGUSR1);
	if(finish)
		kill(info->si_pid, SIGUSR2);
	(void)context;
}

int	main(void)
{
	struct	sigaction	act;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
