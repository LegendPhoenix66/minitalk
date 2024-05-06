
#include "minitalk.h"

int g_received_bits = 0;

void handle_sigusr1(int sig)
{
    // This function will be called when the SIGUSR1 signal is received
    // Here, SIGUSR1 represents a binary 0
	sig = sig;
	g_received_bits = g_received_bits << 1;
}

void handle_sigusr2(int sig)
{
    // This function will be called when the SIGUSR2 signal is received
    // Here, SIGUSR2 represents a binary 1
	sig = sig;
	g_received_bits = (g_received_bits << 1) | 1;
}

int main()
{
    // Register the signal handlers
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    ft_printf("PID: %d\n", getpid());
	int count = 0;
    while(1){
        // wait for signal
        pause();
		count++;
		if (count % 8 == 0){
			ft_printf("%c", g_received_bits);
			g_received_bits = 0;
		}
    }
    return 0;
}