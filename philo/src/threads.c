/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:26:41 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/13 22:53:37 by adi-nata         ###   ########.fr       */
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
	struct timeval	time;
	long			milliseconds;
	long			seconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);

    seconds = time.tv_sec % 60;

	pthread_mutex_lock(&table->status);
    printf("%02ld.%03ld %d %s\n", seconds, milliseconds % 1000, id, message);
	pthread_mutex_unlock(&table->status);

/* 	pthread_mutex_lock(&table->status);
	printf("%ld %d %s\n", millisec, id, message);
	pthread_mutex_unlock(&table->status); */
}

void	ft_forker(t_philo *philo)
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
}

/* void	ft_death(t_philo *philo)
{

} */

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
		ft_status(table, EAT, philo->id);
		usleep(table->eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&table->check);
		if (ft_timedifference(table->time.tv_sec, table->time.tv_usec) >= table->die * 1000)
		{
			pthread_mutex_unlock(&table->check);
			ft_status(table, DIED, philo->id);
		//	ft_death(philo);
			break;
		}
		//pthread_mutex_unlock(&table->check);
		//pthread_mutex_lock(&table->check);
		if (table->times != -1 && ++eat >= table->times)
		{
			pthread_mutex_unlock(&table->check);
			printf("Philo %d is full\n", philo->id);
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
	while(i < table->philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->philos];
		table->philo[i].table = table;
		pthread_create(&table->philo[i].tid, NULL, routine, &table->philo[i]);
		i++;
	}

}
