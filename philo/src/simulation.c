/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:26:41 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/16 22:37:43 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_status(t_table *table, char *message, int id)
{
	static int	death;
	long		timenow;

	pthread_mutex_lock(&table->status);
	if (!ft_strncmp(message, DIED, 57))
		death = 0;
	timenow = ft_timedifference(table->time.tv_sec, table->time.tv_usec);
	if (!death)
		printf("%ld %d %s\n", timenow, id, message);
	if (!death && !ft_strncmp(message, DIED, 57))
		death = 1;
	pthread_mutex_unlock(&table->status);
}

void	ft_lastmeal(t_philo *philo)
{
	ft_status(philo->table, EAT, philo->id);
	pthread_mutex_lock(&philo->table->check);
	philo->last_meal = ft_timedifference
		(philo->table->time.tv_sec, philo->table->time.tv_usec);
	printf("Philo %d last meal: %ld\n", philo->id, philo->last_meal);
	pthread_mutex_unlock(&philo->table->check);
	usleep(philo->table->eat * 1000);
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
	ft_lastmeal(philo);
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
//	if (philo->id % 2 == 0)
//		usleep(1000);
	while (1)
	{
		ft_eat(philo);
		pthread_mutex_lock(&table->check);
		if (table->end == 1 || (table->times != -1 && ++eat >= table->times))
		{
			table->end = 1;
			printf("Philosopher %d is full\n", philo->id);
			pthread_mutex_unlock(&table->check);
			break ;
		}
		pthread_mutex_unlock(&table->check);
		ft_status(table, SLEEP, philo->id);
		usleep(table->sleep * 1000);
		ft_status(table, THINK, philo->id);
	}
	return (NULL);
}

/* void	ft_forker1(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_status(philo->table, RFORK, philo->id);
	pthread_mutex_lock(philo->left_fork);
	ft_status(philo->table, LFORK, philo->id);
	ft_status(philo->table, EAT, philo->id);
	pthread_mutex_lock(&philo->table->check);
	philo->last_meal = ft_timedifference
		(philo->table->time.tv_sec, philo->table->time.tv_usec);
	pthread_mutex_unlock(&philo->table->check);
	usleep(philo->table->eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_forker2(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_status(philo->table, LFORK, philo->id);
	pthread_mutex_lock(philo->right_fork);
	ft_status(philo->table, RFORK, philo->id);
	ft_status(philo->table, EAT, philo->id);
	pthread_mutex_lock(&philo->table->check);
	philo->last_meal = ft_timedifference
		(philo->table->time.tv_sec, philo->table->time.tv_usec);
	pthread_mutex_unlock(&philo->table->check);
	usleep(philo->table->eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
} */

/* void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_forker2(philo);
	else
		ft_forker1(philo);
} */
