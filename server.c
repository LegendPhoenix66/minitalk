/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:29:25 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/22 11:53:40 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct s_connection	g_connection;

void	handle_sigusr1(int sig, siginfo_t *info, void *ucontext)
{
	int	i;

	sig = sig;
	ucontext = ucontext;
	if (g_connection.sender_pid == 0)
	{
		g_connection.sender_pid = info->si_pid;
	}
	else if (g_connection.sender_pid != info->si_pid)
	{
		return ;
	}
	i = 0;
	while (i < 8)
	{
		if (g_connection.received_bits[i] == -1)
		{
			g_connection.received_bits[i] = 0;
			break ;
		}
		++i;
	}
}

void	handle_sigusr2(int sig, siginfo_t *info, void *ucontext)
{
	int	i;

	sig = sig;
	ucontext = ucontext;
	if (g_connection.sender_pid == 0)
	{
		g_connection.sender_pid = info->si_pid;
	}
	else if (g_connection.sender_pid != info->si_pid)
	{
		return ;
	}
	i = 0;
	while (i < 8)
	{
		if (g_connection.received_bits[i] == -1)
		{
			g_connection.received_bits[i] = 1;
			break ;
		}
		++i;
	}
}

void	clear_received_bits(void)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_connection.received_bits[i] = -1;
		++i;
	}
}

void	wait_for_signal(void)
{
	char	c;
	int		i;

	while (1)
	{
		while (g_connection.received_bits[7] == -1)
			pause();
		c = 0;
		i = 0;
		while (i < 8)
		{
			c |= g_connection.received_bits[i] << (7 - i);
			++i;
		}
		if (c == '\x01')
		{
			kill(g_connection.sender_pid, SIGUSR1);
			clear_received_bits();
			g_connection.sender_pid = 0;
			ft_printf("\n");
			continue ;
		}
		ft_printf("%c", c);
		clear_received_bits();
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_sigusr1;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sa.sa_sigaction = handle_sigusr2;
	sigaction(SIGUSR2, &sa, NULL);
	g_connection.sender_pid = 0;
	clear_received_bits();
	ft_printf("PID: %d\n", getpid());
	wait_for_signal();
	return (0);
}
