/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:54:35 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/20 13:24:46 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philos(t_table *table)
{
	int	i;

	if (table->philos == 1)
		ft_philo(table);
	i = 0;
	gettimeofday(&table->time, NULL);
	while (i < table->philos)
	{

		i++;
	}
}

void	ft_philos_innit(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->philos);
	if (!table->philo)
		ft_error(3);
	i = 0;
	while (i < table->philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].last_meal = 0;
		table->philo[i].table = table;
		i++;
	}
}

void	ft_innit(int ac, char **av, t_table *args)
{
	args->philos = ft_atoi(av[1]);
	args->die = ft_atoi(av[2]);
	args->eat = ft_atoi(av[3]);
	args->sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->times = ft_atoi(av[5]);
	else
		args->times = -1;
	args->end = 0;
	args->death = 0;
}

void	ft_check(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		ft_error(0);
	i = 1;
	j = 0;
	while (i < ac)
	{
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				ft_error(1);
			j++;
		}
		j = 0;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table	args;

	ft_check(ac, av);
	ft_innit(ac, av, &args);
	ft_philos_innit(&args);
	
	return (0);
}