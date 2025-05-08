/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:12:13 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/30 17:12:14 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_meal(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->mutex_philo);
	philo->act_time = milliseconds();
	philo->count_eaten++;
	pthread_mutex_unlock(&philo->mutex_philo);
}

void	ft_eat(t_philosophers *philo)
{
	// Bloquea los tenedores según el ID del filósofo (usando la función lock_forks)
	if (!lock_forks(philo))
		return ;
	// Verifica si el filósofo está muerto, si es así, sale de la función
	if (philo_is_dead(philo->rutine))
	{
		unlock_forks(philo); // Desbloquea los tenedores antes de salir
		return ;
	}
	// Establece el estado del filósofo a "comiendo"

	pthread_mutex_lock(&philo->rutine->mutex_rutine);  // Bloquea el mutex antes de modificar el estado
	philo->rutine->status = 1;
	pthread_mutex_unlock(&philo->rutine->mutex_rutine);  // Libera el mutex después de modificar el estado

	// Imprime el mensaje de que el filósofo está comiendo
	print_message("is eating", philo);
	// Actualiza el número de comidas (incrementa el contador)
	update_meal(philo);
	// Simula el tiempo que el filósofo tarda en comer
	usleep(philo->rutine->time_eat * 1000);
	unlock_forks(philo);
	// Después de comer, desbloquea los tenedores
	if (philo_is_dead(philo->rutine))
		return ;
	// Imprime un mensaje indicando que el filósofo ha terminado de comer
	print_message("has finished eating", philo);
}

//he convertido lock_fortks en int para que en esta funcion si al comprobar en lock_forks
//si un filosofo muere se desbloqueen los tenedores y en esta funcion justo despues no los vuelva a desbloquear