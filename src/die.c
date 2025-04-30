/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:12:03 by ksudyn            #+#    #+#             */
/*   Updated: 2025/04/30 17:12:05 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_rutine *rutine)
{
	int	dead;

	pthread_mutex_lock(&rutine->check_dead);
	dead = rutine->dead;
	pthread_mutex_unlock(&rutine->check_dead);
	return (dead);
}