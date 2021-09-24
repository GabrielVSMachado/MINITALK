/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 18:44:13 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/09/18 18:44:13 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_signal(int pid, char *binary)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (binary[i] == '1')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(2);
	}
}

static void	eval_message(int pid, char *message)
{
	char	*binary;
	int		i;

	i = 0;
	while (message[i])
	{
		binary = ft_utoa_base(message[i], "01");
		send_signal(pid, binary);
		i++;
		free(binary);
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
		exit(EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	eval_message(pid, argv[2]);
	return (EXIT_SUCCESS);
}
