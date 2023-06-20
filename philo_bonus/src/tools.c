/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:56:06 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/20 13:26:20 by adi-nata         ###   ########.fr       */
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

ft_destroy(t_table *args)
{
	free(args->philo);
	
}
