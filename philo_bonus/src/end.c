/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:38:01 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/21 01:45:35 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_end(t_table *table)
{
	int	i;
	int	status;

	i = 0;
	while (i < table->philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
		{
			i = 0;
			while (i < table->philos)
				kill(table->philo[i++].pid, SIGKILL);
			return ;
		}
		i++;
	}
	ft_close(table);
	printf("exit: ft_end()\n");
	exit(EXIT_FAILURE);
}

void	ft_close(t_table *args)
{
	sem_close(args->forks);
	sem_close(args->check);
	sem_close(args->status);
	sem_close(args->eating);
	sem_unlink("forks");
	sem_unlink("check");
	sem_unlink("status");
	sem_unlink("eating");
	free(args->philo);
}
