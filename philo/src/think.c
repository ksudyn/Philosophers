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
	int	did_lock;

	did_lock = 0;
	if (philo_is_dead(philo->rutine))
		return ;
	if (philo->rutine->status != 2)
	{
		if (philo_is_dead(philo->rutine))
			return ;
		print_message("is thinking", philo);
		pthread_mutex_lock(&philo->rutine->mutex_rutine);
		did_lock = 1;
		philo->rutine->status = 2;
		usleep(1000);
	}
	if(did_lock)
		pthread_mutex_unlock(&philo->rutine->mutex_rutine);
}

//en esta funcion he metido el did_lock para que no desbloque si no entra en la funcion
// funciona mejor esto que meter todo dentro de la funncion, ppero valdria igua
//asui solo de desbloquea si se bloquea antes 
