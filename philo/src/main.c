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
	t_rutine	rutine;
	int			i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (ft_error(1));
	if (ft_parse(argv, &rutine) == 1)
		return (ft_error(2));
	if (init_philosophers(&rutine) == 1)
		return (ft_error(3));
	init_forks(&rutine);
	rutine.start_rutine = milliseconds();
	init_mutex(&rutine);
	pthread_create(&rutine.chechk_routine, NULL, routine_check, &rutine);
	while (i < rutine.num_philo)
	{
		pthread_join(rutine.philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(rutine.chechk_routine, NULL);
	destroy_mutex(&rutine);
	return (0);
}

// Main temporal a falta de añadir nuevas cosas para la rutina
// parseo bien hecho

// pthread_create			Crea un hilo nuevo y le asigna una función (routine_check, philo_routine, etc.).
// pthread_join				Espera que un hilo termine antes de seguir.
// pthread_mutex_init		Inicializa un mutex.
// pthread_mutex_destroy	Libera un mutex.
// pthread_mutex_lock		Bloquea un mutex (espera si otro hilo lo tiene).
// pthread_mutex_unlock		Desbloquea un mutex.
// usleep					Suspende la ejecución por microsegundos.
// malloc / free			Asignación y liberación de memoria dinámica.

// probar esto 
// valgrind --tool=helgrind ./philo