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
		pthread_mutex_lock(&philo->rutine->mutex_rutine);//mutex para status
		did_lock = 1;
		philo->rutine->status = 0; // Marca que el filósofo está durmiendo.
	}
	if(did_lock)
		pthread_mutex_unlock(&philo->rutine->mutex_rutine);

	while (milliseconds() - start_sleep < philo->rutine->time_sleep)
	{
		if (philo_is_dead(philo->rutine))
			return ;
		usleep(100);
	}
}

//en esta funcion he metido el did_lock para que no desbloque si no entra en la funcion
// funciona mejor esto que meter todo dentro de la funncion, ppero valdria igua
//asui solo de desbloquea si se bloquea antes 