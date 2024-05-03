/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:01:23 by mmeier            #+#    #+#             */
/*   Updated: 2024/04/25 11:18:57 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

static void	bitshift_ctb(pid_t pid, char c)
{
	int	i;

	i = 0;
	int	binary[8];
	while (i <= 7)
	{
		binary[i] = (c >> (7 - i)) & 1;
		if (binary[i] == 1)
			send_bit(pid, binary[i], 1);
		if (binary[i] == 0)
			send_bit(pid, binary[i], 1);
		i++;
	}
}

static void	bitshift_itb(pid_t pid, int nbr)
{
	int	i;

	i = 0;
	int	binary[32];
	while (i <= 31)
	{
		binary[i] = (nbr >> (31 - i)) & 1;
		if (binary[i] == 1)
			send_bit(pid, binary[i], 1);
		if (binary[i] == 0)
			send_bit(pid, binary[i], 1);
		i++;
	}
}

static void	char_to_bit(pid_t pid, char *str, int str_len)
{
	int	i;

	i = 0;
	while (str_len > 0)
	{
		bitshift_ctb(pid, str[i]);
		i++;
		str_len--;
	}
}

static void	client_handler(int signum)
{
	if (signum == SIGUSR1)
		ft_putstr_fd("Signal received from Server\n", 1);
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd("End of message received from Server\n", 1);
		exit(0);
	}
}

int	main(int ac, char *av[])
{
	pid_t				pid;
	int					str_len;
	struct sigaction	s_client;

	pid = 0;
	str_len = 0;
	if (ac != 3)
		return (error_invalid_input(1));
	else
	{
		if (not_only_digits(av[1]))
			return (error_invalid_input(0));
		pid = ft_atop(av[1]);
		if (!pid)
			return (error_invalid_input(0));
		sigemptyset(&s_client.sa_mask);
		s_client.sa_flags = SA_RESTART;
		s_client.sa_handler = client_handler;
		sigaction(SIGUSR1, &s_client, NULL);
		if (sigaction < 0)
			error_invalid_input(2);
		sigaction(SIGUSR2, &s_client, NULL);
		if (sigaction < 0)
			error_invalid_input(3);
		str_len = ft_strlen(av[2]);
		bitshift_itb(pid, str_len);
		char_to_bit(pid, av[2], str_len);
		bitshift_ctb(pid, '\0');
	}
	return (0);
}
