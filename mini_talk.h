/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_talk.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:08 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/06 15:55:46 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TALK_H
# define MINI_TALK_H

# include "./libft/libft.h"
# include <signal.h>

typedef struct s_signal
{
	int		bits;
	int		bytes;
	int		int_compl;
	char	*str;
	int		position;
	int		bitmask;
}				t_signal;

int		not_only_digits(char *str);
int		error_message(int code);
pid_t	ft_atop(const char *str);
void	send_bit(pid_t pid, int bit, int pause_sig);
void	init_sig(t_signal *sig);
void	bitshift_itb(pid_t pid, int nbr);
#endif