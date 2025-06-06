/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:32:39 by jjakupi           #+#    #+#             */
/*   Updated: 2025/06/06 15:12:57 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

// Struct to hold simulation data
typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				simulation_ended;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_data;

// Function prototypes
int		parse_arguments(t_data *data, int argc, char **argv);
int		ft_atoi(const char *str);
int		init_data(t_data *data);
int		init_forks(t_data *data);
void	init_philosophers(t_data *data);
int		start_threads(t_data *data);
void	*philosopher_routine(void *arg);
void	*monitor_philosophers(void *arg);
long	get_time(void);
void	smart_sleep(long time, t_data *data);
void	print_action(t_philo *philo, char *action);
void	cleanup(t_data *data); // ✅ Add cleanup function
void	destroy_mutexes(t_data *data);
int		check_if_all_ate(t_data *data);

#endif
