/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:51:35 by jjakupi           #+#    #+#             */
/*   Updated: 2025/06/06 14:23:53 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	smart_sleep(long time, t_data *data)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->simulation_ended)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(100);
	}
}

static void	print_message(long timestamp, int id, char *action)
{
	if (!strcmp(action, "is eating"))
		printf("\033[32m\033[1m%ld %d %s\033[0m\n",
			timestamp, id, action);
	else if (!strcmp(action, "is sleeping"))
		printf("\033[34m%ld %d %s\033[0m\n",
			timestamp, id, action);
	else if (!strcmp(action, "is thinking"))
		printf("\033[36m%ld %d %s\033[0m\n",
			timestamp, id, action);
	else if (!strcmp(action, "has taken a fork"))
		printf("\033[33m%ld %d %s\033[0m\n",
			timestamp, id, action);
	else if (!strcmp(action, "died"))
		printf("\033[31m\033[1m%ld %d %s\033[0m\n",
			timestamp, id, action);
	else
		printf("%ld %d %s\n", timestamp, id, action);
}

void	print_action(t_philo *philo, char *action)
{
	long	timestamp;
	int		ended;

	pthread_mutex_lock(&philo->data->death_mutex);
	ended = philo->data->simulation_ended;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (ended && strcmp(action, "died") != 0)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_time() - philo->data->start_time;
	print_message(timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
