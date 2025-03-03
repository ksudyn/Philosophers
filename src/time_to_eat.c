/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:10:50 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/27 17:10:52 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
int	eating(t_philosophers *philo, t_parse *parse)
{
	philo->act_time = set_time();

	if (philo->act_time - philo->last_eat > parse->time_die)
	{
		print_actions(parse, philo, "died");
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}

	if (parse->time_eat > parse->time_die)
	{
		print_actions(parse, philo, "is eating");
		sleeping(philo, parse->time_die, parse);
		print_actions(parse, philo, "died");
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}

	pthread_mutex_lock(&parse->mutex);
	philo->last_eat = set_time();
	pthread_mutex_unlock(&parse->mutex);

	print_actions(parse, philo, "is eating");
	sleeping(philo, parse->time_eat, parse);

	return (0);
}*/

