/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:45:47 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/27 18:45:50 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	milliseconds(void)
{
	struct timeval	time;
	long long		milliseconds;


	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
} // transforma el timepo a miliseguncos para que sea mas preciso
void	init_mutex(t_rutine *rutine)
{
	int				i;
	int				thread;

	pthread_mutex_init(&rutine->print_lock, NULL);
	pthread_mutex_init(&rutine->mutex_rutine, NULL);
	pthread_mutex_init(&rutine->meal_full, NULL);
	i = 0;
	while (i < rutine->num_philo)
	{
		thread = pthread_create(&rutine->philos[i].thread_id, NULL, routine,
				&rutine->philos[i]);
		if (thread != 0)
			printf("Error creating thread %d: %d\n", i, ft_error(5));
		i++;
	}
}
//elimine la varibale chek_dead del mutex_init

// Comprueba si un filósofo sigue vivo según el tiempo desde su última comida.
int	philo_is_alive(t_philosophers *philo)
{
	int	alive;

	alive = 1;
	// Bloquea el acceso a datos relacionados con la comida del filósofo
	pthread_mutex_lock(&philo->mutex_philo);
	// Si ya comió lo suficiente, no es considerado "muerto"
	if (philo->rutine->total_turns != -1
		&& philo->count_eaten >= philo->rutine->total_turns)
	{
		pthread_mutex_unlock(&philo->mutex_philo);
		return (1);
	}
	// Si ha pasado mucho tiempo desde su última comida, lo marca como muerto.
	if (milliseconds() - philo->act_time >= philo->rutine->time_die)
	{
		pthread_mutex_lock(&philo->rutine->mutex_rutine);
		if (philo->rutine->dead == 0)
		{
			// Indica al sistema que alguien murió, deteniendo a los demás
			philo->rutine->dead = 1;
		}
		pthread_mutex_unlock(&philo->rutine->mutex_rutine);
		print_message("is dead", philo);

		alive = 0;
	}
	pthread_mutex_unlock(&philo->mutex_philo);
	return (alive);
}

void	destroy_mutex(t_rutine *routine)
{
	int i;

	i = 0;
	while (i < routine->num_philo)
	{
		pthread_mutex_destroy(&routine->philos[i].mutex_philo);
		i++;
	}

	// Destruir los mutex de los tenedores
    destroy_forks(routine, routine->num_philo);

	// i = 0;
	// while (i < routine->num_philo)
	// {
	// 	pthread_mutex_destroy(&routine->fork[i]);
	// 	i++;
	// }
	
	pthread_mutex_destroy(&routine->print_lock);
	
	free(routine->philos);
	routine->philos = NULL;
	free(routine->fork);
	routine->fork = NULL;
}

void	print_message(char *str, t_philosophers *philo)
{
	int	current_time;

	pthread_mutex_lock(&philo->rutine->print_lock);
	current_time = milliseconds() - philo->rutine->start_rutine;
	printf("%u %d %s\n", current_time, philo->id_philo, str);
	pthread_mutex_unlock(&philo->rutine->print_lock);
}