/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_and_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:29:22 by mmatthie          #+#    #+#             */
/*   Updated: 2022/09/19 20:30:07 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_error(char	*str, int errorcode)
{
	if (errorcode != 0)
	{
		printf("%s\n", str);
		return (1);
	}
	else if (errorcode == 0)
	{
		printf("%s\n", str);
		return (0);
	}
	return (0);
}

void	my_print_log(t_philo	*ph, int mod)
{
	pthread_mutex_lock(&ph->mu->death);
	print_log(ph, mod);
	ph->data->die = 1;
	pthread_mutex_unlock(&ph->mu->death);
}

void	*handler(void	*arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (ph->data->die == 0)
	{
		if (ph->data->nb_of_philo > 1)
		{
			if (take_the_time() > ph->last_meal + ph->data->time_to_die)
				my_print_log(ph, 5);
			if (ph->data->die == 0 \
			&& ph->data->nb_ph_fed == ph->data->nb_of_philo)
				my_print_log(ph, 6);
			usleep(1000);
		}
	}
	return (NULL);
}

void	life_routine(t_philo	*ph)
{
	while (ph->data->die == 0)
	{
		thinking(ph);
		take_fork(ph);
		eat(ph);
		drop_fork(ph);
		sleeping(ph);
	}
}

void	*start_routine(void	*arg)
{
	t_philo		*ph;
	pthread_t	checker;

	ph = (t_philo *) arg;
	ph->last_meal = ph->data->init_time;
	if (pthread_create(&checker, NULL, &handler, ph) != 0)
		return (NULL);
	if (ph->data->die == 0)
	{
		if (ph->data->nb_of_philo == 1)
			lonely_philo(ph);
		else
			while (ph->data->die == 0)
				life_routine(ph);
	}
	pthread_join(checker, NULL);
	return (NULL);
}
