/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:32:33 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/09 20:35:53 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"


void	free_philos_array(t_rutine *rutine)
{
	if (!rutine)
		return ;
	if (rutine->philos)
		free(rutine->philos);
	if (rutine->pids)
		free(rutine->pids);
	rutine->philos = NULL;
	rutine->pids = NULL;
}
/* imprimir protegido */
void	print_msg(t_philo *philo, const char *msg)
{
	long long	ts;

	sem_wait(philo->rutine->sem_print);
	ts = milliseconds_bonus() - philo->rutine->start_time;
	printf("%lld %d %s\n", ts, philo->id_philo, msg);
	sem_post(philo->rutine->sem_print);
}

static void	start_child(t_philo *philo)
{
	/* en el hijo: ejecutar rutina y exit */
	philo->rutine->start_time = philo->rutine->start_time; /* no hace nada,
		sólo seguridad */
	philo_routine(philo);
	/* nunca debe volver; philo_routine deberá llamar exit(0/1) */
	exit(0);
}

int	create_processes(t_rutine *rutine)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < rutine->num_philo)
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			/* proceso hijo */
			rutine->philos[i].pid = getpid();
			start_child(&rutine->philos[i]);
			/* no llega */
		}
		/* padre */
		rutine->philos[i].pid = pid;
		rutine->pids[i] = pid;
		i++;
	}
	return (0);
}
