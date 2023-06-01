/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:24:30 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/01 16:05:36 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT	"\e[0;32m Is eating... \e[0m"
# define SLEEP	"\e[0;34m Is sleeping... \e[0m"
# define THINK	"\e[0;38;5;199m Is thinking... \e[0m"
# define RFORK	"has taken the right fork"
# define LFORK	"has taken the left fork"
# define DIED	":skull_and_crossbones: \e[0;31m Died! \e[0m :skull_and_crossbones:"

typedef struct s_philo
{
	int	id;

}	t_philo;

typedef struct s_table
{
	int			philos;
	int			die;
	int			eat;
	int			sleep;
	int			times;
	
	pthread_t	*tid;

	pthread_mutex_t	mutex;

}	t_table;


void	ft_check(int ac, char **av);
void	ft_innit(int ac, char **av, t_table *args);

//	THREADZ
void	*routine(void *arg);
void	ft_threadz(t_table *args);

//	TOOLZ
int		ft_isdigit(int c);
int		ft_atoi(const char *nbr);
void	ft_error(int n);
void	ft_free(t_table *args);


#endif