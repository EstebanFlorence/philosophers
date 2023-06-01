/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:02:46 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/01 14:43:27 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_thread(void *arg)
{
	t_table	*args;

	args = (t_table *)arg;
	pthread_mutex_lock(&args->mutex);

	printf("OK\n");
	sleep(1);

	pthread_mutex_unlock(&args->mutex);


	//ft_printf("FINNISH\n");
	return (NULL);
}

void	ft_innit(int ac, char **av, t_table *args)
{
	args->philos = ft_atoi(av[1]);
	args->die = ft_atoi(av[2]);
	args->eat = ft_atoi(av[3]);
	args->sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->times = ft_atoi(av[5]);

}

void	ft_error(int n)
{
	if (n == 0)
		printf("Error\nWrong number of arguments\n");
	if (n == 1)
		printf("Error\nWrong type of arguments\n");
	if (n == 2)
		printf("Error\npthread_create()\n");

	exit(EXIT_FAILURE);
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

int	main(/* int ac, char **av */)
{
	t_table	args;
	//t_philo	philo;

	//ft_check(ac, av);
	//ft_innit(ac, av, &args);

	pthread_mutex_init(&args.mutex, NULL);

	pthread_create(&args.tid1, NULL, &ft_thread, &args);
	pthread_create(&args.tid2, NULL, &ft_thread, &args);


	pthread_join(args.tid1, NULL);
	pthread_join(args.tid2, NULL);

	pthread_mutex_destroy(&args.mutex);

/* 	ft_printf("%d\n%d\n%d\n%d\n%d\n", 
			args.philos, args.die, args.eat, args.sleep, args.times); */
	
	return (0);
}
