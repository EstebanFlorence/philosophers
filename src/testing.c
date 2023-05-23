/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:28:13 by adi-nata          #+#    #+#             */
/*   Updated: 2023/05/23 16:26:14 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define TIMES_TO_COUNT 21000

#define NC		"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED		"\e[31m"
#define GREEN	"\e[32m"

void	*ft_thread(void *data)
{
	pthread_t		tid;
	unsigned int	*count;
	unsigned int	i;

	tid = pthread_self();
	count = (unsigned int *)data;
	i = 0;
	printf("%sThread [%ld]: Count at thread start = %u.%s\n",
		YELLOW, tid, *count, NC);
	while (i < TIMES_TO_COUNT)
	{
		(*count)++;
		i++;
	}
	printf("%sThread [%ld]: Final count = %u.%s\n",
		BYELLOW, tid, *count, NC);
	return (NULL);
}

int	main(/* int ac, char **av */)
{
	pthread_t		tid1;
	pthread_t		tid2;
	unsigned int	count;

	count = 0;
	printf("Main: Expected count is %s%u%s\n", GREEN, 
					2 * TIMES_TO_COUNT, NC);

	pthread_create(&tid1, NULL, ft_thread, &count);
	printf("Main: Created first thread [%ld]\n", tid1);

	pthread_create(&tid2, NULL, ft_thread, &count);
	printf("Main: Created second thread [%ld]\n", tid1);

	pthread_join(tid1, NULL);
	printf("Main: Joined first thread [%ld]\n", tid1);

	pthread_join(tid2, NULL);
	printf("Main: Joined second thread [%ld]\n", tid1);

	if (count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERROR ! Total count is %u%s\n", RED, count, NC);
	else
		printf("%sMain: OK. Total count is %u%s\n", GREEN, count, NC);
	return (0);
}
