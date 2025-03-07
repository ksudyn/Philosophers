/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:10:50 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/27 17:10:52 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Función para que el filósofo coma
void	eat(t_philosophers *philo)
{
	// Tomar los tenedores
	pthread_mutex_lock(&philo->right_fork);
	printf("[%ld] Filósofo %d tomó el tenedor derecho 🍴\n", milliseconds(), philo->philo);
	pthread_mutex_lock(philo->left_fork);
	printf("[%ld] Filósofo %d tomó el tenedor izquierdo 🍴\n", milliseconds(), philo->philo);

	// Comer
	printf("[%ld] Filósofo %d está comiendo 🍝\n", milliseconds(), philo->philo);
	philo->last_eat = milliseconds(); // Guardar tiempo de última comida
	usleep(philo->parse->time_eat * 1000); // Simular tiempo de comida

	// Soltar los tenedores
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	printf("[%ld] Filósofo %d terminó de comer y soltó los tenedores\n", milliseconds(), philo->philo);
}
