/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:50:07 by jjakupi           #+#    #+#             */
/*   Updated: 2025/02/06 15:29:28 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			perror("Error destroying fork mutex");
		i++;
	}
	if (pthread_mutex_destroy(&data->print_mutex) != 0)
		perror("Error destroying print mutex");
	if (pthread_mutex_destroy(&data->death_mutex) != 0)
		perror("Error destroying death mutex");
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
