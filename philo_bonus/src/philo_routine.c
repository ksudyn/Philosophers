/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:28:57 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/09 20:33:51 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* philo_routine.c - versión corregida */
#include "../includes/philo_bonus.h"

/* monitor: thread que corre dentro de cada proceso hijo */
void	*monitor_thread(void *arg)
{
	t_philo		*philo;
	t_rutine	*r;

	philo = (t_philo *)arg;
	r = philo->rutine;
	while (1)
	{
		sem_wait(r->sem_eat);
		if ((milliseconds_bonus() - philo->last_meal) > r->time_die)
		{
			/* print muerte y salir con status 1 */
			print_msg(philo, "is dead");
			sem_post(r->sem_eat);
			exit(1);
		}
		sem_post(r->sem_eat);
		usleep(1000); /* dormir 1ms para no busyloop */
	}
	return (NULL);
}

/* tomar 2 tenedores usando sem_forks; opcionalmente proteger con sem_room */
static void	take_forks(t_philo *philo)
{
	t_rutine	*r;

	r = philo->rutine;
	if (r->sem_room)
		sem_wait(r->sem_room);
	sem_wait(r->sem_forks);
	print_msg(philo, "has taken a fork");
	sem_wait(r->sem_forks);
	print_msg(philo, "has taken a fork");
}

/* soltar 2 tenedores */
static void	release_forks(t_philo *philo)
{
	t_rutine	*r;

	r = philo->rutine;
	sem_post(r->sem_forks);
	sem_post(r->sem_forks);
	if (r->sem_room)
		sem_post(r->sem_room);
}

/* la rutina principal en el hijo */
void	philo_routine(t_philo *philo)
{
	t_rutine	*r;
	pthread_t	mon;

	r = philo->rutine;
	/* inicializar last_meal */
	sem_wait(r->sem_eat);
	philo->last_meal = milliseconds_bonus();
	sem_post(r->sem_eat);
	/* lanzar monitor */
	if (pthread_create(&mon, NULL, monitor_thread, philo) != 0)
		exit(1);
	pthread_detach(mon);
	/* caso especial 1 filósofo */
	if (r->num_philo == 1)
	{
		sem_wait(r->sem_forks);
		print_msg(philo, "has taken a fork");
		usleep(r->time_die * 1000);
		print_msg(philo, "is dead");
		exit(1);
	}
	/* bucle principal */
	while (r->total_turns == -1 || philo->count_eaten < r->total_turns)
	{
		/* tomar tenedores */
		take_forks(philo);
		/* actualizar last_meal y comer */
		sem_wait(r->sem_eat);
		philo->last_meal = milliseconds_bonus();
		philo->count_eaten++;
		sem_post(r->sem_eat);
		print_msg(philo, "is eating");
		usleep(r->time_eat * 1000);
		/* soltar tenedores */
		release_forks(philo);
		/* dormir */
		print_msg(philo, "is sleeping");
		usleep(r->time_sleep * 1000);
		/* pensar */
		print_msg(philo, "is thinking");
		usleep(1000);
	}
	/* si salió porque comió suficiente -> exit 0 */
	exit(0);
}
