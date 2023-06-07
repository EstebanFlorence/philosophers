/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:02:46 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/07 15:28:00 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->philos);
	if (!table->philo)
		ft_error(3);
	while(i < table->philos)
	{
		table->philo[i].id = i;
		table->philo[i].left_fork = i; 
		i++;
	}
}

void	ft_innit(int ac, char **av, t_table *args)
{
	int	i;

	i = 0;
	args->philos = ft_atoi(av[1]);
	args->die = ft_atoi(av[2]);
	args->eat = ft_atoi(av[3]);
	args->sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->times = ft_atoi(av[5]);
	else
		args->times = -1;

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
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table	args;
	//t_philo	philo;

	ft_check(ac, av);
	ft_innit(ac, av, &args);

	//pthread_mutex_init(&args.mutex, NULL);

	//pthread_create(&args.tid1, NULL, &routine, &args);
	//pthread_create(&args.tid2, NULL, &routine, &args);

	ft_threads(&args);

/* 	for (int i = 0; i < args.philos; i++)
		printf("Philo id: %d\n", args.philo[i].id); */
	//pthread_join(args.tid, NULL);
	//pthread_join(args.tid2, NULL);

	//pthread_mutex_destroy(&args.mutex);

/* 	ft_printf("%d\n%d\n%d\n%d\n%d\n", 
			args.philos, args.die, args.eat, args.sleep, args.times); */


	ft_finish(&args);

	return (0);
}
