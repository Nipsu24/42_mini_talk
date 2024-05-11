/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:47:00 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/05/08 16:39:54 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk_bonus.h"

/*Converts int to its bit representation via bitshift operation.
  Starting from most significant bit, bits are shifted from left
  to right and every time, last bit resulting from this shift is 
  extracted via '&' operation. Bit is then given to send_bit function,
  additionally to pid and flag (1) (indication for pausing process in 
  send_bit function) */
void	bitshift_itb(pid_t pid, int nbr)
{
	int	i;
	int	binary[32];

	i = 0;
	while (i <= 31)
	{
		binary[i] = (nbr >> (31 - i)) & 1;
		if (binary[i] == 1)
			if (!(send_bit(pid, binary[i], 1)))
				exit (1);
		if (binary[i] == 0)
			if (!(send_bit(pid, binary[i], 1)))
				exit (1);
		i++;
	}
}

/*pause_sig = 0 & SIGUSR1 (bit = 0) sent by server each time after 
  receiving a "bit" (SIGUSR1/SIGUSR2 signal) from client (client always
  sends pause_sig = 1 for pausing).
  pause_sig = 0 & SIGUSR2 (bit = 1) sent by server after receiving 
  complete *str.*/
int	send_bit(pid_t pid, int bit, int pause_sig)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) < 0)
		{
			ft_putstr_fd("Error.\nBit could not be sent.\n", 1);
			return (0);
		}
	}
	else if (bit == 1)
	{
		if (kill(pid, SIGUSR2) < 0)
		{
			ft_putstr_fd("Error.\nBit could not be sent.\n", 1);
			return (0);
		}
	}
	if (pause_sig != 0)
		pause();
	return (1);
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
