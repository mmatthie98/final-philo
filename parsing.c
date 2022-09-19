/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:06:52 by mmatthie          #+#    #+#             */
/*   Updated: 2022/09/19 19:07:04 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int arg)
{
	if (arg >= '0' && arg <= '9')
		return (0);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	neg;
	int	i;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] >= 7 && str[i] <= 13)
		i++;
	if ((str && (str[i] == '+')) || (str && (str[i] == '-')))
	{
		if (str[i] == '-')
			neg -= 2;
		i++;
	}
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res * neg);
}

int	check_the_arg(char	**av, t_data	*data)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				j++;
			else
			{
				printf("use only digit please\n");
				return (1);
			}
		}
		i++;
	}
	if (i > 5)
		data->indicate = 1;
	return (0);
}

int	get_the_arg(char	**av, t_data	*data)
{
	int	i;
	int	tmp;

	i = 1;
	tmp = 0;
	if (av)
	{
		data->nb_of_philo = ft_atoi(av[1]);
		if (data->nb_of_philo == 0)
		{
			printf("nb of philo need to be a positive value\n");
			return (1);
		}
		data->time_to_die = ft_atoi(av[2]);
		data->time_to_eat = ft_atoi(av[3]);
		data->time_to_sleep = ft_atoi(av[4]);
		data->indicate = 0;
		data->die = 0;
		if (av[5] && av[5] != 0)
			data->nb_of_time_each_eat = ft_atoi(av[5]);
		else
			data->nb_of_time_each_eat = -1;
	}
	return (0);
}
