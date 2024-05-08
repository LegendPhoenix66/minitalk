#include "minitalk.h"

void send_message(int pid, char *message)
{
	message = ft_strjoin(message, "\x01");
	while (*message)
	{
		int i = 7;
		while (i >= 0) {
			if ((*message >> i) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(150);
			i--;
		}
		message++;
	}
}

void sig_handler(int signum)
{
	signum = signum;
	ft_printf("Message received by the server\n");
}

int main(int argc, char **argv)
{
	argc = argc;
	argv = argv;

	signal(SIGUSR1, sig_handler);

	int pid = ft_atoi(argv[1]);

	send_message(pid, argv[2]);

	return 0;
}