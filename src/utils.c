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
	struct timeval time;
	long long 	milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	
	return(milliseconds);
}//transforma el timepo a miliseguncos para que sea mas preciso


void	init_mutex(t_rutine *rutine)
{
	int	i;
	int	thread;

	i = 0;
	pthread_mutex_init(&rutine->print_lock, NULL);
	pthread_mutex_init(&rutine->check_dead, NULL);
	pthread_mutex_init(&rutine->meal_full, NULL);
	while(i < rutine->num_philo)
	{
		thread = pthread_create(&rutine->philos[i].thread_id, NULL, routine,
					&rutine->philos[i]);
		if (thread != 0)
			printf("Error creating thread %d: %d\n", i, ft_error(5));
		i++;
	}
}


void	*routine_check(void *arg)
{
	t_rutine	*rutine;
	//int		i;

	rutine = (t_rutine *)arg;
	while (1)
	{
		//i = 0;
		// while (i < rutine->num_philo)
		// {
		// 	if (!is_alive(&rutine->philos[i]))
		// 		return (NULL);
		// 	i++;
		// }
		pthread_mutex_lock(&rutine->meal_full);
		if (rutine->philosophers_full == rutine->num_philo)
		{
			pthread_mutex_unlock(&rutine->meal_full);
			return (NULL);
		}
		pthread_mutex_unlock(&rutine->meal_full);
		usleep(500);
	}
	return (NULL);
}


// int	is_alive(t_philo *philo)
// {
// 	int	alive;

// 	alive = 1;
// 	pthread_mutex_lock(&philo->meal_mutex);
// 	if (philo->table->max_meals != -1
// 		&& philo->meals_eaten >= philo->table->max_meals)
// 	{
// 		pthread_mutex_unlock(&philo->meal_mutex);
// 		return (1);
// 	}
// 	if (get_time() - philo->last_meal >= philo->table->time_to_die)
// 	{
// 		pthread_mutex_lock(&philo->table->sim_mutex);
// 		if (philo->table->dead == 0)
// 		{
// 			philo->table->dead = 1;
// 		}
// 		pthread_mutex_unlock(&philo->table->sim_mutex);
// 		print_routine(philo, P_DIE);
// 		alive = 0;
// 	}
// 	pthread_mutex_unlock(&philo->meal_mutex);
// 	return (alive);
// }

// void	destroy_all(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	while (i < table->total_philo)
// 	{
// 		pthread_mutex_destroy(&table->philos[i].meal_mutex);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < table->total_philo)
// 	{
// 		pthread_mutex_destroy(&table->forks[i]);
// 		i++;
// 	}
// 	free(table->philos);
// 	table->philos = NULL;
// 	free(table->forks);
// 	table->forks = NULL;
// 	pthread_mutex_destroy(&table->sim_mutex);
// 	pthread_mutex_destroy(&table->print_lock);
// }