/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:39:57 by ksudyn            #+#    #+#             */
/*   Updated: 2025/03/10 18:40:22 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Funcion temporal de pensar
void think(t_philosophers *philo)
{
    printf("Filósofo %d está pensando 🤔\n", philo->philo);
    usleep(philo->parse->time_sleep * 1000);  // Simula el tiempo de pensar
}
