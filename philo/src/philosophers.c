/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:02:46 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/09 18:02:26 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	gettimeofday(&args->time, NULL);
	args->start = ft_gettime();
	

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
	ft_mutex_innit(&args);

	//ft_philos(&args);

/* 	for (int i = 0; i < args.philos; i++)
		printf("Philo id: %d\n", args.philo[i].id);

	printf("%d\n%d\n%d\n%d\n%d\n", 
			args.philos, args.die, args.eat, args.sleep, args.times); */

	ft_finish(&args);

	return (0);
}
