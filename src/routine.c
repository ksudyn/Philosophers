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

//Funcion de rutina donde se mete todas las acciones
void *philo_routine(void *arg)
{
    t_philosophers *philo = (t_philosophers *)arg;

    while (1)
    {
        think(philo);         // El filósofo piensa
        eat(philo);           // El filósofo come
        sleep_philo(philo);   // El filósofo duerme
    }

    return NULL;
}

