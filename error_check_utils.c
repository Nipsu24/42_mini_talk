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
