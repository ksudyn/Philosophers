/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:17:42 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/10 19:46:20 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Hilo creado dentro de cada proceso filósofo.
// Vigila si el filósofo muere (no come en time_die ms):
// Toma el semáforo sem_eat para proteger last_meal.
// Compara tiempo actual (milliseconds_bonus()) con last_meal.
// Si pasó time_die → imprime “is dead”, libera sem_eat y sale del proceso con exit(1).
// Sino → libera semáforo y duerme 1 ms (usleep(1000)) para no hacer busy-wait.
void	*monitor_thread(void *arg)
{
	t_philo		*philo;
	t_rutine	*rutin;

	philo = (t_philo *)arg;
	rutin = philo->rutine;
	while (1)
	{
		sem_wait(rutin->sem_eat);
		if ((milliseconds_bonus() - philo->last_meal) > rutin->time_die)
		{
			/* print muerte y salir con status 1 */
			print_msg(philo, "is dead");
			sem_post(rutin->sem_eat);
			exit(1);
		}
		sem_post(rutin->sem_eat);
		usleep(1000); /* dormir 1ms para no busyloop */
	}
	return (NULL);
}


// Toma dos “tenedores” usando sem_forks.
// Si sem_room está activo, primero hace sem_wait(sem_room) (evita deadlock).
// Luego:
// sem_wait(sem_forks) → primer tenedor.
// print_msg(philo, "has taken a fork");
// sem_wait(sem_forks) → segundo tenedor.
// print_msg(philo, "has taken a fork");
void	take_forks(t_philo *philo)
{
	t_rutine	*rutin;

	rutin = philo->rutine;
	if (rutin->sem_room)
		sem_wait(rutin->sem_room);
	sem_wait(rutin->sem_forks);
	print_msg(philo, "has taken a fork");
	sem_wait(rutin->sem_forks);
	print_msg(philo, "has taken a fork");
}

// Libera los tenedores tomados:
// sem_post(sem_forks) dos veces.
// Si sem_room existe → sem_post(sem_room) para “dejar entrar” otro filósofo al comedor.
void	release_forks(t_philo *philo)
{
	t_rutine	*rutin;

	rutin = philo->rutine;
	sem_post(rutin->sem_forks);
	sem_post(rutin->sem_forks);
	if (rutin->sem_room)
		sem_post(rutin->sem_room);
}

// Actualiza last_meal protegida por sem_eat.
// Crea hilo monitor_thread dentro del proceso (pthread_create).
// Si falla el hilo → limpia recursos con child_cleanup y sale (exit(1)).
// Hace pthread_detach para que el hilo termine automáticamente al finalizar el proceso.
void	init_philo(t_philo *philo)
{
	t_rutine	*r;
	pthread_t	mon;

	r = philo->rutine;
	sem_wait(r->sem_eat);
	philo->last_meal = milliseconds_bonus();
	sem_post(r->sem_eat);
	if (pthread_create(&mon, NULL, monitor_thread, philo) != 0)
	{
		child_cleanup(r);
		exit(1);
	}
	pthread_detach(mon);
}

// Caso especial: solo hay un filósofo.
// Toma un tenedor (sem_wait(sem_forks)) → imprime mensaje.
// Duerme time_die ms → muere (no puede comer con un solo tenedor) → imprime mensaje.
// Limpia recursos y sale.
void	handle_single_philo(t_philo *philo)
{
	t_rutine	*rutin;

	rutin = philo->rutine;
	sem_wait(rutin->sem_forks);
	print_msg(philo, "has taken a fork");
	usleep(rutin->time_die * 1000);
	print_msg(philo, "is dead");
	child_cleanup(rutin);
	exit(1);
}
