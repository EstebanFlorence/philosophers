/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:26:41 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/07 22:33:51 by adi-nata         ###   ########.fr       */
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
	pthread_mutex_init(&table->message, NULL);

}

void	ft_message(t_table *table, char *message, int id)
{
	struct timeval	time;
	long			millisec;

	gettimeofday(&time, NULL);
	millisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	pthread_mutex_lock(&table->message);
	printf("%ld %d %s\n", millisec, id, message);
	pthread_mutex_unlock(&table->message);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	int		eat;

	philo = (t_philo *)arg;
	table = philo->table;
	eat = 0;
	while (!table->end)
	{
		ft_message(table, THINK, philo->id);
		pthread_mutex_lock(philo->left_fork);
		ft_message(table, LFORK, philo->id);
		pthread_mutex_lock(philo->right_fork);
		ft_message(table, RFORK, philo->id);
		ft_message(table, EAT, philo->id);
		usleep(table->eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_message(table, SLEEP, philo->id);
		eat++;
		if (table->times && eat >= table->times)
		{
			philo->eaten = eat;
			break;
		}
	}
	return (NULL);
}
