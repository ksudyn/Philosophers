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
	t_parse philo;
	int i;
	if (argc != 5 && argc != 6)
		return (ft_error(1));
	if (parse(argv, &philo) == 1)
		return (ft_error(2));
	if (philos(&philo) != 0)
        return (ft_error(3));
	
	i = 0;
	while (i < philo.num_philo)
    {
        if (pthread_create(&philo.philos[i].thread_id, NULL, philo_routine, &philo.philos[i]) != 0)
            return (ft_error(4));
        pthread_detach(philo.philos[i].thread_id);  // Desacoplar el hilo
        i++;
    }

	sleep(3); 
	return (0);
}
//Main temporal a falta de añadir nuevas cosas para la rutina
//parseo bien hecho