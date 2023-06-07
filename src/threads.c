/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:26:41 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/07 17:20:22 by adi-nata         ###   ########.fr       */
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

/* void	ft_threads(t_table *table)
{

}

void	*routine(void *arg)
{

} */
