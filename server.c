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

static void	str_len_received(t_signal *sig)
{
	if (sig->bits == sizeof(int) * 8 && sig->int_compl == 0)
	{
		sig->int_compl = 1;
		ft_putstr_fd("Strlen received: ", 1);
		ft_putnbr_fd(sig->bytes, 1);
		ft_putstr_fd("\n", 1);
		sig->str = malloc((sig->bytes + 1) * sizeof(char));
		if (!sig->str)
		{
			ft_putstr_fd("Error\n. Malloc failure\n", 2);
			exit (1);
		}
		sig->str[sig->bytes] = '\0';
		sig->bits = 0;
	}
}

static void	str_received(t_signal *sig, pid_t pid)
{
	static int	i;
	
	(void)pid;
	if (sig->bits == sizeof(char) * 8 && sig->int_compl == 1)
	{
		sig->str[i] = sig->bytes;
		if (sig->str[i] != '\0')
			i++;
		if (sig->bytes == '\0')
		{
			ft_putstr_fd("message client:\n", 1);
			ft_putstr_fd(sig->str, 1);
			ft_putstr_fd("\n", 1);
			free(sig->str);
			sig->str = NULL;
			sig->int_compl = 0;
			i = 0;
			send_bit(pid, 1, 0);
		}
		sig->bits = 0;
	}
}

static void	store_bits_in_bytes(t_signal *sig, int int_chr_flag)
{
	if (int_chr_flag == 0)
	{
		sig->position =((sizeof(int) * 8) - 1) - sig->bits;
		sig->bitmask = 1 << sig->position;
		sig->bytes |= sig->bitmask;
		sig->position = 0;
		sig->bitmask = 0;
	}
	if (int_chr_flag == 1)
	{
		sig->position =((sizeof(char) * 8) - 1) - sig->bits;
		sig->bitmask = 1 << sig->position;
		sig->bytes |= sig->bitmask;
		sig->position = 0;
		sig->bitmask = 0;
	}
}

static void	signal_handler(int signum, siginfo_t *info, void *content)
{
	static t_signal	sig;
	static int		init;

	(void)content;
	(void)info;
	if (init == 0)
	{
		init_sig(&sig);
		init = 1;
	}
	if (sig.bits == 0)
		sig.bytes = 0;
	if (signum == SIGUSR2 && sig.int_compl == 0)
		store_bits_in_bytes(&sig, 0);
	else if (signum == SIGUSR2 && sig.int_compl == 1)
		store_bits_in_bytes(&sig, 1);
	sig.bits++;
	str_len_received(&sig);
	str_received(&sig, info->si_pid);
	send_bit(info->si_pid, 0, 0);
}
	
int	main(void)
{
	struct sigaction	s_server;
	
	sigemptyset(&s_server.sa_mask);
	s_server.sa_sigaction = signal_handler;
	s_server.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGUSR1, &s_server, NULL);
	if (sigaction < 0)
		error_invalid_input(2);
	sigaction(SIGUSR2, &s_server, NULL);
	if (sigaction < 0)
		error_invalid_input(3);
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	while (1)
	{
		pause();
	}
	return (0);
}
