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

void	philo_info(t_philosophers *philo, int id, t_parse *parse)
{
	philo->parse->dead = 0;
	philo->id_philo = id;
	philo->parse->status = 1;
	philo->act_time = milliseconds(); // Inicializa el tiempo actual
	philo->parse = parse;
	parse->total_turns = 0;
	philo->left_fork = id - 1;
	philo->right_fork = id % parse->num_philo;
}

int	init_philosophers(t_parse *parse)
{
	int	i;

	parse->philos = malloc(sizeof(t_philosophers) * parse->num_philo);
	if (!parse->philos)
		return (ft_error(3));
	i = 0;
	while (i < parse->num_philo)
	{
		pthread_mutex_init(&parse->philos[i].mutex, NULL);
		philo_info(parse->philos, i + 1, parse);
		i++;
	}
	printf("se reserva la memoria\n");
	return (0);
}