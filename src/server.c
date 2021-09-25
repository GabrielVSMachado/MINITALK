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

void	test(int s, siginfo_t *info_signal, void *cont)
{
	static int	i;
	static char	result;

	cont = (void *)cont;
	if (i <= 0 && result == 0)
		i = 7;
	if (s == SIGUSR1)
		result |= 1 << i;
	if (i == 0)
	{
		ft_printf("%c", result);
		result = 0;
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
