/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:01:38 by mmeier            #+#    #+#             */
/*   Updated: 2024/04/25 11:36:34 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	signal_handler(int signum, siginfo_t info, void *content)
{
	static int	byte;
	int			bit;
	static int	bit_count;

	bit = 0;
	if (signum == SIGUSR1)
		bit = 0;
	if (signum == SIGUSR2)
		bit = 1;
	byte = (byte << 1) + bit;
	bit_count++;
	if (bit_count == 8)
	{
		ft_printf("%c", (char)byte);
		byte = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	s_server;
	
	
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	s_server.sa_sigaction = signal_handler;
	sigemptyset(&s_server.sa_mask);
	s_server.sa_flags = SA_SIGINFO | SA_RESTART;
	while (1)
	{
		signal(SIGUSR2, signal_handler);
		signal(SIGUSR1, signal_handler);
		pause();
	}
	return (0);
}
