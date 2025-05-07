/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:39:57 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/10 18:40:22 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_think(t_philosophers *philo)
{
	if (philo_is_dead(philo->rutine))
		return ;
	if (philo->rutine->status != 2)
	{
		if (philo_is_dead(philo->rutine))
			return ;
		print_message("is thinking", philo);
		pthread_mutex_lock(&philo->rutine->mutex_rutine);
		philo->rutine->status = 2;
		usleep(1000);
	}
	pthread_mutex_unlock(&philo->rutine->mutex_rutine);
}
