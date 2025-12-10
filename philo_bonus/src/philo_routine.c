/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:28:57 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/10 19:49:28 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// take_forks(philo) → toma dos tenedores.
// Bloquea sem_eat → actualiza last_meal y count_eaten.
// Imprime “is eating” y duerme time_eat ms.
// release_forks(philo) → libera tenedores.
// Imprime “is sleeping” → duerme time_sleep ms.
// Imprime “is thinking” → duerme 1 ms para no saturar CPU.
static void	philo_eat_sleep_think(t_philo *philo)
{
	t_rutine	*r;

	r = philo->rutine;
	take_forks(philo);
	sem_wait(r->sem_eat);
	philo->last_meal = milliseconds_bonus();
	philo->count_eaten++;
	sem_post(r->sem_eat);
	print_msg(philo, "is eating");
	usleep(r->time_eat * 1000);
	release_forks(philo);
	print_msg(philo, "is sleeping");
	usleep(r->time_sleep * 1000);
	print_msg(philo, "is thinking");
	usleep(1000);
}


// Llama init_philo → inicializa monitor.
// Si solo hay un filósofo → llama handle_single_philo.
// Bucle principal:
// Mientras no haya un límite de comidas (total_turns == -1) o no se hayan alcanzado, llama philo_eat_sleep_think.
// Al terminar → child_cleanup y exit(0)
void	philo_routine(t_philo *philo)
{
	t_rutine	*rutin;

	rutin = philo->rutine;
	init_philo(philo);
	if (rutin->num_philo == 1)
		handle_single_philo(philo);
	while (rutin->total_turns == -1 || philo->count_eaten < rutin->total_turns)
		philo_eat_sleep_think(philo);
	child_cleanup(rutin);
	exit(0);
}
