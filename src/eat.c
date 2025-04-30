/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:12:13 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/30 17:12:14 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eat(t_philosophers *philo)
{
    // Bloquea los tenedores según el ID del filósofo (usando la función lock_forks)
    lock_forks(philo);

    // Verifica si el filósofo está muerto, si es así, sale de la función
    if (is_dead(philo->rutine))
    {
        unlock_forks(philo);  // Desbloquea los tenedores antes de salir
        return ;
    }

    // Establece el estado del filósofo a "comiendo"
    philo->rutine->status = 1;

    // Imprime el mensaje de que el filósofo está comiendo
    pthread_mutex_lock(&philo->rutine->print_lock);
    printf("%ld %d is eating\n", milliseconds(), philo->id_philo);
    pthread_mutex_unlock(&philo->rutine->print_lock);

    // Actualiza el número de comidas (incrementa el contador)
    //update_meal(philo);

    // Simula el tiempo que el filósofo tarda en comer
    usleep(philo->rutine->time_eat * 1000);

    // Después de comer, desbloquea los tenedores
    unlock_forks(philo);

    // Imprime un mensaje indicando que el filósofo ha terminado de comer
    pthread_mutex_lock(&philo->rutine->print_lock);
    printf("%ld %d has finished eating\n", milliseconds(), philo->id_philo);
    pthread_mutex_unlock(&philo->rutine->print_lock);
}
