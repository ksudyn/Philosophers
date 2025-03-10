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

int		init_philosophers(t_parse	*philo)
{
	int	i;

	philo->philos = malloc(sizeof(*philo->philos) * philo->num_philo);
	if (!philo->philos)
    return (ft_error(3));

	i = 0;
	  while (i < philo->num_philo) {
        philo->philos[i].philo = i + 1;  // Asigna el ID del filósofo
        philo->philos[i].parse = philo;  // Conecta con la estructura principal, esto permite que el filósofo pueda acceder a información globa
        philo->philos[i].last_eat = 0;   // Inicializa el tiempo de última comida
        philo->philos[i].act_time = 0;   // Inicializa el tiempo actual

        // Inicializar el tenedor derecho
        pthread_mutex_init(&philo->philos[i].right_fork, NULL);

        i++;
    }
    printf("las funciones philos funcionan 1\n");
    return (0);
}

void    assign_forks(t_parse *philo)
{
    int i;

    i = 0;
    while(i < philo->num_philo)
    {
        if(i == 0)
            philo->philos[i].left_fork = &philo->philos[philo->num_philo - 1].right_fork;
        else
            philo->philos[i].left_fork = &philo->philos[i - 1].right_fork;
        i++;
    }
    printf("las funciones philos funcionan 2\n");
}

int philos(t_parse *philo)
{
    if (init_philosophers(philo) != 0)
        return (1);
    assign_forks(philo);
    printf("las funciones philos funcionan 3\n");
    return (0);
}