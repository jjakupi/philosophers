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

void	print_action(t_philo *philo, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->simulation_ended)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, action);
		if (strcmp(action, "has taken a fork") == 0)
			printf("🔍 DEBUG: Philosopher %d picked up a fork at %ld ms\n",
				philo->id, timestamp);
		else if (strcmp(action, "is eating") == 0)
			printf("✅ Philosopher %d is eating at %ld ms\n",
				philo->id, timestamp);
		else if (strcmp(action, "is sleeping") == 0)
			printf("🛏️ Philosopher %d is sleeping at %ld ms\n",
				philo->id, timestamp);
		else if (strcmp(action, "is thinking") == 0)
			printf("🤔 Philosopher %d is thinking at %ld ms\n",
				philo->id, timestamp);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

