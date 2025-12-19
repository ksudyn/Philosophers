/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:21:37 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/12 18:25:56 by ksudyn           ###   ########.fr       */
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

/* Inicializa semáforo de control de impresión de muerte */
static int init_sem_dead(t_rutine *r)
{
    sem_unlink("/philo_sem_dead");
    r->sem_dead = sem_open("/philo_sem_dead", O_CREAT | O_EXCL, 0644, 1);
    return (r->sem_dead == SEM_FAILED);
}

/* Inicializa semáforos básicos: print, forks y eat */
static int init_basic_sems(t_rutine *r)
{
    sem_unlink("/philo_sem_print");
    sem_unlink("/philo_sem_forks");
    sem_unlink("/philo_sem_eat");

    r->sem_print = sem_open("/philo_sem_print", O_CREAT | O_EXCL, 0644, 1);
    if (r->sem_print == SEM_FAILED)
        return (1);

    r->sem_forks = sem_open("/philo_sem_forks", O_CREAT | O_EXCL, 0644, r->num_philo);
    if (r->sem_forks == SEM_FAILED)
        return (1);

    r->sem_eat = sem_open("/philo_sem_eat", O_CREAT | O_EXCL, 0644, 1);
    if (r->sem_eat == SEM_FAILED)
        return (1);

    return (0);
}

/* Inicializa semáforo de control de "room" (para evitar deadlock) */
static int init_sem_room(t_rutine *r)
{
    if (r->num_philo > 1)
    {
        r->sem_room = sem_open("/philo_sem_room", O_CREAT | O_EXCL, 0644,
                               r->num_philo - 1);
        if (r->sem_room == SEM_FAILED)
            r->sem_room = NULL;
    }
    else
        r->sem_room = NULL;

    return (0);
}

/* Función principal que llama a todas las anteriores */
int init_semaphores(t_rutine *r)
{
    if (init_sem_dead(r))
        return (1);
    if (init_basic_sems(r))
        return (1);
    init_sem_room(r);  // room no es crítico si falla
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