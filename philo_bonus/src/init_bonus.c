/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:21:37 by ksudyn            #+#    #+#             */
/*   Updated: 2026/06/24 16:49:27 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	init_philos_array(t_rutine *rutine)
{
	int	i;

	if (!rutine)
		return (1);
	if (rutine->num_philo <= 0 || rutine->num_philo > 200)
		return (1);
	rutine->philos = malloc(sizeof(t_philo) * rutine->num_philo);
	rutine->pids = malloc(sizeof(pid_t) * rutine->num_philo);
	if (!rutine->philos || !rutine->pids)
	{
		free_philos_array(rutine);
		return (1);
	}
	i = 0;
	while (i < rutine->num_philo)
	{
		rutine->philos[i].id_philo = i + 1;
		rutine->philos[i].last_meal = milliseconds_bonus();
		rutine->philos[i].count_eaten = 0;
		rutine->philos[i].pid = -1;
		rutine->philos[i].rutine = rutine;
		i++;
	}
	return (0);
}

static int	init_sem_dead(t_rutine *r)
{
	sem_unlink("/philo_sem_dead");
	r->sem_dead = sem_open("/philo_sem_dead", O_CREAT | O_EXCL, 0644, 1);
	return (r->sem_dead == SEM_FAILED);
}

static int	init_basic_sems(t_rutine *r)
{
	sem_unlink("/philo_sem_print");
	sem_unlink("/philo_sem_forks");
	sem_unlink("/philo_sem_eat");
	r->sem_print = sem_open("/philo_sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (r->sem_print == SEM_FAILED)
		return (1);
	r->sem_forks = sem_open("/philo_sem_forks", O_CREAT | O_EXCL, 0644,
			r->num_philo);
	if (r->sem_forks == SEM_FAILED)
		return (1);
	r->sem_eat = sem_open("/philo_sem_eat", O_CREAT | O_EXCL, 0644, 1);
	if (r->sem_eat == SEM_FAILED)
		return (1);
	return (0);
}

static int	init_sem_room(t_rutine *r)
{
	if (r->num_philo > 1)
	{
		r->sem_room = sem_open("/philo_sem_room", O_CREAT | O_EXCL, 0644,
				r->num_philo - 1);
		if (r->sem_room == SEM_FAILED)
			r->sem_room = NULL;
	}
	else
		r->sem_room = NULL;
	return (0);
}

int	init_semaphores(t_rutine *r)
{
	if (init_sem_dead(r))
		return (1);
	if (init_basic_sems(r))
		return (1);
	init_sem_room(r);
	return (0);
}
