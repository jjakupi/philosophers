/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:07:22 by jjakupi           #+#    #+#             */
/*   Updated: 2025/01/30 15:56:27 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_philos_ate(t_data *data)
{
	int	i;
	int	count;

	count = 0;
	if (data->must_eat == -1)
		return (0);

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat)
			count++;
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
	return (count == data->num_philos); // Only return true if ALL philosophers have eaten enough
}

void	*monitor_philosophers(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->death_mutex);
			if ((get_time() - data->philos[i].last_meal_time) >= data->time_to_die)
			{
				data->simulation_ended = 1;
				printf("%ld %d died\n", get_time() - data->start_time, data->philos[i].id);
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL); // ✅ Exit properly to avoid re-unlocking
			}
			pthread_mutex_unlock(&data->death_mutex);
			i++;
		}

		// ✅ Exit if simulation ended
		pthread_mutex_lock(&data->death_mutex);
		if (data->simulation_ended)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&data->death_mutex);

		usleep(500);
	}
	return (NULL);
}

