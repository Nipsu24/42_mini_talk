/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:47:00 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/05/03 14:47:03 by mariusmeier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	bitshift_itb(pid_t pid, int nbr)
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
void	send_bit(pid_t pid, char bit, char pause_sig)
{
	if (bit == 0)
	{
		kill(pid, SIGUSR1);
		if (kill < 0)
		{
			ft_putstr_fd("Error\n. Bit could not be sent\n", 1);
			exit (1);
		}	
	}
	else if (bit == 1)
	{
		kill(pid, SIGUSR2);
		if (kill < 0)
		{
			ft_putstr_fd("Error\n. Bit could not be sent\n", 1);
			exit (1);
		}	
	}
	if (pause_sig != 0)
		pause();
}

void	init_sig(t_signal *sig)
{
	sig->bits = 0;
	sig->bytes = 0;
	sig->int_compl = 0;
	sig->str = NULL;
	sig->position = 0;
	sig->bitmask = 0;
}

static pid_t	ft_convertno(const char *str, int n, int minus)
{
	long int	number;
	long int	prenbr;

	prenbr = 0;
	number = 0;
	while (str[n] >= 48 && str[n] <= 57)
	{
		number *= 10;
		number += str[n] - 48;
		n++;
		if (prenbr > number)
		{
			if (minus > 0)
				return (0);
			else
				return (-1);
		}
		prenbr = number;
	}
	return (number);
}

pid_t	ft_atop(const char *str)
{
	int		i;
	int		minus;
	pid_t	number;
	int		plus;

	minus = 0;
	plus = 0;
	number = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		if (str[i] == '+')
			plus++;
		if (minus + plus > 1)
			return (0);
		i++;
	}
	number = ft_convertno(str, i, minus);
	if (minus == 1)
		return (-number);
	return (number);
}
