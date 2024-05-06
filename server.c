
#include "minitalk.h"

void handle_sigusr1(int sig)
{
    // This function will be called when the SIGUSR1 signal is received
    // Here, SIGUSR1 represents a binary 0
	sig = sig;
    ft_printf("Received binary 0\n");
}

void handle_sigusr2(int sig)
{
    // This function will be called when the SIGUSR2 signal is received
    // Here, SIGUSR2 represents a binary 1
	sig = sig;
    ft_printf("Received binary 1\n");
}

int main()
{
    // Register the signal handlers
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    ft_printf("PID: %d\n", getpid());
    while(1){
        // wait for signal
        pause();
    }
    return 0;
}