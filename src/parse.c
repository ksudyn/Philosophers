/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:03:36 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/28 15:03:54 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse(char **argv, t_philosophers)
{
	t_philosophers	*philo;
	int i;

	i = 1;
	while(argv[i])
	{
		if (check_number(argv[i]) == 1)
			return (1);
		i++;
	}

	philo->num_philo = ft_atol(argv[1]);
	philo->time_die = ft_atol(argv[2]);
	philo->time_eat = ft_atol(argv[3]);
	philo->time_sleep = ft_atol(argv[4]);
	if (i = 6)
	{
		philo->turns = ft_atol(argv[5]);
		if (philo->turns > INT_MAX || philo->turns == 0)
				return (1);
	}
	if (philo->num_philo > INT_MAX || philo->num_philo == 0
			|| philo->time_die > INT_MAX || philo->time_die == 0
			|| philo->time_eat > INT_MAX || philo->time_eat == 0
			|| philo->time_sleep > INT_MAX || philo->time_sleep == 0)
			return (1);
	return (0);
}