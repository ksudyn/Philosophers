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

int	ft_parse(char **argv, t_parse *parse)
{
	int i;

	i = 1;
	while(argv[i])
	{
		if (check_number(argv[i]) == 1)
			return (1);
		i++;
	}

	parse->num_philo = ft_atol(argv[1]);
	printf("%ld\n", parse->num_philo);
	parse->time_die = ft_atol(argv[2]);
	printf("%ld\n", parse->time_die);
	parse->time_eat = ft_atol(argv[3]);
	printf("%ld\n", parse->time_eat);
	parse->time_sleep = ft_atol(argv[4]);
	printf("%ld\n", parse->time_sleep);
	if (i == 6)
	{
		parse->turns = ft_atol(argv[5]);
		printf("%ld\n", parse->turns);
		if (parse->turns > INT_MAX || parse->turns == 0)
				return (1);
	}
	if (parse->num_philo > INT_MAX || parse->num_philo == 0
			|| parse->time_die > INT_MAX || parse->time_die == 0
			|| parse->time_eat > INT_MAX || parse->time_eat == 0
			|| parse->time_sleep > INT_MAX || parse->time_sleep == 0)
			return (1);
	return (0);
}