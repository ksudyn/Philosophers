/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:45:04 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/10 17:45:23 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// se escribe (void *philo) y dentro de la funcion se hace para que acceda al typedef strcut)
// si se escribe routine (t_philosophers *philo),
// se deberia de escribir en init_mutex se pasa esto pthread_create(&thread, NULL, routine, philo);
// y eso daría error de compilación. routine no es compatible con el tipo que espera

void	precise_sleep(long duration)
{
	long	start;

	start = milliseconds();
	while ((milliseconds() - start) < duration)
		usleep(100);
}

void	*one_philo(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->rutine->fork[philo->left_fork]);
	print_message("has taken a fork", philo);
	precise_sleep(philo->rutine->time_die);
	pthread_mutex_lock(&philo->rutine->mutex_rutine);
	if (!philo->rutine->dead)
	{
		philo->rutine->dead = 1;
	}
	pthread_mutex_unlock(&philo->rutine->mutex_rutine);
	pthread_mutex_unlock(&philo->rutine->fork[philo->left_fork]);
	return (NULL);
}
//he metido mutex_rutine en lugar de la variable anterior que al final elimine

void	*routine(void *philo)
{
	t_philosophers	*phil;

	phil = (t_philosophers *)philo;
	if (phil->rutine->num_philo == 1)
		return one_philo(philo);
	if (phil->id_philo % 2 == 0)
		usleep(5000);
	while (!philo_is_dead(phil->rutine) && (phil->rutine->total_turns == -1
			|| phil->count_eaten < phil->rutine->total_turns))
	{
		if (philo_is_dead(phil->rutine))
			break ;
		ft_eat(phil);
		ft_sleep(phil);
		ft_think(phil);
	}
	if (phil->rutine->total_turns != -1
		&& phil->count_eaten >= phil->rutine->total_turns)
	{
		pthread_mutex_lock(&phil->rutine->meal_full);
		phil->rutine->philosophers_full++;
		pthread_mutex_unlock(&phil->rutine->meal_full);
	}
	return (NULL);
}

void	*routine_check(void *arg)
{
	t_rutine	*rutine;
	int			i;

	rutine = (t_rutine *)arg;
	while (1)
	{
		i = 0;
		while (i < rutine->num_philo)
		{
			if (!philo_is_alive(&rutine->philos[i]))
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&rutine->meal_full);
		if (rutine->total_turns != -1
			&& rutine->philosophers_full == rutine->num_philo)
		{
			pthread_mutex_unlock(&rutine->meal_full);
			return (NULL);
		}
		pthread_mutex_unlock(&rutine->meal_full);
		usleep(500);
			// Pequeño delay para evitar sobrecargar la CPU con el bucle
	}
	return (NULL);
}
