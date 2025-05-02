/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:12:22 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/30 17:12:24 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philosophers *philo)
{
	long 	start_sleep;

	start_sleep = milliseconds();
	if (philo_is_dead(philo->rutine))
		return ;
	if (philo->rutine->status != 0)
	{
		// Imprimir el estado de dormir con printf
		pthread_mutex_lock(&philo->rutine->print_lock);
		printf("%d is sleeping\n", philo->id_philo);
		pthread_mutex_unlock(&philo->rutine->print_lock);
		philo->rutine->status = 0; // Marca que el filósofo está durmiendo.
	}
	while (milliseconds() - start_sleep < philo->rutine->time_sleep)
	{
		if (philo_is_dead(philo->rutine))
			return ;
		usleep(100);
	}
}