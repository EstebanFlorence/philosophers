/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:48:36 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/20 11:49:04 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nbr)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
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
		res = res * 10 + *nbr - '0';
		nbr++;
	}
	return (res * sign);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (ss1[i] != ss2[i] || ss1[i] == 0 || ss2[i] == 0)
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
