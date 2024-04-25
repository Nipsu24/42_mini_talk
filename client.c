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

int	not_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

int	error_invalid_input(int code)
{
	if (code == 0)
	{
		ft_putstr_fd("ERROR.\nInvalid server-pid :(\n", 2);
		return (-1);
	}
	if (code == 1)
	{
		ft_putstr_fd("ERROR.\nInvalid input :(\n", 2);
		return (-1);
	}
	return (0);
}

void	bitshift_ctb(char c, int pid)
{
	int	i;

	i = 0;
	int	binary[8];
	while (i <= 7)
	{
		binary[i] = (c >> (7 - i)) & 1;
		if (binary[i] == 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i++;
		usleep(300);
	}
}

void	char_to_bit(int pid, char *str, int str_len)
{
	int	i;

	i = 0;
	while (str_len > 0)
	{
		bitshift_ctb(str[i], pid);
		i++;
		str_len--;
	}
}

int	main(int ac, char *av[])
{
	int		pid;
	int		str_len;

	pid = 0;
	str_len = 0;
	if (ac != 3)
		return (error_invalid_input(1));
	if (ac == 3)
	{
		if (not_only_digits(av[1]))
			return (error_invalid_input(0));
		pid = ft_atoi(av[1]);
		if (!pid)
			return (error_invalid_input(0));
		str_len = ft_strlen(av[2]);
		char_to_bit(pid, av[2], str_len);
	}
	return (0);
}
