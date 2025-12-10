/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:32:33 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/10 20:42:02 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* libera la memoria dinámica que almacena */
void	free_philos_array(t_rutine *rutine)
{
	if (!rutine)
		return ;
	if (rutine->philos)
		free(rutine->philos);
	if (rutine->pids)
		free(rutine->pids);
	rutine->philos = NULL;
	rutine->pids = NULL;
}
/* imprimir protegido */
void	print_msg(t_philo *philo, const char *msg)
{
	long long	ts;

	sem_wait(philo->rutine->sem_print);
	ts = milliseconds_bonus() - philo->rutine->start_time;
	printf("%lld %d %s\n", ts, philo->id_philo, msg);
	sem_post(philo->rutine->sem_print);
}

void	child_cleanup(t_rutine *rutin)
{
	if (!rutin)
		return ;
	if (rutin->sem_print && rutin->sem_print != SEM_FAILED)
		sem_close(rutin->sem_print);
	if (rutin->sem_forks && rutin->sem_forks != SEM_FAILED)
		sem_close(rutin->sem_forks);
	if (rutin->sem_eat && rutin->sem_eat != SEM_FAILED)
		sem_close(rutin->sem_eat);
	if (rutin->sem_room && rutin->sem_room != SEM_FAILED)
		sem_close(rutin->sem_room);
	/* liberar arrays heredados por fork (reduce "still reachable" de Valgrind) */
	if (rutin->philos)
	{
		free(rutin->philos);
		rutin->philos = NULL;
	}
	if (rutin->pids)
	{
		free(rutin->pids);
		rutin->pids = NULL;
	}
}
