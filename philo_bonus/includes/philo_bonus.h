/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:37:40 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/09 20:34:41 by ksudyn           ###   ########.fr       */
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

typedef struct s_rutine	t_rutine;
typedef struct s_philo	t_philo;

struct					s_philo
{
	int					id_philo;
	long long			last_meal;
	int					count_eaten;
	pid_t				pid;
	pthread_t			monitor;
	t_rutine			*rutine;
};

struct					s_rutine
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					total_turns;

	long long			start_time;

	sem_t				*sem_print;
	sem_t				*sem_forks;
	sem_t				*sem_eat;
	sem_t				*sem_room;

	t_philo				*philos;
	pid_t				*pids;
};

/* ft_error */
int						ft_error(int i);

int						ft_atol(const char *s);
int						check_number(const char *s);
int						assign_value(int *dest, char *str);

int						ft_parse_bonus(int argc, char **argv, t_rutine *rutine);
long long				milliseconds_bonus(void);

int						init_philos_array(t_rutine *rutine);
void					free_philos_array(t_rutine *rutine);
int						init_semaphores(t_rutine *rutine);

int						spawn_philosophers(t_rutine *rutine);
void					wait_and_cleanup(t_rutine *rutine);

void					philo_routine(t_philo *philo);
void					*monitor_thread(void *arg);

void					print_msg(t_philo *philo, const char *msg);

#endif
