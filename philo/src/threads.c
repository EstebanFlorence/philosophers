/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:26:41 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/09 18:27:23 by adi-nata         ###   ########.fr       */
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
	pthread_mutex_init(&table->status, NULL);
	pthread_mutex_init(&table->check, NULL);

}

void	ft_status(t_table *table, char *message, int id)
{
	struct timeval	time;
	long			millisec;

	gettimeofday(&time, NULL);
	millisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	pthread_mutex_lock(&table->status);
	printf("%ld %d %s\n", millisec, id, message);
	pthread_mutex_unlock(&table->status);
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
		ft_status(table, THINK, philo->id);
		
		eat++;
		if (table->times && eat >= table->times)
		{
			philo->eaten = eat;
			break;
		}
	}
	return (NULL);
}

void	ft_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->philos);
	if (!table->philo)
		ft_error(3);
	while(i < table->philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->philos];
		table->philo[i].eaten = 0;
		table->philo[i].table = table;
		pthread_create(&table->philo[i].tid, NULL, routine, &table->philo[i]);
		i++;
	}

}


/* 		ft_status(table, THINK, philo->id);
		pthread_mutex_lock(philo->left_fork);
		ft_status(table, LFORK, philo->id);
		pthread_mutex_lock(philo->right_fork);
		ft_status(table, RFORK, philo->id);
		ft_status(table, EAT, philo->id);
		usleep(table->eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_status(table, SLEEP, philo->id);
		usleep(table->sleep * 1000); */
