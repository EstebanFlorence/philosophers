/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:41:58 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/19 16:40:23 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

time_t	ft_timedifference(time_t start, suseconds_t ustart)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec - start) * 1000 + (time.tv_usec - ustart) / 1000);
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = ft_gettime();
	while (ft_gettime() - start < time)
		usleep(100);
}

void	ft_error(int n)
{
	if (n == 0)
		write(2, "Error:\nWrong number of arguments\n", 34);
	if (n == 1)
		write(2, "Error:\nWrong type of arguments\n", 32);
	if (n == 2)
		write(2, "Error:\npthread()\n", 18);
	if (n == 3)
		write(2, "Error:\nmalloc()\n", 17);
	exit(EXIT_FAILURE);
}

void	ft_philo(t_table *table)
{
	ft_status(table, RFORK, 1);
	ft_usleep(table->die + 1);
	ft_status(table, DIED, 1);
	pthread_mutex_destroy(&table->forks[0]);
	pthread_mutex_destroy(&table->status);
	pthread_mutex_destroy(&table->check);
	free(table->forks);
	free(table->philo);
	exit (EXIT_SUCCESS);
}
