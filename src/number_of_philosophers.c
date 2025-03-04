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
	
}