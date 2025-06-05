/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:02:15 by jjakupi           #+#    #+#             */
/*   Updated: 2025/06/05 14:56:27 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


static void	handle_single_philo(t_philo *philo)
{
	print_action(philo, "has taken a fork");
	smart_sleep(philo->data->time_to_die);
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->data->simulation_ended = 1;
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_action(philo, "died");
}

static void	initial_delay(t_philo *philo)
{
	if (philo->id % 2 == 0)
		smart_sleep(2);
}

static void	pickup_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		smart_sleep(1);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		smart_sleep(2);
		pthread_mutex_lock(philo->right_fork);
	}
	print_action(philo, "has taken a fork");
}

static void	eat_and_release(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->death_mutex);
	smart_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	sleep_and_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep);
	print_action(philo, "is thinking");
	smart_sleep(1);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo = arg;

	if (philo->data->num_philos == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	initial_delay(philo);
	while (!philo->data->simulation_ended)
	{
		sleep_and_think(philo);
		pickup_forks(philo);
		eat_and_release(philo);
	}
	return (NULL);
}
