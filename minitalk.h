#ifndef MINITALK_H
#define MINITALK_H

#include "printf/ft_printf.h"
#include <unistd.h>
#include <signal.h>

struct s_connection {
	int sender_pid;
	int received_bits[8];
};

#endif //MINITALK_H
