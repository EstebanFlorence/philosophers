/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:41:58 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/05 17:09:37 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(t_table *args)
{
	free(args->tid);
	free(args->forks);
}

void	ft_error(int n)
{
	if (n == 0)
		write(2, "Error:\nWrong number of arguments\n", 34);
	if (n == 1)
		write(2, "Error:\nWrong type of arguments\n", 32);
	if (n == 2)
		write(2, "Error:\npthread()\n", 18);
	if (n == 3)
		write(2, "Error:\nmalloc()\n", 17);

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
