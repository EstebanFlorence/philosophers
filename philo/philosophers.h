/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:24:30 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/20 19:00:49 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define EAT	"\e[0;32m Is eating... \e[0m"
# define SLEEP	"\e[0;34m Is sleeping... \e[0m"
# define THINK	"\e[0;38;5;199m Is thinking... \e[0m"
# define RFORK	"has taken the right fork"
# define LFORK	"has taken the left fork"
# define DIED	"☠️☠️☠️ \e[0;31m Died! \e[0m ☠️☠️☠️"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;

	struct timeval	time;
	time_t			last_meal;

	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

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

	pthread_mutex_t	*forks;
	pthread_mutex_t	status;
	pthread_mutex_t	check;

	struct timeval	time;

	t_philo			*philo;

}	t_table;

void	ft_check(int ac, char **av);
void	ft_innit(int ac, char **av, t_table *args);
void	ft_mutex_innit(t_table *table);
void	ft_philos(t_table *table);
void	ft_philo(t_table *table);

//	SIMULATION
void	*routine(void *arg);
void	ft_eat(t_philo *philo);
void	ft_meal(t_philo *philo);
void	ft_status(t_table *table, char *message, int id);
void	ft_end(t_table *table);
int		ft_death(t_table *table, int i);

//	TOOLS
void	ft_error(int n);
void	ft_destroy(t_table *args);
void	ft_usleep(time_t time);
time_t	ft_gettime(void);
time_t	ft_timedifference(time_t start, suseconds_t ustart);

//	LIBFT
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nbr);

#endif