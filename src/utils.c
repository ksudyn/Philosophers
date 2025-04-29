/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:45:47 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/27 18:45:50 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atol(const char *num)
{
	long	result;
	result = 0;

	while (*num == ' ' || *num == '\t' || *num == '\n' || *num == '\v'
		|| *num == '\f' || *num == '\r')
		num++;
	if(*num == '+' && *(num + 1) == '+')
		return (0);
	if (*num == '+')
		num++;
	if(*num < '0' || *num > '9')
		return (0);

	while (*num >= '0' && *num <= '9')
	{
		result = result * 10 + (*num - '0');
		num++;
	}
	return (result);
}

int	check_number(char *numbers)
{
	int	i;
	int	digit;
	long	num;

	i = 0;
	digit = 0;
	if (numbers[i] == '+')
		i++;

	while (numbers[i])
	{
		if (!is_digit(numbers[i]))
			return (1);
		digit++;
		i++;
	}
	if (digit > 12)
		return (1);

	num = atol(numbers);
	if (num > INT_MAX || num == 0)
		return (1);

	return (0);
}

long	milliseconds(void)
{
	struct timeval time;
	long long 	milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	
	return(milliseconds);
}//transforma el timepo a miliseguncos para que sea mas preciso
