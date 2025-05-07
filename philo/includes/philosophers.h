/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:12:54 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/19 19:21:59 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h> //gettimeofday
// pthread_create pthread_detach pthread_join pthread_mutex_init
// pthread_mutex_destroy pthread_mutex_lock pthread_mutex_unlock

# include <stdio.h>  //printf
# include <stdlib.h> //malloc free
# include <string.h> //memset
# include <unistd.h> //write usleep
// INT_MAX INT_MIN
# include <limits.h>
# include <stdint.h>

typedef struct s_rutine	t_rutine;
typedef struct s_philosophers
{
	int					id_philo;
	long long			act_time;
	int					count_eaten;
	int					left_fork;
	int					right_fork;
	pthread_mutex_t		mutex_philo;
	pthread_t			thread_id;
	t_rutine			*rutine;
}						t_philosophers;

typedef struct s_rutine
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					total_turns;
	int					dead;
	int					philosophers_full;
	int					status;
	int					start_rutine;
	pthread_mutex_t		*fork;
	pthread_mutex_t		meal_full;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		check_dead;
	pthread_mutex_t		mutex_rutine;
	pthread_t			chechk_routine;
	t_philosophers		*philos;
}						t_rutine;
// DIE.C
int						philo_is_dead(t_rutine *rutine);
// EAT.C
void					update_meal(t_philosophers *philo);
void					ft_eat(t_philosophers *philo);
// FORKS.C
void 					lock_forks_odd(t_philosophers *philo);
void					lock_forks(t_philosophers *philo);
void					unlock_forks(t_philosophers *philo);
void					init_forks(t_rutine *rutine);
void					destroy_forks(t_rutine *rutine, int i);
// FT_ERROR.C
int						ft_error(int i);
// LIBFT.C
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strchr(const char *s, int c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
int						is_digit(char c);
// MAIN.C
int						main(int argc, char **argv);
// NUMBER_OF_PHILO
int						init_philosophers(t_rutine *rutine);
// PARSE.C
int						check_number(char *numbers);
int						ft_atol(const char *num);
int						assign_value(int *dest, char *str);
int						ft_parse(char **argv, t_rutine *rutine);
// ROUTINE.C
void					precise_sleep(long duration);
void					*one_philo(t_philosophers *philo);
void					*routine(void *philo);
void					*routine_check(void *arg);
// SLEEP.C
void					ft_sleep(t_philosophers *philo);
// THINK.C
void					ft_think(t_philosophers *philo);
// UTILS.C
long					milliseconds(void);
void					init_mutex(t_rutine *rutine);
int						philo_is_alive(t_philosophers *philo);
void					destroy_mutex(t_rutine *routine);
void					print_message(char *str, t_philosophers *philo);

#endif
