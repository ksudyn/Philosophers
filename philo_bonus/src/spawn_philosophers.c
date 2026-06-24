/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:12:34 by ksudyn            #+#    #+#             */
/*   Updated: 2026/06/24 16:37:41 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static pid_t	spawn_child(t_rutine *r, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		return (-1);
	}
	else if (pid == 0)
	{
		r->philos[index].pid = getpid();
		philo_routine(&r->philos[index]);
		exit(0);
	}
	else
	{
		r->philos[index].pid = pid;
		r->pids[index] = pid;
	}
	return (pid);
}

int	spawn_philosophers(t_rutine *r)
{
	int	i;
	int	j;

	if (!r || !r->philos || !r->pids)
		return (1);
	i = 0;
	while (i < r->num_philo)
	{
		if (spawn_child(r, i) < 0)
		{
			j = 0;
			while (j < i)
			{
				if (r->philos[j].pid > 0)
					kill(r->philos[j].pid, SIGKILL);
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
