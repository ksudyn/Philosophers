/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_philosophers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:10:04 by ksudyn            #+#    #+#             */
/*   Updated: 2026/06/24 16:59:15 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_info(t_philosophers *philo, int id, t_rutine *rutine)
{
	philo->id_philo = id;
	philo->act_time = milliseconds();
	philo->rutine = rutine;
	philo->left_fork = id - 1;
	philo->right_fork = id % rutine->num_philo;
	philo->count_eaten = 0;
}

int	init_philosophers(t_rutine *rutine)
{
	int	i;

	i = 0;
	if (rutine->num_philo > 200 || rutine->num_philo <= 0)
		return (ft_error(6));
	rutine->philosophers_full = 0;
	rutine->status = 1;
	rutine->dead = 0;
	rutine->philos = malloc(sizeof(t_philosophers) * rutine->num_philo);
	if (!rutine->philos)
		return (ft_error(3));
	while (i < rutine->num_philo)
	{
		if (pthread_mutex_init(&rutine->philos[i].mutex_philo, NULL) != 0)
		{
			rutine->philos = NULL;
			return (ft_error(2));
		}
		philo_info(&rutine->philos[i], i + 1, rutine);
		i++;
	}
	return (0);
}
