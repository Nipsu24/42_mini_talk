/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:01:38 by mmeier            #+#    #+#             */
/*   Updated: 2024/04/22 16:13:37 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	signal_handler(int signum)
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
// {
// 	static char	*byte;
// 	static int	i;
// 	int			zero;
// 	int			one;
// 	int			j;

// 	zero = 0;
// 	one = 1;
// 	byte = 0;
// 	i = 0;
// 	j = 0;
// 	if (signum == SIGUSR1)
// 	{
// 		if (!byte)
// 			byte = ft_strdup(ft_itoa(zero));
// 		else
// 			byte = ft_strjoin(byte, ft_itoa(zero));
// 		i++;
// 	}
// 	else if (signum == SIGUSR2)
// 	{
// 		if (!byte)
// 			byte = ft_strdup(ft_itoa(one));
// 		else
// 			byte = ft_strjoin(byte, ft_itoa(one));
// 		i++;
// 	}
// 	if (i == 7)
// 	{
// 		while (byte[j])
// 		{
// 			byte[j]
// 			j++;
// 		}
// 		ft_printf("%c", byte);
// 		i = 0;
// 	}
// }

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		signal(SIGUSR2, signal_handler);
		signal(SIGUSR1, signal_handler);
		pause();
	}
	return (0);
}
