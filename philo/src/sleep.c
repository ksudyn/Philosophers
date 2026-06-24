/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:12:22 by ksudyn            #+#    #+#             */
/*   Updated: 2026/06/24 16:59:10 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philosophers *philo)
{
	long	start_sleep;
	int		did_lock;

	did_lock = 0;
	start_sleep = milliseconds();
	if (philo_is_dead(philo->rutine))
		return ;
	if (philo->rutine->status != 0)
	{
		if (philo_is_dead(philo->rutine))
			return ;
		print_message("is sleeping", philo);
		pthread_mutex_lock(&philo->rutine->mutex_rutine);
		did_lock = 1;
		philo->rutine->status = 0;
	}
	if (did_lock)
		pthread_mutex_unlock(&philo->rutine->mutex_rutine);
	while (milliseconds() - start_sleep < philo->rutine->time_sleep)
	{
		if (philo_is_dead(philo->rutine))
			return ;
		usleep(100);
	}
}
