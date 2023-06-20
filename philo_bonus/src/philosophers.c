/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:54:35 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/21 00:51:19 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philos(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->philos);
	if (!table->philo)
		ft_error(3);
	if (table->philos == 1)
		ft_philo(table);
	i = 0;
	gettimeofday(&table->time, NULL);
	while (i < table->philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].last_meal = 0;
		table->philo[i].table = table;
		table->philo[i].pid = fork();
		if (table->philo[i].pid == -1)
			ft_error(2);
		if (table->philo[i].pid == 0)
			ft_process(&table->philo[i]);
		i++;
	}
	ft_end(table);
}

void	ft_sem_innit(t_table *table)
{
	sem_unlink("forks");
	sem_unlink("check");
	sem_unlink("status");
	sem_unlink("eating");
	table->forks = sem_open("forks", O_CREAT, S_IRWXU, table->philos);
	table->check = sem_open("check", O_CREAT, S_IRWXU, 1);
	table->status = sem_open("status", O_CREAT, S_IRWXU, 1);
	table->eating = sem_open("eating", O_CREAT, S_IRWXU, 0);
	if (table->forks == SEM_FAILED || table->check == SEM_FAILED
		|| table->status == SEM_FAILED)
		ft_error(4);
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
	ft_sem_innit(&args);
	ft_philos(&args);
	ft_close(&args);
	return (0);
}