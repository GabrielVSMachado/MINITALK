/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 21:55:26 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/09/23 21:55:26 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

struct s_pid_message
{
	char	*message;
	int		pid;
};

typedef struct s_str_tmp
{
	char	*to_join;
	char	*joined;
	char	c_to_str[2];
}	t_str_tmp;

#endif
