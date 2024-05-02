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
			kill(pid, SIGUSR2);
		if (binary[i] == 0)
			kill(pid, SIGUSR1);
		i++;
		usleep(300);
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
			kill(pid, SIGUSR2);
		if (binary[i] == 0)
			kill(pid, SIGUSR1);
		i++;
		usleep(300);
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

int	main(int ac, char *av[])
{
	pid_t	pid;
	int		str_len;

	pid = 0;
	str_len = 0;
	if (ac != 3)
		return (error_invalid_input(1));
	if (ac == 3)
	{
		if (not_only_digits(av[1]))
			return (error_invalid_input(0));
		pid = ft_atop(av[1]);
		if (!pid)
			return (error_invalid_input(0));
		str_len = ft_strlen(av[2]);
		bitshift_itb(pid, str_len);
		char_to_bit(pid, av[2], str_len);
		bitshift_ctb(pid, '\0');
	}
	return (0);
}
