/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:30:54 by mmatthie          #+#    #+#             */
/*   Updated: 2022/09/19 21:18:32 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_data
{
	int					nb_of_philo;
	unsigned long long	init_time;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_time_each_eat;
	int					indicate;
	int					nb_ph_fed;
	int					die;
}			t_data;

typedef struct s_mu
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	log;
	pthread_mutex_t	death;
	pthread_mutex_t	fed_ph;
}	t_mu;

typedef struct s_philo
{
	pthread_t			th;
	int					philo_id;
	unsigned long long	last_meal;
	int					right_fork;
	int					left_fork;
	int					nb_of_lunch;
	int					meal_min;
	t_data				*data;
	t_mu				*mu;
}			t_philo;

// parsing.c
int					ft_isdigit(int arg);
int					check_the_arg(char	**av, t_data	*data);
int					get_the_arg(char	**av, t_data	*data);
int					ft_atoi(const char *str);

//parsing2.c
long long			ft_atoll(const char	*str);
size_t				ft_strlentab(char	**tab);

//init_and_destroy.c
void				init_mu(t_philo	*ph, t_mu	*mu);
void				init_philo(t_philo	*ph, t_data	*data, t_mu	*mu);
void				lonely_philo(t_philo	*ph);
void				init_thread(t_philo	*ph);
void				*destroy_mu(t_philo	*ph);

//time_and_print.c
unsigned long long	take_the_time(void);
void				time_to_wait(unsigned long long time);
void				print_data(t_data	*data, t_philo	*ph, int i);
void				print_log(void	*arg, int mod);

//doing_things.c
void				drop_fork(t_philo	*ph);
void				eat(t_philo	*ph);
void				take_fork(t_philo	*arg);
void				sleeping(void	*args);
void				thinking(void	*args);

//routine_and_handler
int					my_error(char	*str, int errorcode);
void				*handler(void	*arg);
void				life_routine(t_philo	*ph);
void				*start_routine(void	*arg);
void				my_print_log(t_philo	*ph, int mod);
#endif
