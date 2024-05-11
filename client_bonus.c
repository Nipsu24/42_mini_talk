/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:01:23 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/07 15:54:50 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk_bonus.h"

/*Converts char to its bit representation via bitshift operation.
  Starting from most significant bit, bits are shifted from left
  to right and every time, last bit resulting from this shift is 
  extracted via '&' operation. Bit is then given to send_bit function,
  additionally to pid and flag (1) (indication for pausing process in 
  send_bit function) */
static void	bitshift_ctb(pid_t pid, char c)
{
	int	i;
	int	binary[8];

	i = 0;
	while (i <= 7)
	{
		binary[i] = (c >> (7 - i)) & 1;
		if (binary[i] == 1)
			if(!(send_bit(pid, binary[i], 1)))
				exit (1);
		if (binary[i] == 0)
			if (!(send_bit(pid, binary[i], 1)))
				exit (1);
		i++;
	}
}

/*Converts str to its bit representation, see bitshift_ctb function*/
static void	str_to_bit(pid_t pid, char *str, int str_len)
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

/*Defines how client should react when receiving SIGUSR1/SIGUSR2 signal*/
static void	signal_handler(int signum)
{
	static int	count;

	if (signum == SIGUSR1)
	{
		ft_putstr_fd("[", 1);
		ft_putnbr_fd(count, 1);
		ft_putstr_fd("]: ", 1);
		ft_putstr_fd("Signal received from Server\n", 1);
		count++;
	}
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd("End of message received from Server\n", 1);
		exit(0);
	}
}

/*Installs signal handler for SIGUSR1 / SIGUSR2*/
static void	init_sigusr(struct sigaction *s_client)
{
	if (sigaction(SIGUSR1, s_client, NULL) < 0)
		error_message(2);
	if (sigaction(SIGUSR2, s_client, NULL) < 0)
		error_message(3);
}

/*Checks for valid args and whether pid only consists of digits. 
  Converts av[1] to pid_t with atop function. Assigns signal_handler
  function to sa_handler instance of sigaction struct "s_client". 
  init_sigusr function installs signal handler for SIGUSR1 / SIGUSR2 and  
  hanlder will be executed as defined by s_client struct (which holds the 
  information on signal_handler function).
  Sends strlen, av[2] and null-terminator via kill-function to server and waits
  for each bit sent for server response. */
int	main(int ac, char *av[])
{
	pid_t				pid;
	int					str_len;
	struct sigaction	s_client;

	if (ac != 3)
		return (error_message(1));
	else
	{
		if (not_only_digits(av[1]))
			return (error_message(0));
		pid = ft_atop(av[1]);
		if (!pid)
			return (error_message(0));
		sigemptyset(&s_client.sa_mask);
		s_client.sa_flags = SA_RESTART;
		s_client.sa_handler = signal_handler;
		init_sigusr(&s_client);
		str_len = ft_strlen(av[2]);
		bitshift_itb(pid, str_len);
		str_to_bit(pid, av[2], str_len);
		bitshift_ctb(pid, '\0');
	}
	return (0);
}
