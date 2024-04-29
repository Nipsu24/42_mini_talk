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

void	str_len_received(t_signal *sig)
{
	if ((sig->bits == sizeof(int) * 8) && !(sig->int_compl))
	{
		sig->int_compl = 1;
		sig->str = calloc(sig->bytes + 1, sizeof(char));
		if (!sig->str)
		{
			ft_putstr_fd("Error. Calloc failure\n", 2);
			exit (1);
		}
		sig->str[sig->bytes] = '\0';
		sig->bits = 0;
	}
}

void	str_received(t_signal *sig, pid_t pid)
{
	static int	i;
	(void)pid;

	if (sig->bits == sizeof(char) * 8 && sig->int_compl == 1)
	{
		sig->str[i] = sig->bytes;
		i++;
		if (sig->str[i] == '\0')
		{
			ft_putstr_fd("message client:\n", 1);
			ft_putstr_fd(sig->str, 1);
			ft_putstr_fd("\n", 1);
			free(sig->str);
			sig->str = NULL;
			sig->int_compl = 0;
			i = 0;
		}
		sig->bits = 0;
	}
}

void	signal_handler(int signum, siginfo_t *info, void *content)
{
	static t_signal	sig;
	int	position;
	int	bitmask;
	
	(void)content;
	(void)info;
	position = 0;
	bitmask = 0;
	sig.int_compl = 0;
	if (sig.bits == 0)
		sig.bytes = 0;
	if (signum == SIGUSR2 && !sig.int_compl)
	{
		position =((sizeof(int) * 8) - 1) - sig.bits;
		bitmask = 1 << position;
		sig.bytes |= bitmask;
		position = 0;
		bitmask = 0;
	}
	else if (signum == SIGUSR2 && sig.int_compl == 1)
	{
		position =((sizeof(char) * 8) - 1) - sig.bits;
		bitmask = 1 << position;
		sig.bytes |= bitmask;
		position = 0;
		bitmask = 0;
	}
	sig.bits++;
	str_len_received(&sig);
	str_received(&sig, info->si_pid);
}
	

int	main(void)
{
	struct sigaction	s_server;
	
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	sigemptyset(&s_server.sa_mask);
	s_server.sa_flags = SA_SIGINFO | SA_RESTART;
	s_server.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &s_server, NULL);
	if (sigaction < 0)
	{
		ft_putstr_fd("ERROR.\nSIGUSR1 could not be configured :(\n", 2);
		exit(1);
	}
	sigaction(SIGUSR2, &s_server, NULL);
	if (sigaction < 0)
	{
		ft_putstr_fd("ERROR.\nSIGUSR2 could not be configured :(\n", 2);
		exit(1);
	}
	while (1)
	{
		pause();
	}
	return (0);
}
