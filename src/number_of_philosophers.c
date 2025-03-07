/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_philosophers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:10:04 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/27 17:10:05 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		philos(t_parse	*philo)
{
	int	i;

	philo->philos = malloc(sizeof(*philo->philos) * philo->num_philo);
	if (!philo->philos)
    return (ft_error(3));

	i = 0;
	  while (i < philo->num_philo) {
        philo->philos[i].philo = i + 1;  // Asigna el ID del filósofo
        philo->philos[i].parse = philo;  // Conecta con la estructura principal
        philo->philos[i].last_eat = 0;   // Inicializa el tiempo de última comida
        philo->philos[i].act_time = 0;   // Inicializa el tiempo actual

        // Inicializar el tenedor derecho
        pthread_mutex_init(&philo->philos[i].right_fork, NULL);

        // Asignar el tenedor izquierdo (el derecho del anterior)
        if (i == 0)
            philo->philos[i].left_fork = &philo->philos[philo->num_philo - 1].right_fork;
        else
            philo->philos[i].left_fork = &philo->philos[i - 1].right_fork;

        i++;
    }

    return (0);
}