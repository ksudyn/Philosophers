/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:12:13 by ksudyn            #+#    #+#             */
/*   Updated: 2026/06/24 16:52:40 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_meal(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->mutex_philo);
	philo->act_time = milliseconds();
	philo->count_eaten++;
	pthread_mutex_unlock(&philo->mutex_philo);
}

static int	eating_loop(t_philosophers *philo, long start)
{
	while (milliseconds() - start < philo->rutine->time_eat)
	{
		if (!philo_is_dead(philo->rutine))
		{
			unlock_forks(philo);
			return (0);
		}
		usleep(100);
	}
	return (1);
}

void	ft_eat(t_philosophers *philo)
{
	long	start;

	if (!lock_forks(philo))
		return ;
	if (philo_is_dead(philo->rutine))
	{
		unlock_forks(philo);
		return ;
	}
	pthread_mutex_lock(&philo->rutine->mutex_rutine);
	philo->rutine->status = 1;
	pthread_mutex_unlock(&philo->rutine->mutex_rutine);
	print_message("is eating", philo);
	update_meal(philo);
	start = milliseconds();
	if (!eating_loop(philo, start))
		return ;
	unlock_forks(philo);
	if (philo_is_dead(philo->rutine))
		return ;
	print_message("has finished eating", philo);
}
