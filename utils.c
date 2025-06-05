/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:51:35 by jjakupi           #+#    #+#             */
/*   Updated: 2025/06/05 13:45:26 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	smart_sleep(long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
}

void	print_action(t_philo *philo, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->simulation_ended)
	{
		timestamp = get_time() - philo->data->start_time;

		if (strcmp(action, "is eating") == 0)
			printf(GREEN BOLD "%ld %d %s\n" RESET, timestamp, philo->id, action);
		else if (strcmp(action, "is sleeping") == 0)
			printf(BLUE "%ld %d %s\n" RESET, timestamp, philo->id, action);
		else if (strcmp(action, "is thinking") == 0)
			printf(CYAN "%ld %d %s\n" RESET, timestamp, philo->id, action);
		else if (strcmp(action, "has taken a fork") == 0)
			printf(YELLOW "%ld %d %s\n" RESET, timestamp, philo->id, action);
		else if (strcmp(action, "died") == 0)
			printf(RED BOLD "%ld %d %s\n" RESET, timestamp, philo->id, action);
		else
			printf("%ld %d %s\n", timestamp, philo->id, action);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
