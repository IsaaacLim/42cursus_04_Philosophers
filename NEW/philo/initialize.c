#include "philo.h"

static bool	ft_check_neg(int variables)
{
	int	argv[5];
	int	i;

	argv[0] = g_argv.n_philos;
	argv[1] = g_argv.life_span;
	argv[2] = g_argv.eating;
	argv[3] = g_argv.sleeping;
	argv[4] = g_argv.n_to_eat;
	i = -1;
	while (++i < variables)
	{
		if (argv[i] < 0)
		{
			printf("\033[0;31mInput positive values only\033[0m\n");
			return (false);
		}
	}
	return (true);
}

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
	g_argv.philo_finished = 0;
	if (argv[5])
	{
		g_argv.n_to_eat = ft_atoi(argv[5]);
		if (!ft_check_neg(5))
			return (false);
	}
	else
	{
		g_argv.n_to_eat = -1;
		if (!ft_check_neg(4))
			return (false);
	}
	return (true);
}

static void	ft_stdout_color(char *philo_color, int i)
{
	char	colors[6][10];

	ft_strncpy(colors[0], RED, 10);
	ft_strncpy(colors[1], GREEN, 10);
	ft_strncpy(colors[2], YELLOW, 10);
	ft_strncpy(colors[3], BLUE, 10);
	ft_strncpy(colors[4], PURPLE, 10);
	ft_strncpy(colors[5], CYAN, 10);
	ft_strncpy(philo_color, colors[i % 6], 10);
}

/*
** Designed to prevent deadlock with order of forks taken as:
**	- Odd numbered philosophers will take left one first
**	- Even numbered philosohers will take right one first
*/
void	ft_init_philo(t_philos *philo)
{
	int	i;

	i = -1;
	while (++i < g_argv.n_philos)
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
		ft_stdout_color(philo[i].color, i);
	}
}
