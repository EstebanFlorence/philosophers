/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:48:20 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/19 02:44:48 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_death(t_table *table, int i)
{
	if (ft_timedifference
		(table->death == 0 && table->time.tv_sec, table->time.tv_usec) - table->philo[i].last_meal
		> (time_t)table->die)
	{
		ft_status(table, DIED, table->philo[i].id);
		table->end = 1;
		return (1);
	}
	return (0);
}

void	ft_end(t_table *table)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&table->check);
		if (table->end == 1 || ft_death(table, i))
		{
			pthread_mutex_unlock(&table->check);
			break ;
		}
		i++;
		if (i == table->philos)
			i = 0;
		pthread_mutex_unlock(&table->check);
		usleep(5000);
	}
}

void	ft_destroy(t_table *args)
{
	int	i;

	i = 0;
	while (i < args->philos)
		pthread_join(args->philo[i++].tid, NULL);
	i = 0;
	while (i < args->philos)
		pthread_mutex_destroy(&args->forks[i++]);
	pthread_mutex_destroy(&args->status);
	pthread_mutex_destroy(&args->check);
	pthread_mutex_destroy(&args->simulation);
	free(args->forks);
	free(args->philo);
}
