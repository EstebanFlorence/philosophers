/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:24:30 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/07 18:36:45 by adi-nata         ###   ########.fr       */
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
	int			id;
	int			left_fork;
	int			right_fork;
	int			eaten;

	pthread_t	tid;

}	t_philo;

typedef struct s_table
{
	int				philos;
	int				die;
	int				eat;
	int				sleep;
	int				times;
	
//	pthread_t		*tid;
//	pthread_mutex_t	mutex;

	pthread_mutex_t	*forks;
	pthread_mutex_t	message;

	t_philo			*philo;

}	t_table;


void	ft_check(int ac, char **av);
void	ft_innit(int ac, char **av, t_table *args);
void	ft_philos(t_table *table);

//	THREADZ
void	ft_mutex_innit(t_table *table);
//void	*routine(void *arg);
//void	ft_threads(t_table *table);

//void	*exroutine(void *arg);

//	TOOLZ
int		ft_isdigit(int c);
int		ft_atoi(const char *nbr);
void	ft_error(int n);
void	ft_finish(t_table *args);


#endif