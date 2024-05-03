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