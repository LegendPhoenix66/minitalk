/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:29:05 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/22 11:29:14 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_message(int pid, char *message)
{
	int	i;

	message = ft_strjoin(message, "\x01");
	while (*message)
	{
		i = 7;
		while (i >= 0)
		{
			if ((*message >> i) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(50);
			i--;
		}
		message++;
	}
}

void	sig_handler(int signum)
{
	signum = signum;
	ft_printf("Message received by the server\n");
}

int	main(int argc, char **argv)
{
	int	pid;

	argc = argc;
	argv = argv;
	signal(SIGUSR1, sig_handler);
	pid = ft_atoi(argv[1]);
	send_message(pid, argv[2]);
	return (0);
}
