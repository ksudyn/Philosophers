/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:51:19 by ksudyn            #+#    #+#             */
/*   Updated: 2025/02/19 19:58:10 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error(int i)
{
	if (i == 1)
		printf("Número de argumentos erroneos.\n");
	if (i == 2)
		printf("Error al verificar y convertir los argumentos");
	if (i == 3)
		printf("Error al cargar los filosofos");
	if (i == 4)
		printf("Error al cargar los tenedores");
	if (i == 5)
		printf("Error al crear los hilos");
}
