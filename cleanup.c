/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:50:07 by jjakupi           #+#    #+#             */
/*   Updated: 2025/06/06 14:08:39 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			printf("Error: Failed to destroy fork mutex\n");
		i++;
	}
	if (pthread_mutex_destroy(&data->print_mutex) != 0)
		printf("Error: Failed to destroy print mutex\n");
	if (pthread_mutex_destroy(&data->death_mutex) != 0)
		printf("Error: Failed to destroy death mutex\n");
}

void	free_memory(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	cleanup(t_data *data)
{
	destroy_mutexes(data);
	free_memory(data);
}
