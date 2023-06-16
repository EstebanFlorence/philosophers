/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:48:20 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/16 14:51:15 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_reaper(t_table *table, int i)
{
	if (ft_timedifference
		(table->time.tv_sec, table->time.tv_usec) - table->philo[i].last_meal
		> (time_t)table->die)
	{
		printf("ft_reaper:\n\ttime difference: %ld\n", ft_timedifference
		(table->time.tv_sec, table->time.tv_usec) - table->philo[i].last_meal);
		ft_status(table, DIED, table->philo[i].id);
		table->end = 1;
		pthread_mutex_unlock(&table->check);
		return (1);
	}
	return (0);
}

void	ft_death(t_table *table)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&table->check);
		if (table->end == 1)
		{
			pthread_mutex_unlock(&table->check);
			break ;
		}
		if (ft_reaper(table, i))
			return ;
		i++;
		if (i == table->philos)
			i = 0;
		pthread_mutex_unlock(&table->check);
		usleep(5000);
	}
}
