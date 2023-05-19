/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:15:46 by adi-nata          #+#    #+#             */
/*   Updated: 2023/05/10 15:16:19 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *nbr)
{
	int		sign;
	double	power;
	double	res;

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
