/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 19:43:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/09/18 19:43:52 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	join_characters(t_process *msn, char character)
{
	if (!msn->first_time)
	{
		msn->to_join = ft_strdup("");
		msn->first_time = 1;
	}
	else
		msn->to_join = msn->joined;
	msn->c_to_str[0] = character;
	msn->joined = ft_strjoin(msn->to_join, msn->c_to_str);
	free(msn->to_join);
	msn->to_join = NULL;
}

static void	finish_communication(t_process *msn, int pid)
{
	ft_printf("%s", msn->joined);
	free(msn->joined);
	ft_bzero(msn, sizeof(t_process));
	kill(pid, SIGUSR2);
}

void	test(int s, siginfo_t *info_signal, void *cont)
{
	static int			i;
	static char			result;
	static t_process	msn;

	cont = (void *)cont;
	if (i <= 0 && msn.process == FALSE)
	{
		i = 7;
		msn.process = TRUE;
	}
	if (s == SIGUSR1)
		result |= 1 << i;
	if (i == 0)
	{
		if (result == '\0')
			finish_communication(&msn, info_signal->si_pid);
		else
			join_characters(&msn, result);
		result = 0;
		msn.process = FALSE;
	}
	i--;
	kill(info_signal->si_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &test;
	ft_printf("PID: %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (TRUE)
		;
	return (EXIT_SUCCESS);
}
