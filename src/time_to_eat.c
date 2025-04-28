/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:10:50 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/27 17:10:52 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// //Funcion temporal para comer
// void    eat(t_philosophers *philo)
// {
//     // Tomar los tenedores
//     pthread_mutex_lock(philo->left_fork);
//     pthread_mutex_lock(&philo->right_fork);

//     // Comer
//     printf("Filósofo %d ha tomado los tenedores y está comiendo 🍝\n", philo->philo);
//     philo->last_eat = milliseconds();
//     usleep(philo->parse->time_eat * 1000);

//     // Soltar los tenedores
//     pthread_mutex_unlock(&philo->right_fork);
//     pthread_mutex_unlock(philo->left_fork);

//     printf("Filósofo %d terminó de comer y soltó los tenedores 💤\n", philo->philo);
// }
