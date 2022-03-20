/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:27:36 by anonymous         #+#    #+#             */
/*   Updated: 2022/03/14 21:48:55 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_usr(int signum, siginfo_t *info, void *ptr)
{
	static sig_atomic_t	shift;
	static char			ch;
	static int			pid;

	(void)ptr;
	if (pid != info->si_pid)
	{
		shift = 0;
		ch = 0;
	}
	if (signum == SIGUSR1)
	{
		ch ^= 1 << shift;
		shift++;
	}
	else
		shift++;
	if (shift == 8)
	{
		write(1, &ch, 1);
		ch = 0;
		shift = 0;
	}
	pid = info->si_pid;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act_usr;
	sigset_t			m_sign;

	ft_printf("%d\n", getpid());
	sigemptyset(&m_sign);
	sigaddset(&m_sign, SIGINT);
	sigaddset(&m_sign, SIGUSR1);
	sigaddset(&m_sign, SIGUSR2);
	act_usr.sa_mask = m_sign;
	act_usr.sa_flags = SA_SIGINFO;
	act_usr.sa_sigaction = &handler_usr;
	while (1)
	{
		if (sigaction(SIGUSR1, &act_usr, NULL) == -1)
		{
			write(1, "SIGUSR1 Error\n", 14);
			return (1);
		}
		if (sigaction(SIGUSR2, &act_usr, NULL) == -1)
		{
			write(1, "SIGUSR2 Error\n", 14);
			return (1);
		}
	}
	return (0);
}
