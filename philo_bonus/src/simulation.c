/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:31:57 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/21 00:57:37 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_status(t_table *table, char *message, int id)
{
	long	timenow;

	sem_wait(table->status);
	timenow = ft_timedifference(table->time.tv_sec, table->time.tv_usec);
	if (!table->death)
		printf("%ld %d %s\n", timenow, id, message);
	if (!table->death && !ft_strncmp(message, DIED, 57))
		table->death = 1;
	sem_post(table->status);
}

void	ft_philo(t_table *table)
{
	ft_status(table, FORK, 1);
	ft_usleep(table->eat);
	ft_status(table, DIED, 1);

	ft_close(table);
	exit(EXIT_SUCCESS);
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->table->forks);
	ft_status(philo->table, FORK, philo->id);
	sem_wait(philo->table->forks);
	ft_status(philo->table, FORKK, philo->id);
	ft_status(philo->table, EAT, philo->id);
	sem_wait(philo->table->check);
	philo->last_meal = ft_timedifference
		(philo->time.tv_sec, philo->time.tv_usec);
	sem_post(philo->table->check);
	ft_usleep(philo->table->eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	ft_process(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	int		eat;

	philo = (t_philo *)arg;
	table = philo->table;
	eat = 0;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		ft_eat(philo);
		sem_wait(philo->table->check);
		if (philo->table->end == 1 || (table->times != -1 && ++eat >= table->times))
		{
			table->end = 1;
			sem_post(philo->table->check);
			break ;
		}
		sem_post(philo->table->check);
		ft_status(philo->table, SLEEP, philo->id);
		ft_usleep(philo->table->sleep);
		ft_status(philo->table, THINK, philo->id);
	}
}
