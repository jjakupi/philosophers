/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:07:22 by jjakupi           #+#    #+#             */
/*   Updated: 2025/06/06 14:08:26 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->must_eat)
		philo->data->simulation_ended = 1;
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_action(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

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
	return (count == data->num_philos);
}

static void	check_death(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		if ((get_time() - data->philos[i].last_meal_time)
			>= data->time_to_die)
		{
			data->simulation_ended = 1;
			pthread_mutex_unlock(&data->death_mutex);
			print_action(&data->philos[i], "died");
			return ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
}

void	*monitor_philosophers(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->simulation_ended)
	{
		check_death(data);
		if (data->simulation_ended)
			return (NULL);
		if (check_if_all_ate(data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	check_if_all_ate(t_data *data)
{
	int	count;
	int	i;

	if (data->must_eat == -1)
		return (0);
	count = 0;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat)
			count++;
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
	if (count == data->num_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->simulation_ended = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}
