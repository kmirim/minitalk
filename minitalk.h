#include <unistd.h>
#include <signal.h>

#ifndef MINITALK_H
 #define MINITALK_H
#endif

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int	ft_atoi(const char *nptr);
void	send_message(int signum);
void	ft_char_to_bits(int pid, unsigned char c);
