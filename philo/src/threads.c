/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:26:41 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/15 19:47:18 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_mutex_innit(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philos);
	if (!table->forks)
		ft_error(3);
	while (i < table->philos)
		pthread_mutex_init(&table->forks[i++], NULL);
	pthread_mutex_init(&table->check, NULL);
	pthread_mutex_init(&table->status, NULL);

}

void	ft_status(t_table *table, char *message, int id)
{
	static int flag = 0;
	long			time_is_now;

	time_is_now = ft_timedifference(table->time.tv_sec, table->time.tv_usec);
	pthread_mutex_lock(&table->status);
	if (!flag)
    	printf("%ld %d %s\n", time_is_now, id, message);
	if (!flag && !ft_strncmp(message, DIED, 57))
		flag = 1;
	pthread_mutex_unlock(&table->status);
}

void	ft_forker(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_status(philo->table, LFORK, philo->id);
		pthread_mutex_lock(philo->right_fork);
		ft_status(philo->table, RFORK, philo->id);
		ft_status(philo->table, EAT, philo->id);
		pthread_mutex_lock(&philo->table->check);
		philo->last_meal = ft_timedifference(philo->table->time.tv_sec, philo->table->time.tv_usec);
		pthread_mutex_unlock(&philo->table->check);
		usleep(philo->table->eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_status(philo->table, RFORK, philo->id);
		pthread_mutex_lock(philo->left_fork);
		ft_status(philo->table, LFORK, philo->id);
		ft_status(philo->table, EAT, philo->id);
		pthread_mutex_lock(&philo->table->check);
		philo->last_meal = ft_timedifference(philo->table->time.tv_sec, philo->table->time.tv_usec);
		pthread_mutex_unlock(&philo->table->check);
		usleep(philo->table->eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void check_death(t_table *table)
{
	int i = 0;
	while (1)
	{
		pthread_mutex_lock(&table->check);
		if (table->end == 1)
		{
			pthread_mutex_unlock(&table->check);
			break;
		}
		if (ft_timedifference(table->time.tv_sec, table->time.tv_usec) - table->philo[i].last_meal > (time_t)table->die)
		{
			ft_status(table, DIED, table->philo[i].id);
			table->end = 1;
			pthread_mutex_unlock(&table->check);
			return ;
		}
		i++;
		if (i == table->philos)
			i = 0;
		pthread_mutex_unlock(&table->check);
		usleep(5000);
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
	while (1)
	{
		ft_forker(philo);
		pthread_mutex_lock(&table->check);
		if (table->end == 1 || (table->times != -1 && ++eat >= table->times))
		{
			pthread_mutex_unlock(&table->check);
			break;
		}
		pthread_mutex_unlock(&table->check);
		ft_status(table, SLEEP, philo->id);
		usleep(table->sleep * 1000);
		ft_status(table, THINK, philo->id);
	}
	return (NULL);
}

void	ft_philos(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->philos);
	if (!table->philo)
		ft_error(3);
	i = 0;
	gettimeofday(&table->time, NULL);
	while(i < table->philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->philos];
		table->philo[i].table = table;
		table->philo[i].last_meal = ft_gettime();
		gettimeofday(&table->philo[i].time, NULL);
		pthread_create(&table->philo[i].tid, NULL, routine, &table->philo[i]);
		i++;
	}
	check_death(table);
}
