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

	if (argc != 5 && argc != 6)
		return (ft_error(1));
	if (ft_parse(argv, &rutine) == 1)
		return (ft_error(2));
	if (init_philosophers(&rutine))
		return (ft_error(3));
	init_forks(&rutine);
	rutine.start_rutine = milliseconds();
	//start_threads(t_table *table) de sergio, que hace?
	
	return (0);
}
// Main temporal a falta de añadir nuevas cosas para la rutina
// parseo bien hecho