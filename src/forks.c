/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:30:26 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/29 19:30:28 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void lock_forks(t_philosophers *philo)
{
    // Para evitar interbloqueos: orden de adquisición diferente para pares e impares
    if (philo->id_philo % 2 == 0)
    {
        pthread_mutex_lock(&philo->rutine->fork[philo->right_fork]);
        pthread_mutex_lock(&philo->rutine->fork[philo->left_fork]);
    }
    else
    {
        pthread_mutex_lock(&philo->rutine->fork[philo->left_fork]);
        pthread_mutex_lock(&philo->rutine->fork[philo->right_fork]);
    }
}
// Si todos toman primero el tenedor izquierdo,
// todos tendrían uno bloqueado, y nunca llegarían al segundo (interbloqueo total).
// Al variar el orden entre pares e impares:
// No todos toman el mismo tenedor primero.
// Siempre hay una posibilidad de que uno de ellos avance, coma y libere

// Esta estrategia asegura que:
// No todos los filósofos se quedan atascados esperando el segundo tenedor.
// Se logra progreso seguro y concurrente sin interbloqueo

void unlock_forks(t_philosophers *philo)
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
//tiene que desbloquearse en el orden inverso al que se bloquearon para optimizar

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