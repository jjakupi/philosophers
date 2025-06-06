#include "philo.h"

int	is_positive_number(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	i = 0;
	while (str[i] == '0')
		i++;
	if (!str[i])
		return (0);
	return (1);
}

int	parse_arguments(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo num_philos time_to_die time_to_eat "
			"time_to_sleep [num_must_eat]\n");
		return (1);
	}
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->simulation_ended = 0;
	if (!is_positive_number(argv[1])
		|| !is_positive_number(argv[2])
		|| !is_positive_number(argv[3])
		|| !is_positive_number(argv[4])
		|| (argc == 6 && !is_positive_number(argv[5])))
	{
		printf("Error: All arguments must be positive integers.\n");
		return (1);
	}
	return (0);
}
