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

void	philo_info(t_philosophers *philo, int id, t_rutine *rutine)
{
	rutine->dead = 0;
	philo->id_philo = id;
	rutine->status = 1;//se mantien en 1 si ningun filosofo muere al morir se pone en 0
	philo->act_time = milliseconds(); // Inicializa el tiempo actual
	philo->rutine = rutine;
	rutine->total_turns = 0;//el sexto argumento, es 0 si no hay o si aun no han llegado a ahacer tantas veces la rutina
	philo->left_fork = id - 1;
	philo->right_fork = id % rutine->num_philo;

	// printf("%i, rutine->dead \n", rutine->dead);
	// printf("%i, philo->id_philo \n", philo->id_philo);
	// printf("%i, rutine->status \n", rutine->status);
	// printf("%lli, philo->act_time \n", philo->act_time);
	// printf("%i, rutine->total_turns \n", rutine->total_turns);
	// printf("%i, philo->left_fork \n", philo->left_fork);
	// printf("%i philo->right_fork \n", philo->right_fork);
}

int	init_philosophers(t_rutine *rutine)
{
	int	i;

	i = 0;
	if(rutine->num_philo > 200 || rutine->num_philo <= 0)
		return(ft_error(6));
	rutine->philos = malloc(sizeof(t_philosophers) * rutine->num_philo);
	if (!rutine->philos)
		return (ft_error(3));
	while (i < rutine->num_philo)
	{
		if(pthread_mutex_init(&rutine->philos[i].mutex, NULL) != 0)
		{
			rutine->philos = NULL;
			return(ft_error(2));
		}
		philo_info(rutine->philos, i + 1, rutine);
		i++;
	}
	printf("se reserva la memoria\n");
	return (0);
}