/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:37:40 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/10 20:44:48 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_rutine	t_rutine;

struct s_philo
{
	int					id_philo;     // ID lógico del filósofo (1, 2, 3...) para identificarlos en mensajes
	long long			last_meal;    // Momento (en ms) del último alimento para monitorizar si muere
	int					count_eaten;  // Cuántas veces ha comido este filósofo
	pid_t				pid;          // PID del proceso hijo correspondiente a este filósofo
	pthread_t			monitor;      // Hilo interno que monitorea la vida del filósofo (para detectar muerte)
	t_rutine			*rutine;      // Puntero a la estructura principal con todos los datos de la simulación
};

struct s_rutine
{
	int					num_philo;    // Número total de filósofos
	int					time_die;     // Tiempo máximo sin comer antes de morir (ms)
	int					time_eat;     // Tiempo que tarda en comer (ms)
	int					time_sleep;   // Tiempo que tarda en dormir (ms)
	int					total_turns;  // Número de comidas que cada filósofo debe realizar (-1 si infinito)

	long long			start_time;   // Momento inicial de la simulación (ms) para calcular tiempos relativos

	// Semáforos POSIX (sustituyen los mutex de la versión obligatoria)
	sem_t				*sem_print;   // Semáforo para proteger la impresión en consola (solo un filósofo imprime a la vez)
	sem_t				*sem_forks;   // Semáforo que controla el acceso a los "tenedores" (forks)
	sem_t				*sem_eat;     // Semáforo para proteger el conteo de comidas y evitar condiciones de carrera
	sem_t				*sem_room;    // Semáforo opcional para limitar cuántos filósofos pueden intentar comer al mismo tiempo

	t_philo				*philos;      // Array de filósofos
	pid_t				*pids;        // Array de PID de todos los procesos hijos, para que el padre pueda controlarlos
};

/*	ft_error 				*/
int						ft_error_bonus(int i);
/*	init_bonus.c 			*/
int						init_philos_array(t_rutine *rutine);
int						init_semaphores(t_rutine *rutine);
/*	philo_routine_utils.c	*/
void					*monitor_thread(void *arg);
void					take_forks(t_philo *philo);
void					release_forks(t_philo *philo);
void					init_philo(t_philo *philo);
void					handle_single_philo(t_philo *philo);
/*	philo_routine.c			*/
void					philo_routine(t_philo *philo);
/*	process_manager.c		*/
void					wait_and_cleanup(t_rutine *rutine);
int						spawn_philosophers(t_rutine *rutine);
/*	utils_bonus_2.c 		*/
void					free_philos_array(t_rutine *rutine);
void					print_msg(t_philo *philo, const char *msg);
void					child_cleanup(t_rutine *r);
/*	utils_bonus.c 			*/
long long				milliseconds_bonus(void);
int						ft_atol(const char *s);
int						check_number(const char *s);
int						assign_value(int *dest, char *str);
int						ft_parse_bonus(int argc, char **argv, t_rutine *rutine);
#endif
