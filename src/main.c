/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:33:35 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/27 18:33:37 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philosophers philo;

	if (argc != 5 && argc != 6)
		return (ft_error(1));
	if (parse(argv, &philo) == 1)
		return (ft_error(2));
}
