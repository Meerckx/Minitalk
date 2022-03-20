/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:24:06 by anonymous         #+#    #+#             */
/*   Updated: 2022/03/14 21:56:36 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

sig_atomic_t	g_flag = 0;

int	is_valid(int argc, char **argv)
{
	int	i;

	if (argc != 3)
		return (0);
	i = 0;
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
			return (0);
		i++;
	}
	return (1);
}

void	receiving(int signal)
{
	if (signal == SIGUSR1)
		write(1, "Signal received\n", 16);
	g_flag = 1;
}

void	sig_handler(int pid, int ch)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (ch & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		ch >>= 1;
		i++;
		while (g_flag != 1)
		{
		}
		g_flag = 0;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	g_flag = 0;
	if (!is_valid(argc, argv))
	{
		write(1, "Error! Enter: ./client [PID] [STRING]\n", 38);
		exit(1);
	}
	signal(SIGUSR1, receiving);
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		sig_handler(pid, argv[2][i]);
		i++;
	}
	sig_handler(pid, argv[2][i]);
	return (0);
}
