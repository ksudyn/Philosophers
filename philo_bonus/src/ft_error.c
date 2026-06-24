/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:06:24 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/10 20:44:16 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_error_bonus(int i)
{
	if (i == 1)
		printf("Error: invalid args\n");
	if (i == 2)
		printf("Error: init array failed\n");
	if (i == 3)
		printf("Error: sem init phios\n");
	if (i == 4)
		printf("Error: fork failed\n");
	if (i == 5)
		printf("Error: init threads\n");
	if (i == 6)
		printf("Error: number of philosophers\n");
	return (1);
}
