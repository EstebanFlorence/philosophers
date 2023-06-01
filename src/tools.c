/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:41:58 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/01 15:54:00 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(t_table *args)
{
	free(args->tid);
}

void	ft_error(int n)
{
	if (n == 0)
	{
		printf("Wrong number of arguments\n");
		exit(EXIT_SUCCESS);
	}
	if (n == 1)
	{
		printf("Wrong type of arguments\n");
		exit(EXIT_SUCCESS);
	}
	if (n == 2)
		perror("pthread()");

	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *nbr)
{
	int	sign;
	int	power;
	int	res;

	sign = 1;
	power = 1.0;
	res = 0.0;
	while (*nbr == ' ' || \
			(*nbr >= '\t' && *nbr <= '\r'))
		nbr++;
	if (*nbr == '-' || *nbr == '+')
	{
		if (*nbr == '-')
			sign *= -1;
		nbr++;
	}
	while (*nbr >= '0' && *nbr <= '9')
	{
		res = res * 10.0 + *nbr - '0';
		nbr++;
	}
	if (*nbr == '.')
		nbr++;
	while (*nbr >= '0' && *nbr <= '9')
	{
		res = res * 10.0 + *nbr - '0';
		power *= 10.0;
		nbr++;
	}
	return (sign * res / power);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
