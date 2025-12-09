/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:28:30 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/09 20:35:47 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* process_manager.c */
#include "../includes/philo_bonus.h"

void	wait_and_cleanup(t_rutine *rutine)
{
	int		i;
	int		status;
	pid_t	wpid;
	int		someone_died;

	someone_died = 0;
	/* esperar a cualquier hijo; si alguno sale con status != 0
		-> matar el resto */
	for (i = 0; i < rutine->num_philo; i++)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == -1)
			continue ;
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			someone_died = 1;
		if (WIFSIGNALED(status))
			someone_died = 1;
		/* si detectamos muerte, seguimos esperando pero luego mataremos */
	}
	if (someone_died)
	{
		i = 0;
		while (i < rutine->num_philo)
		{
			kill(rutine->philos[i].pid, SIGKILL);
			i++;
		}
	}
	/* cerrar y unlink semáforos (padre) */
	if (rutine->sem_print)
		sem_close(rutine->sem_print);
	if (rutine->sem_forks)
		sem_close(rutine->sem_forks);
	if (rutine->sem_eat)
		sem_close(rutine->sem_eat);
	if (rutine->sem_room)
		sem_close(rutine->sem_room);
	sem_unlink("/philo_sem_print");
	sem_unlink("/philo_sem_forks");
	sem_unlink("/philo_sem_eat");
	sem_unlink("/philo_sem_room");
	free_philos_array(rutine);
}

/* spawn_philosophers.c
 *
 * Crea num_philo procesos,
	guarda sus pids en rutine->philos[].pid y en rutine->pids[].

	* El hijo ejecuta philo_routine(&rutine->philos[i]) y nunca vuelve (philo_routine debe terminar con exit()).
 * Si fork falla, mata a todos los hijos ya creados y devuelve 1.
 */

int	spawn_philosophers(t_rutine *rutine)
{
	int		i;
	pid_t	pid;
	int		j;

	if (!rutine || !rutine->philos || !rutine->pids)
		return (1);
	i = 0;
	while (i < rutine->num_philo)
	{
		pid = fork();
		if (pid < 0)
		{
			/* Fork falló: limpiar procesos ya creados */
			j = 0;
			while (j < i)
			{
				if (rutine->philos[j].pid > 0)
					kill(rutine->philos[j].pid, SIGKILL);
				j++;
			}
			return (1);
		}
		else if (pid == 0)
		{
			/* --- Proceso hijo --- */
			/* Guardar su pid localmente */
			rutine->philos[i].pid = getpid();
			/* IMPORTANTE: en el hijo no debemos volver al padre.
				philo_routine debe terminar el proceso con exit(0) si sale normalmente,
				o exit(1) si detecta muerte / error. */
			philo_routine(&rutine->philos[i]);
			/* Si philo_routine retorna por algún motivo, forzamos salida */
			exit(0);
		}
		else
		{
			/* --- Proceso padre --- */
			rutine->philos[i].pid = pid;
			rutine->pids[i] = pid;
		}
		i++;
	}
	return (0);
}
