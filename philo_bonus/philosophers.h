/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:36:18 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/19 17:45:09 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <semaphore.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT	"\e[0;32m Is eating... \e[0m"
# define SLEEP	"\e[0;34m Is sleeping... \e[0m"
# define THINK	"\e[0;38;5;199m Is thinking... \e[0m"
# define RFORK	"has taken the right fork"
# define LFORK	"has taken the left fork"
# define DIED	"☠️☠️☠️ \e[0;31m Died! \e[0m ☠️☠️☠️"

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



#endif