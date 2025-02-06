/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:02:15 by jjakupi           #+#    #+#             */
/*   Updated: 2025/02/06 14:51:39 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");

	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;

	// ✅ Check if this philosopher reached must_eat
	if (philo->meals_eaten == philo->data->must_eat)
		philo->data->simulation_ended = 1;

	pthread_mutex_unlock(&philo->data->death_mutex);

	print_action(philo, "is eating");
	smart_sleep(philo->data->time_to_eat);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
    if (philo->data->num_philos == 1)
    {
        print_action(philo, "has taken a fork");
        smart_sleep(philo->data->time_to_die);  // Wait for inevitable death
        return (NULL);  // Exit immediately
    }
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->simulation_ended)
	{
		print_action(philo, "is thinking");
		if (philo->data->simulation_ended) break;
		usleep(200);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			print_action(philo, "has taken a fork");
			usleep(100);
			pthread_mutex_lock(philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			print_action(philo, "has taken a fork");
			usleep(100);
			pthread_mutex_lock(philo->right_fork);
		}
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->last_meal_time = get_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->death_mutex);
		smart_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep);
		usleep(500);
	}
	return (NULL);
}
