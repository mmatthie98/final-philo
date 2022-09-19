/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:00:53 by mmatthie          #+#    #+#             */
/*   Updated: 2022/09/19 18:02:29 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	take_the_time(void)
{
	unsigned long long	result;
	struct timeval		tv;

	result = 0;
	if (gettimeofday(&tv, NULL) != 0)
		return (1);
	result = tv.tv_sec * 1000;
	result += tv.tv_usec / 1000;
	return (result);
}

void	time_to_wait(unsigned long long time)
{
	unsigned long long	start;

	start = take_the_time();
	while (take_the_time() - start < time)
		usleep(500);
}

void	print_log(void *arg, int mod)
{
	t_philo				*ph;
	unsigned long long	time;

	ph = (t_philo *)arg;
	time = take_the_time() - ph->data->init_time;
	pthread_mutex_lock(&ph->mu->log);
	if (ph->data->die == 0)
	{
		if (mod == 1)
			printf("%llu %d has taken a fork\n", time, ph->philo_id);
		else if (mod == 2)
			printf("%llu %d is eating\n", time, ph->philo_id);
		else if (mod == 3)
			printf("%llu %d is sleeping\n", time, ph->philo_id);
		else if (mod == 4)
			printf("%llu %d is thinking\n", time, ph->philo_id);
		else if (mod == 5)
			printf("%llu %d is died\n", time, ph->philo_id);
		else if (mod == 6)
			printf("every philo are starved! thank yah!\n");
	}
	pthread_mutex_unlock(&ph->mu->log);
}
