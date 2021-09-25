#include "philo.h"

bool	ft_init_arg(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("\033[0;31mrun: ./philo\033[0m number_of_philosophers\033[0;33m "
			"time_to_die\033[0m time_to_eat\033[0;33m time_to_sleep\033[0m "
			"[number_of_times_each_philosopher_must_eat]\n");
		return (false);
	}
	g_argv.n_philos = ft_atoi(argv[1]);
	g_argv.life_span = ft_atoi(argv[2]);
	g_argv.eating = ft_atoi(argv[3]);
	g_argv.sleeping = ft_atoi(argv[4]);
	if (g_argv.n_philos < 0 || g_argv.life_span < 0 || g_argv.eating < 0 || g_argv.sleeping < 0)
	{
		printf("\033[0;31mInput positive values only\033[0m\n");
		return (false);
	}
	if (argv[5])
	{
		g_argv.n_to_eat = ft_atoi(argv[5]);
		if (g_argv.n_to_eat < 0)
			{
				printf("\033[0;31mInput positive values only\033[0m\n");
				return (false);
			}
	}
	else
		g_argv.n_to_eat = -1;
	g_argv.philo_finished = 0;
	return (true);
}

void ft_init_philo(t_philos *philo)
{
	int i;

	i = 0;
	while (i < g_argv.n_philos)
	{
		pthread_mutex_init(&g_fork[i], NULL);
		philo[i].x = i + 1;
		if (i % 2 == 0)
		{
			philo[i].fork_a = (i + 1) % g_argv.n_philos;
			philo[i].fork_b = i;
		}
		else
		{
			philo[i].fork_a = i;
			philo[i].fork_b = (i + 1) % g_argv.n_philos;
		}
		philo[i].n_eaten = 0;
		philo[i].t_last_meal = 0;
		i++;
	}
}
