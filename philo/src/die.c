/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:12:03 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/11 14:50:10 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_is_dead(t_rutine *rutine)
{
	int	dead;

	pthread_mutex_lock(&rutine->mutex_rutine);
	dead = rutine->dead;
	pthread_mutex_unlock(&rutine->mutex_rutine);
	// cambiando la variable porque en philo_is_alive es otroa
	return (dead);
}
