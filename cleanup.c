/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:50:07 by jjakupi           #+#    #+#             */
/*   Updated: 2025/01/30 16:39:31 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]); // ✅ Destroy each fork mutex
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex); // ✅ Destroy print mutex
	pthread_mutex_destroy(&data->death_mutex); // ✅ Destroy death mutex
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
	destroy_mutexes(data); // ✅ Destroy all mutexes
	free_memory(data); // ✅ Free allocated memory
}
