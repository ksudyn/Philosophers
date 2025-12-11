/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:30:26 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/11 19:19:09 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_forks_odd(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->rutine->fork[philo->left_fork]);
	if (philo_is_dead(philo->rutine))
	{
		pthread_mutex_unlock(&philo->rutine->fork[philo->left_fork]);
		return (0);
	}
	print_message("has taken a fork", philo);
	pthread_mutex_lock(&philo->rutine->fork[philo->right_fork]);
	if (philo_is_dead(philo->rutine))
	{
		pthread_mutex_unlock(&philo->rutine->fork[philo->right_fork]);
		pthread_mutex_unlock(&philo->rutine->fork[philo->left_fork]);
		return (0);
	}
	print_message("has taken a fork", philo);
	return (1);
}

int	lock_forks(t_philosophers *philo)
{
	if (philo_is_dead(philo->rutine))
		return (0);
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(&philo->rutine->fork[philo->right_fork]);
		if (philo_is_dead(philo->rutine))
		{
			pthread_mutex_unlock(&philo->rutine->fork[philo->right_fork]);
			return (0);
		}
		print_message("has taken a fork", philo);
		pthread_mutex_lock(&philo->rutine->fork[philo->left_fork]);
		if (philo_is_dead(philo->rutine))
		{
			pthread_mutex_unlock(&philo->rutine->fork[philo->left_fork]);
			pthread_mutex_unlock(&philo->rutine->fork[philo->right_fork]);
			return (0);
		}
		print_message("has taken a fork", philo);
		return (1);
	}
	else
		return (lock_forks_odd(philo));
}

// Si todos toman primero el tenedor izquierdo,
// todos tendrían uno bloqueado, y nunca llegarían al segundo (interbloqueo total).
// Al variar el orden entre pares e impares:
// No todos toman el mismo tenedor primero.
// Siempre hay una posibilidad de que uno de ellos avance, coma y libere

// Esta estrategia asegura que:
// No todos los filósofos se quedan atascados esperando el segundo tenedor.
// Se logra progreso seguro y concurrente sin interbloqueo

void	unlock_forks(t_philosophers *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_unlock(&philo->rutine->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->rutine->fork[philo->right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->rutine->fork[philo->right_fork]);
		pthread_mutex_unlock(&philo->rutine->fork[philo->left_fork]);
	}
}
// esta función es crucial para que los tenedores no queden "retenidos"
// por un filósofo después de comer,
// y para que la ejecución pueda continuar sin bloqueos innecesarios
// tiene que desbloquearse en el orden inverso al que se bloquearon para optimizar

void	init_forks(t_rutine *rutine)
{
	int	i;

	i = 0;
	rutine->fork = malloc(sizeof(pthread_mutex_t) * rutine->num_philo);
	if (!rutine->fork)
		return ;
	while (i < rutine->num_philo)
	{
		if (pthread_mutex_init(&rutine->fork[i], NULL))
		{
			printf("error no mutex\n");
			destroy_forks(rutine, i);
			rutine->fork = NULL;
			return ;
		}
		i++;
	}
}

void	destroy_forks(t_rutine *rutine, int i)
{
	if (!rutine->fork)
		return ;
	while (--i >= 0)
		pthread_mutex_destroy(&rutine->fork[i]);
	free(rutine->fork);
	rutine->fork = NULL;
}
