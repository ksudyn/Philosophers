/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:50:51 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/10 20:45:04 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_rutine	rutine;

	/* inicializar a cero */
	memset(&rutine, 0, sizeof(rutine));
	if (ft_parse_bonus(argc, argv, &rutine) != 0)
		return (ft_error_bonus(1));
	if (init_philos_array(&rutine) != 0)
		return (ft_error_bonus(2));
	if (init_semaphores(&rutine) != 0)
	{
		free_philos_array(&rutine);
		return (ft_error_bonus(3));
	}
	/* marcar tiempo de inicio común */
	rutine.start_time = milliseconds_bonus();
	if (spawn_philosophers(&rutine) != 0)
	{
		wait_and_cleanup(&rutine);
		return (ft_error_bonus(4));
	}
	/* padre espera y limpia */
	wait_and_cleanup(&rutine);
	return (0);
}

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./philo_bonus 5 800 200 200 3

// Explicación rápida de las opciones:

// --leak-check=full → comprueba todos los leaks.

// --show-leak-kinds=all → muestra todos los tipos de fuga (definitivas, posibles…).

// --track-origins=yes → ayuda a encontrar dónde se originan los punteros inválidos.

// --log-file=valgrind.log → guarda el resultado en un archivo para revisarlo cómodamente.

// Después puedes abrir el log con:

// less valgrind.log


// y buscar definitely lost o still reachable para ver si hay fugas.