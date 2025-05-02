/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:03:36 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/28 15:03:54 by ksudyn           ###   ########.fr       */
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
	if (*num == '+' && *(num + 1) == '+')
		return (0);
	if (*num == '+')
		num++;
	if (*num < '0' || *num > '9')
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
	int		i;
	int		digit;
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

int	assign_value(int *dest, char *str)
{
	int	temp;

	temp = ft_atol(str);
	if (temp > INT_MAX || temp <= 0)
		return (1);
	*dest = (int)temp;
	return (0);
}

int	ft_parse(char **argv, t_rutine *rutine)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (check_number(argv[i]) == 1)
			return (1);
		i++;
	}
	if (assign_value(&rutine->num_philo, argv[1])
		|| assign_value(&rutine->time_die, argv[2])
		|| assign_value(&rutine->time_eat, argv[3])
		|| assign_value(&rutine->time_sleep, argv[4]))
		return (1);
	if (argv[5])
	{
		if (assign_value(&rutine->total_turns, argv[5]))
			return (1);
	}
	else
		rutine->total_turns = -1;
	// printf("num_filo %li\n", rutine->num_philo);
	// printf("time_die %li\n", rutine->time_die);
	// printf("time_eat %li\n", rutine->time_eat);
	// printf("time_sleep %li\n", rutine->time_sleep);
	// printf("turns %li\n", rutine->total_turns);
	return (0);
}
