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

static struct s_pid_message	g_info;

void	send_signal(int pid)
{
	static int	i;
	static int	j;

	(void)pid;
	if (g_info.message[j])
	{
		if (((g_info.message[j] >> (7 - i++)) & 0b1))
			kill(g_info.pid, SIGUSR1);
		else
			kill(g_info.pid, SIGUSR2);
		if (i == 8)
		{
			i = 0;
			j++;
		}
	}
	else
		kill(g_info.pid, SIGUSR2);
}

static void	_quit(int sig)
{
	ft_bzero(&g_info, sizeof(struct s_pid_message));
	if (sig == SIGUSR2)
		exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	struct sigaction	quit;

	ft_bzero(&sa, sizeof(struct sigaction));
	ft_bzero(&quit, sizeof(struct sigaction));
	if (argc != 3)
		exit(EXIT_FAILURE);
	quit.sa_handler = _quit;
	sa.sa_handler = send_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &quit, NULL);
	g_info.pid = ft_atoi(argv[1]);
	g_info.message = argv[2];
	send_signal(g_info.pid);
	while (TRUE)
		pause();
	return (EXIT_SUCCESS);
}
