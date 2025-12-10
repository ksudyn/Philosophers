/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:21:37 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/10 19:47:59 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* init_philos_array: llena datos básicos (no toca semáforos ni forks) */
int	init_philos_array(t_rutine *rutine)
{
	int	i;

	if (!rutine)
		return (1);
	if (rutine->num_philo <= 0 || rutine->num_philo > 200)
		return (1);
	rutine->philos = malloc(sizeof(t_philo) * rutine->num_philo);
	rutine->pids = malloc(sizeof(pid_t) * rutine->num_philo);
	if (!rutine->philos || !rutine->pids)
	{
		free_philos_array(rutine);
		return (1);
	}
	i = 0;
	while (i < rutine->num_philo)
	{
		rutine->philos[i].id_philo = i + 1;
		rutine->philos[i].last_meal = milliseconds_bonus();
		rutine->philos[i].count_eaten = 0;
		rutine->philos[i].pid = -1;
		rutine->philos[i].rutine = rutine;
		i++;
	}
	return (0);
}

/* init_semaphores: crea y asigna semáforos POSIX nombrados */
int	init_semaphores(t_rutine *rutine)
{
	sem_unlink("/philo_sem_print");
	sem_unlink("/philo_sem_forks");
	sem_unlink("/philo_sem_eat");
	sem_unlink("/philo_sem_room");
	rutine->sem_print = sem_open("/philo_sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (rutine->sem_print == SEM_FAILED)
		return (1);
	rutine->sem_forks = sem_open("/philo_sem_forks", O_CREAT | O_EXCL, 0644,
			rutine->num_philo);
	if (rutine->sem_forks == SEM_FAILED)
		return (1);
	rutine->sem_eat = sem_open("/philo_sem_eat", O_CREAT | O_EXCL, 0644, 1);
	if (rutine->sem_eat == SEM_FAILED)
		return (1);
	if (rutine->num_philo > 1)
		rutine->sem_room = sem_open("/philo_sem_room", O_CREAT | O_EXCL, 0644,
				rutine->num_philo - 1);
	else
		rutine->sem_room = NULL;
	if (rutine->sem_room == SEM_FAILED)
		rutine->sem_room = NULL;

	return (0);
}
// sem_unlink elimina un semáforo nombrado del sistema operativo, si existe.
// Es similar a borrar un archivo, porque los semáforos POSIX con nombre viven en el kernel
// y persisten incluso después de que el programa termina.
// Lo hacemos al inicio para evitar errores al crear el semáforo con sem_open(O_CREAT | O_EXCL):
// O_CREAT → crea el semáforo si no existe.
// O_EXCL → si ya existe, falla.
// Sin el sem_unlink, si ejecutas tu programa varias veces seguidas,
// sem_open fallará porque el semáforo ya estaba creado de la ejecución anterior.
// sem_unlink limpia semáforos "viejos" antes de crear los nuevos para esta ejecución