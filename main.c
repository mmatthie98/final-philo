/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:56:34 by mmatthie          #+#    #+#             */
/*   Updated: 2022/09/19 21:41:28 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char	**av)
{
	t_data	data;
	t_mu	mu;
	t_philo	*ph;

	ph = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!ph)
		return (my_error("ph issue's\n", 1));
	if (ac > 4 && ac < 7)
	{
		if (check_the_arg(av, &data) == 0)
		{
			if (get_the_arg(av, &data) == 0)
			{
				init_philo(ph, &data, &mu);
				init_mu(ph, &mu);
				init_thread(ph);
				destroy_mu(ph);
			}
		}
	}
	else
		printf("insert at minimum 5 parameters and not more than 6\n");
	return (0);
}
