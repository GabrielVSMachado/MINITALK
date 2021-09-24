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

void	test(int s)
{
	static int	i;
	static char	result;

	if (s == SIGUSR1)
	{
		if (i <= 0 && result == 0)
			i = 6;
		result |= 1 << i;
	}
	if (i == 0)
	{
		ft_printf("%c", result);
		result = 0;
	}
	i--;
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &test;
	ft_printf("PID: %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (TRUE)
		;
	return (EXIT_SUCCESS);
}
