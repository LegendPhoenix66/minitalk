#include "minitalk.h"

// Send a message to the server
void send_message(int pid, char *message)
{
	// Loop through each character in the message
	while (*message)
	{
		// Loop through each bit in the character
		for (int i = 7; i >= 0; i--)
		{
			// Send a SIGUSR1 signal if the bit is 1
			if ((*message >> i) & 1)
				kill(pid, SIGUSR2);
			// Send a SIGUSR2 signal if the bit is 0
			else
				kill(pid, SIGUSR1);
			// Wait for the server to confirm the signal
			usleep(100);
		}
		// Move to the next character
		message++;
	}
}

int main(int argc, char **argv)
{
	argc = argc;
	argv = argv;

	// Get the PID of the server
	int pid = ft_atoi(argv[1]);

	// Send the message to the server
	send_message(pid, argv[2]);

	return 0;
}