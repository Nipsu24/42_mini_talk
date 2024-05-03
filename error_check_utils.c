/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariusmeier <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:44:39 by mariusmeier       #+#    #+#             */
/*   Updated: 2024/05/02 09:44:42 by mariusmeier      ###   ########.fr       */
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
		i++;
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
	if (code == 2)
	{
		ft_putstr_fd("ERROR.\nSIGUSR1 could not be configured :(\n", 2);
		exit (1);
	}
	if (code == 3)
	{
		ft_putstr_fd("ERROR.\nSIGUSR2 could not be configured :(\n", 2);
		exit (1);
	}
	return (0);
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
