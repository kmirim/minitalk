 #include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write (fd, &*s++, 1);
}

static void	send_error(int pid, int signum)
{
	if (kill(pid, signum) == -1)
		ft_putstr_fd("Failed to establish connection.\n", 1);
	exit(1);
}

static void	char_to_bits(int pid , unsigned char c)
{
	int	i;

	i = -1;
	while(++i < 8)
	{
		if (c & 0b10000000)
			kill(pid,SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(200);
	}
}

static int	signal_control;

static void	read_message(char *msg, int pid)
{
	while(*msg)
	{
		char_to_bits(pid, *msg);
		msg++;
	}
}

static void	handler(int signum)
{
	if (signum == SIGUSR1)
		signal_control = 0;
	else if (signum == SIGUSR2)
		ft_putstr_fd("Message send!\n", 1);
}

int	main(int count, char **value)
{
	struct	sigaction	act;

	act.sa_handler = handler;
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	int	pid;

	if (count == 3)
	{	
		pid = atoi(value[1]);
		read_message(value[2], pid);
		signal_control = 1;
	}
	else 
		ft_putstr_fd("Plese. Usage: ./client <pid> [message].\n", 1);
	return (0);
}
