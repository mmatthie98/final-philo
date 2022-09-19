/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:28:05 by mmatthie          #+#    #+#             */
/*   Updated: 2022/09/19 21:19:01 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mu(t_philo	*ph, t_mu	*mu)
{
	int	i;

	i = 0;
	ph->mu->forks = malloc(sizeof(pthread_mutex_t) * ph->data->nb_of_philo);
	if (!mu->forks)
		printf("error in mutex malloc\n");
	while (i < ph->data->nb_of_philo)
	{
		if (pthread_mutex_init(&ph->mu->forks[i], NULL) != 0)
			printf("error with init mutex right_fork\n");
		i++;
	}
	if (pthread_mutex_init(&ph->mu->log, NULL) != 0)
		printf("error in mutex init\n");
	if (pthread_mutex_init(&ph->mu->fed_ph, NULL) != 0)
		printf("error in mutex init\n");
	if (pthread_mutex_init(&ph->mu->death, NULL) != 0)
		printf("error in mutex init\n");
}

void	init_philo(t_philo	*ph, t_data	*data, t_mu	*mu)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_philo)
	{
		ph[i].philo_id = i;
		ph[i].last_meal = 0;
		ph[i].nb_of_lunch = 0;
		ph[i].data = data;
		ph[i].left_fork = i;
		ph[i].meal_min = 0;
		ph[i].right_fork = ((i + 1) % data->nb_of_philo);
		ph[i].mu = mu;
	}
}

void	init_thread(t_philo	*ph)
{
	int	i;

	i = 0;
	ph->data->init_time = take_the_time();
	while (i < ph->data->nb_of_philo)
	{
		if (pthread_create(&ph[i].th, NULL, &start_routine, &ph[i]) != 0)
			printf("error in thread creation\n");
		i = i + 2;
	}
	time_to_wait(2);
	i = 1;
	while (i < ph->data->nb_of_philo)
	{
		if (pthread_create(&ph[i].th, NULL, &start_routine, &ph[i]) != 0)
			printf("error in the thread creation\n");
		i = i + 2;
	}
	i = -1;
	while (++i < ph->data->nb_of_philo)
		pthread_join(ph[i].th, NULL);
}

void	lonely_philo(t_philo	*ph)
{
	if (ph->data->nb_of_philo == 1 && ph->data->die == 0)
	{
		print_log(ph, 1);
		time_to_wait(ph->data->time_to_die);
		my_print_log(ph, 5);
	}
}

void	*destroy_mu(t_philo	*ph)
{
	int	i;

	i = -1;
	while (++i < ph->data->nb_of_philo)
	{
		if (pthread_mutex_destroy(&ph->mu->forks[i]) != 0)
			return (NULL);
		i++;
	}
	if (pthread_mutex_destroy(&ph->mu->log) != 0)
		return (NULL);
	if (pthread_mutex_destroy(&ph->mu->fed_ph) != 0)
		return (NULL);
	if (pthread_mutex_destroy(&ph->mu->death) != 0)
		return (NULL);
	return (NULL);
}
