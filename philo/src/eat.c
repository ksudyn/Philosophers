/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:12:13 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/11 19:48:51 by ksudyn           ###   ########.fr       */
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

/* eating_loop: maneja la espera durante el tiempo de comida, 
   verificando constantemente si el filósofo murió */
static int	eating_loop(t_philosophers *philo, long start)
{
	while (milliseconds() - start < philo->rutine->time_eat)
	{
		// Si el filósofo muere durante la comida, desbloqueamos tenedores y salimos
		if (!philo_is_dead(philo->rutine))
		{
			unlock_forks(philo);
			return (0);
		}
		usleep(100); // Espera mínima para no sobrecargar CPU
	}
	return (1); // Comida completada sin morir
}

/* ft_eat: función principal que ejecuta la rutina de comer */
void	ft_eat(t_philosophers *philo)
{
	long start;

	// Intentar tomar ambos tenedores; si falla, salir
	if (!lock_forks(philo))
		return ;

	// Si ya está muerto antes de empezar a comer, liberar tenedores y salir
	if (philo_is_dead(philo->rutine))
	{
		unlock_forks(philo);
		return ;
	}

	// Cambiar el estado global a "comiendo"
	pthread_mutex_lock(&philo->rutine->mutex_rutine);
	philo->rutine->status = 1;
	pthread_mutex_unlock(&philo->rutine->mutex_rutine);

	// Mostrar mensaje de que está comiendo y actualizar contador de comidas
	print_message("is eating", philo);
	update_meal(philo);

	// Iniciar bucle de espera mientras el filósofo come
	start = milliseconds();
	if (!eating_loop(philo, start))
		return ;

	// Terminar comida y liberar los tenedores
	unlock_forks(philo);

	// Si murió justo al final, salir antes de imprimir mensaje final
	if (philo_is_dead(philo->rutine))
		return ;

	// Mensaje de que terminó de comer
	print_message("has finished eating", philo);
}




//he convertido lock_fortks en int para que en esta funcion si al comprobar en lock_forks
//si un filosofo muere se desbloqueen los tenedores y en esta funcion justo despues no los vuelva a desbloquear