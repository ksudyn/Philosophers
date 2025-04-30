/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:45:04 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/10 17:45:23 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//se escribe (void *philo) y dentro de la funcion se hace para que acceda al typedef strcut)
// si se escribe routine (t_philosophers *philo),
// se deberia de escribir en init_mutex se pasa esto pthread_create(&thread, NULL, routine, philo);
// y eso daría error de compilación. routine no es compatible con el tipo que espera

void    *routine(void *philo)
{
    t_philosophers	*phil;

	phil = (t_philosophers *)philo;
    if (phil->id_philo % 2 == 0)
		usleep(5000);
    while (phil->rutine->dead == 0 && (phil->rutine->turns == -1
			|| phil->rutine->turns < phil->rutine->total_turns))
    {
        if (is_dead(phil->rutine))
			break ;
        eat(phil);
        ft_sleep(phil);
        ft_think(phil);
    }
    pthread_mutex_lock(&phil->rutine->meal_full);
	phil->rutine->philosophers_full++;
	pthread_mutex_unlock(&phil->rutine->meal_full);
    return (NULL);
}
