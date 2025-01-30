/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:49:49 by jjakupi           #+#    #+#             */
/*   Updated: 2025/01/30 16:40:41 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Error: Mutex initialization failed\n"), 1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (printf("Error: Print mutex init failed\n"), 1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (printf("Error: Death mutex init failed\n"), 1);
	return (0);
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		i++;
	}
}

int	init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->philos || !data->forks)
		return (printf("Error: Memory allocation failed\n"), 1);
	if (init_forks(data) != 0)
		return (1);
	init_philosophers(data);
	return (0);
}


int	start_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
			return (printf("Error: Failed to create thread\n"), 1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_philosophers, data) != 0)
		return (printf("Error: Failed to create monitor thread\n"), 1);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}
