/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:17:42 by ksudyn            #+#    #+#             */
/*   Updated: 2026/06/24 16:46:02 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*monitor_thread(void *arg)
{
	t_philo		*philo;
	t_rutine	*r;
	long long	time_since_meal;

	philo = (t_philo *)arg;
	r = philo->rutine;
	while (1)
	{
		sem_wait(r->sem_eat);
		time_since_meal = milliseconds_bonus() - philo->last_meal;
		sem_post(r->sem_eat);
		if (time_since_meal > r->time_die)
		{
			if (sem_trywait(r->sem_dead) == 0)
			{
				print_msg(philo, "is dead");
				exit(1);
			}
			else
				exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	t_rutine	*rutin;

	rutin = philo->rutine;
	if (rutin->sem_room)
		sem_wait(rutin->sem_room);
	sem_wait(rutin->sem_forks);
	print_msg(philo, "has taken a fork");
	sem_wait(rutin->sem_forks);
	print_msg(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	t_rutine	*rutin;

	rutin = philo->rutine;
	sem_post(rutin->sem_forks);
	sem_post(rutin->sem_forks);
	if (rutin->sem_room)
		sem_post(rutin->sem_room);
}

void	init_philo(t_philo *philo)
{
	t_rutine	*r;
	pthread_t	mon;

	r = philo->rutine;
	sem_wait(r->sem_eat);
	philo->last_meal = milliseconds_bonus();
	sem_post(r->sem_eat);
	if (pthread_create(&mon, NULL, monitor_thread, philo) != 0)
	{
		child_cleanup(r);
		exit(1);
	}
	pthread_detach(mon);
	if (philo->id_philo % 2 == 0)
		usleep(5000);
}

void	handle_single_philo(t_philo *philo)
{
	t_rutine	*rutin;

	rutin = philo->rutine;
	sem_wait(rutin->sem_forks);
	print_msg(philo, "has taken a fork");
	usleep(rutin->time_die * 1000);
	print_msg(philo, "is dead");
	child_cleanup(rutin);
	exit(1);
}
