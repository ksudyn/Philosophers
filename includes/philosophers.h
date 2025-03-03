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
typedef struct s_philosophers
{
	struct	s_parse		*parse;
	int					philo;
	long 				act_time;
	long				last_eat;//almacena la ultima vez que el filosofo comio en milisegundos
	pthread_mutex_t 	right_fork;
	pthread_mutex_t 	*left_fork;
}				t_philosophers;

typedef struct s_parse
{
	pthread_mutex_t		mutex;//es un candado que impide que dos hilos (filósofos) modifiquen la misma variable al mismo tiempo
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
//PARSE.C
int		parse(char **argv, t_parse *philo);
//TIME_TO_DIE.C

//TIME_TO_EAT.C
int		eating(t_philosophers *philo, t_parse *parse);
//TIME_TO_SLEEP.C

//UTILS.C
int		check_number(char *numbers);
int		ft_atol(const char *num);
long	time_milliseconds(void);

#endif
