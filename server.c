#include "minitalk.h"

struct s_connection g_connection;

void handle_sigusr1(int sig, siginfo_t *info, void *ucontext)
{
	sig = sig;
	ucontext = ucontext;
	if (g_connection.sender_pid == 0) {
		g_connection.sender_pid = info->si_pid;
	} else if (g_connection.sender_pid != info->si_pid) {
		return;
	}

	int i = 0;
	while (i < 8) {
		if (g_connection.received_bits[i] == -1) {
			g_connection.received_bits[i] = 0;
			break;
		}
		++i;
	}
}

void handle_sigusr2(int sig, siginfo_t *info, void *ucontext)
{
	sig = sig;
	ucontext = ucontext;

	if (g_connection.sender_pid == 0) {
		g_connection.sender_pid = info->si_pid;
	} else if (g_connection.sender_pid != info->si_pid) {
		return;
	}

	int i = 0;
	while (i < 8) {
		if (g_connection.received_bits[i] == -1) {
			g_connection.received_bits[i] = 1;
			break;
		}
		++i;
	}
}

void clear_received_bits()
{
	int i = 0;
	while (i < 8) {
		g_connection.received_bits[i] = -1;
		++i;
	}
}

int check_flag()
{
	int i = 0;
	while (i < 7) {
		if (g_connection.received_bits[i] != 0) {
			return 0;
		}
		++i;
	}
	if (g_connection.received_bits[i] != 1) {
		return 0;
	}
	return 1;
}

int main()
{
	struct sigaction sa;

	// Register the signal handlers
	sa.sa_sigaction = handle_sigusr1;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);

	sa.sa_sigaction = handle_sigusr2;
	sigaction(SIGUSR2, &sa, NULL);

	g_connection.sender_pid = 0;
	clear_received_bits();

	ft_printf("PID: %d\n", getpid());
	int count = 0;
	while (1) {
		while (count < 8) {
			pause();
			++count;
		}
		count = 0;
		if (check_flag()) {
			kill(g_connection.sender_pid, SIGUSR1);
			clear_received_bits();
			g_connection.sender_pid = 0;
			ft_printf("\n");
			continue;
		}
		char c = 0;
		int i = 0;
		while (i < 8) {
			if (g_connection.received_bits[i] == -1) {
				ft_printf("Error: missing bit: %d\n", i);
			}
			c |= g_connection.received_bits[i] << (7 - i);
			++i;
		}
		ft_printf("%c", c);
		clear_received_bits();
	}
	return 0;
}