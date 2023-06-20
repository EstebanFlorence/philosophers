/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:26:41 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/18 04:04:09 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_status(t_table *table, char *message, int id)
{
	long	timenow;

	pthread_mutex_lock(&table->status);
	timenow = ft_timedifference(table->time.tv_sec, table->time.tv_usec);
	if (!table->death)
		printf("%ld %d %s\n", timenow, id, message);
	if (!table->death && !ft_strncmp(message, DIED, 57))
		table->death = 1;
	pthread_mutex_unlock(&table->status);
}

void	ft_meal(t_philo *philo)
{
	ft_status(philo->table, EAT, philo->id);
	pthread_mutex_lock(&philo->table->check);
	philo->last_meal = ft_timedifference
		(philo->time.tv_sec, philo->time.tv_usec);
	pthread_mutex_unlock(&philo->table->check);
	ft_usleep(philo->table->eat);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_status(philo->table, LFORK, philo->id);
		pthread_mutex_lock(philo->right_fork);
		ft_status(philo->table, RFORK, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_status(philo->table, RFORK, philo->id);
		pthread_mutex_lock(philo->left_fork);
		ft_status(philo->table, LFORK, philo->id);
	}
	ft_meal(philo);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	int		eat;

	philo = (t_philo *)arg;
	table = philo->table;
	eat = 0;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		ft_eat(philo);
		pthread_mutex_lock(&table->check);
		if (table->end == 1 || (table->times != -1 && ++eat >= table->times))
		{
			table->end = 1;
			pthread_mutex_unlock(&table->check);
			break ;
		}
		pthread_mutex_unlock(&table->check);
		ft_status(table, SLEEP, philo->id);
		ft_usleep(table->sleep);
		ft_status(table, THINK, philo->id);
	}
	return (NULL);
}
