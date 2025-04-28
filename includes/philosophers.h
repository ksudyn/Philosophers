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

# include <sys/time.h>//gettimeofday

# include <pthread.h>
//pthread_create pthread_detach pthread_join pthread_mutex_init
//pthread_mutex_destroy pthread_mutex_lock pthread_mutex_unlock

# include <unistd.h>//write usleep

# include <stdio.h>//printf

# include <stdlib.h>//malloc free

# include <string.h>//memset
//INT_MAX INT_MIN
# include <stdint.h>
# include <limits.h>

typedef struct s_parse t_parse; 

typedef struct s_philosophers
{
	pthread_mutex_t		mutex;//es un candado que impide que dos hilos (filósofos) modifiquen la misma variable al mismo tiempo
	int					id_philo;
	long long			act_time;
	long				last_eat;//almacena la ultima vez que el filosofo comio en milisegundos
	int					right_fork;
	int				 	left_fork;
	pthread_t			thread_id;
	t_parse				*parse;
}				t_philosophers;

typedef struct s_parse
{
	pthread_mutex_t     *fork;
	int					dead;
	int					status;
	int					total_turns;
	long				num_philo;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	long				turns;
	t_philosophers		*philos;
}				t_parse;

//FT_ERROR.C
int		ft_error(int i);
//LIBFT.C
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		is_digit(char c);
//MAIN.C
int		main(int argc, char **argv);
//NUMBER_OF_PHILO
int 	init_philosophers(t_parse *parse);
//PARSE.C
int		ft_parse(char **argv, t_parse *philo);
//ROUTINE.C
void *philo_routine(void *arg);
//THINK.C
void think(t_philosophers *philo);
//TIME_TO_DIE.C
void check_death(t_parse *philo);
//TIME_TO_EAT.C
void    eat(t_philosophers *philo);
//TIME_TO_SLEEP.C
void sleep_philo(t_philosophers *philo);
//UTILS.C
int		check_number(char *numbers);
int		ft_atol(const char *num);
long	milliseconds(void);

#endif
