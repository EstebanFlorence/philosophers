/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:41:58 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/09 18:21:37 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	ft_timedifference(time_t start, suseconds_t ustart)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec - start) * 1000 + (time.tv_usec - ustart) / 1000);
}

time_t	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_timecheck(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check);
	if ((philo->start - philo->table->start) >= philo->table->die)
		ft_status(philo->table, DIED, philo->id);
	
	pthread_mutex_unlock(&philo->table->check);

}

void	ft_finish(t_table *args)
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
	free(args->forks);
	free(args->philo);
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

int	ft_atoi(const char *nbr)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*nbr == ' ' || \
			(*nbr >= '\t' && *nbr <= '\r'))
		nbr++;
	if (*nbr == '-' || *nbr == '+')
	{
		if (*nbr == '-')
			sign *= -1;
		nbr++;
	}
	while (*nbr >= '0' && *nbr <= '9')
	{
		res = res * 10 + *nbr - '0';
		nbr++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}



/*
	while (i < args->philos)
		pthread_mutex_init(&args->forks[i++], NULL);
	i = 0;
	while (i < args->philos)
	{
		args->philo[i].id = i;
		pthread_mutex_lock(&args->mutex);

		printf("Philo id: %d\n", args->philo[i].id);

		pthread_mutex_unlock(&args->mutex);
		i++;
	}

void	ft_threadz(t_table *args)
{
	int	i;

	i = 0;
	while (i < args->philos)
	{
		
		if (pthread_create(&args->tid[i], NULL, &routine, args) != 0)
			ft_error(2);
		i++;
		printf("Thread %d: %lu has started\n", i, args->tid[i]);
	}

	i = 0;
	while (i < args->philos)
	{
		
		if (pthread_join(args->tid[i], NULL) != 0)
			ft_error(2);
		i++;
		printf("Thread %d: %lu has finished\n", i, args->tid[i]);
	}

void	*exroutine(void *arg)
{
	t_table	*args;

	args = (t_table *)arg;
	pthread_mutex_lock(&args->mutex);

	printf("OK\n");
	sleep(1);

	pthread_mutex_unlock(&args->mutex);

	return (NULL);
}

} */
