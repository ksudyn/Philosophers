/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:39:59 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/10 20:39:02 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

long long	milliseconds_bonus(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
}

int	ft_atol(const char *num)
{
	long	result;

	result = 0;
	if (!num)
		return (0);
	while (*num == ' ' || *num == '\t' || *num == '\n')
		num++;
	if (*num == '+')
		num++;
	if (*num < '0' || *num > '9')
		return (0);
	while (*num >= '0' && *num <= '9')
	{
		result = result * 10 + (*num - '0');
		if (result > INT_MAX)
			return (INT_MAX);
		num++;
	}
	return ((int)result);
}

int	check_number(const char *src)
{
	int		i;
	int		digits;
	long	val;

	i = 0;
	digits = 0;
	if (!src)
		return (1);
	if (src[0] == '+')
		i++;
	while (src[i])
	{
		if (src[i] < '0' || src[i] > '9')
			return (1);
		digits++;
		i++;
	}
	if (digits == 0 || digits > 12)
		return (1);
	val = atol(src);
	if (val == 0 || val > INT_MAX)
		return (1);
	return (0);
}

int	assign_value_bonus(int *dest, char *str)
{
	int	v;

	v = ft_atol(str);
	if (v <= 0 || v > INT_MAX)
		return (1);
	*dest = v;
	return (0);
}

/* parse */
int	ft_parse_bonus(int argc, char **argv, t_rutine *rutine)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (check_number(argv[i]))
			return (1);
		i++;
	}
	if (assign_value_bonus(&rutine->num_philo, argv[1])
		|| assign_value_bonus(&rutine->time_die, argv[2])
		|| assign_value_bonus(&rutine->time_eat, argv[3])
		|| assign_value_bonus(&rutine->time_sleep, argv[4]))
		return (1);
	if (argv[5])
	{
		if (assign_value_bonus(&rutine->total_turns, argv[5]))
			return (1);
	}
	else
		rutine->total_turns = -1;
	return (0);
}
