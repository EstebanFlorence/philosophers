/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:36:18 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/21 00:09:02 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
#include <fcntl.h>

# define EAT	"\e[0;32m Is eating... \e[0m"
# define SLEEP	"\e[0;34m Is sleeping... \e[0m"
# define THINK	"\e[0;38;5;199m Is thinking... \e[0m"
# define FORK	"has taken a fork"
# define FORKK	"has taken another fork"
# define DIED	"☠️☠️☠️ \e[0;31m Died! \e[0m ☠️☠️☠️"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;

	struct timeval	time;
	time_t			last_meal;

	pthread_t		tid;
	pid_t			pid;

	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				philos;
	int				die;
	int				eat;
	int				sleep;
	int				times;

	int				death;
	int				end;

	sem_t			*forks;
	sem_t			*status;
	sem_t			*check;

	struct timeval	time;

	t_philo			*philo;

}	t_table;

void	ft_check(int ac, char **av);
void	ft_innit(int ac, char **av, t_table *args);
void	ft_sem_innit(t_table *table);

//	SIMULATION
void	ft_process(void *arg);
void	ft_eat(t_philo *philo);
void	ft_philo(t_table *table);
void	ft_status(t_table *table, char *message, int id);
void	ft_end(t_table *table);

//	TOOLS
void	ft_error(int n);
void	ft_close(t_table *args);
time_t	ft_gettime(void);
time_t	ft_timedifference(time_t start, suseconds_t ustart);
void	ft_usleep(time_t time);

//	LIBFT
int		ft_atoi(const char *nbr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);

#endif