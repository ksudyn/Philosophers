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

int	ft_parse(char **argv, t_rutine *rutine)
{
	int i;

	i = 1;
	while(argv[i])
	{
		if (check_number(argv[i]) == 1)
			return (1);
		i++;
	}
	rutine->num_philo = ft_atol(argv[1]);
	printf("%ld\n", rutine->num_philo);
	rutine->time_die = ft_atol(argv[2]);
	printf("%ld\n", rutine->time_die);
	rutine->time_eat = ft_atol(argv[3]);
	printf("%ld\n", rutine->time_eat);
	rutine->time_sleep = ft_atol(argv[4]);
	printf("%ld\n", rutine->time_sleep);
	if (i == 6)
	{
		rutine->turns = ft_atol(argv[5]);
		printf("%ld\n", rutine->turns);
		if (rutine->turns > INT_MAX || rutine->turns == 0)
				return (1);
	}
	if (rutine->num_philo > INT_MAX || rutine->num_philo == 0
			|| rutine->time_die > INT_MAX || rutine->time_die == 0
			|| rutine->time_eat > INT_MAX || rutine->time_eat == 0
			|| rutine->time_sleep > INT_MAX || rutine->time_sleep == 0)
			return (1);
	return (0);
}