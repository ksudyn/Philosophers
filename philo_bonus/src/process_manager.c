/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:28:30 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/12 17:56:23 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* Espera a todos los hijos y devuelve 1 si alguno murió */
static int	wait_for_first_child_exit(t_rutine *r)
{
	int		status;
	pid_t	wpid;

	(void)r;
	status = 0;
	wpid = waitpid(-1, &status, 0);
	if (wpid == -1)
		return (0);
	/* si salió con error => alguien murió => return 1 */
	if ((WIFEXITED(status) && WEXITSTATUS(status) != 0)
		|| WIFSIGNALED(status))
		return (1);
	return (0);
}


/* Mata todos los hijos usando SIGKILL */
static void	kill_all_children(t_rutine *r)
{
	int	i;

	i = 0;
	while (i < r->num_philo)
	{
		if (r->philos[i].pid > 0)
			kill(r->philos[i].pid, SIGKILL);
		i++;
	}
}

/* Cierra y unlinka semáforos y libera memoria */
static void	cleanup_semaphores(t_rutine *r)
{
	if (r->sem_print)
		sem_close(r->sem_print);
	if (r->sem_forks)
		sem_close(r->sem_forks);
	if (r->sem_eat)
		sem_close(r->sem_eat);
	if (r->sem_room)
		sem_close(r->sem_room);
	if (r->sem_dead)
		sem_close(r->sem_dead);
	sem_unlink("/philo_sem_print");
	sem_unlink("/philo_sem_forks");
	sem_unlink("/philo_sem_eat");
	sem_unlink("/philo_sem_room");
	sem_unlink("/philo_sem_dead");
	free_philos_array(r);
}

/* Función principal */
void	wait_and_cleanup(t_rutine *r)
{
	if (!r)
		return ;
	if (wait_for_first_child_exit(r))
		kill_all_children(r);
	cleanup_semaphores(r);
}
