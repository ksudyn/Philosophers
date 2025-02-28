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

int	parse(char **argv, t_philosophers *philo)
{
	int i;

	i = 1;
	while(argv[i])
	{
		if (check_number(argv[i]) == 1)
			return (1);
		i++;
	}

	philo->num_philo = ft_atol(argv[1]);
	printf("%d\n", philo->num_philo);
	philo->time_die = ft_atol(argv[2]);
	printf("%ld\n", philo->time_die);
	philo->time_eat = ft_atol(argv[3]);
	printf("%ld\n", philo->time_eat);
	philo->time_sleep = ft_atol(argv[4]);
	printf("%ld\n", philo->time_sleep);
	if (i == 6)
	{
		philo->turns = ft_atol(argv[5]);
		printf("%ld\n", philo->turns);
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