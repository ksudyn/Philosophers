/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:10:21 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/27 17:10:23 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Funcion temporal de morir
void check_death(t_parse *philo)
{
    long current_time;
    int i;

    i = 0;
    while (i < philo->num_philo)
    {
        current_time = milliseconds();
        if (current_time - philo->philos[i].last_eat > philo->time_die)
        {
            printf("Filósofo %d ha muerto por no comer a tiempo 😱\n", philo->philos[i].philo);
            exit(0);  // Matar el programa
        }
        i++;
        usleep(1000);  // Revisa la muerte cada milisegundo
    }
}
