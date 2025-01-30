#include "philosophers.h"

int	parse_arguments(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [num_must_eat]\n");
		return (1);
	}

	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
	data->simulation_ended = 0;

	// Validate values
	if (data->num_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0 ||
		data->time_to_sleep < 0 || (argc == 6 && data->must_eat <= 0))
	{
		printf("Error: Invalid argument values.\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(&data, argc, argv) != 0)
		return (1);

	if (init_data(&data) != 0)
		return (1);

	if (start_threads(&data) != 0)
	{
		cleanup(&data); // ✅ Cleanup in case of failure
		return (1);
	}

	cleanup(&data); // ✅ Ensure proper cleanup before exiting
	return (0);
}

