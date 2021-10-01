#include "philo_bonus.h"

void	ft_error(int errno)
{
	if (errno == 3)
		printf("Sem_open failed\n");
	exit (0);
}

static void	ft_check_neg(int num_of_vars)
{
	int	argv[5];
	int	i;

	argv[0] = g_argv.n_philos;
	argv[1] = g_argv.life_span;
	argv[2] = g_argv.eating;
	argv[3] = g_argv.sleeping;
	argv[4] = g_argv.n_to_eat;
	i = -1;
	while (++i < num_of_vars)
	{
		if (argv[i] < 0)
		{
			printf("\033[0;31mInput positive values only\033[0m\n");
			exit (1);
		}
	}
}

void	ft_init_arg(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("\033[0;31mrun: ./philo\033[0m number_of_philosophers\033[0;33m "
			"time_to_die\033[0m time_to_eat\033[0;33m time_to_sleep\033[0m "
			"[number_of_times_each_philosopher_must_eat]\n");
		exit (1);
	}
	g_argv.n_philos = ft_atoi(argv[1]);
	g_argv.life_span = ft_atoi(argv[2]);
	g_argv.eating = ft_atoi(argv[3]);
	g_argv.sleeping = ft_atoi(argv[4]);
	if (argv[5])
	{
		g_argv.n_to_eat = ft_atoi(argv[5]);
		ft_check_neg(5);
	}
	else
	{
		g_argv.n_to_eat = -1;
		ft_check_neg(4);
	}
}

void	ft_init_philo(t_philos *philo)
{
	int		i;
	char	colors[6][10];

	ft_strncpy(colors[0], RED, 10);
	ft_strncpy(colors[1], GREEN, 10);
	ft_strncpy(colors[2], YELLOW, 10);
	ft_strncpy(colors[3], BLUE, 10);
	ft_strncpy(colors[4], PURPLE, 10);
	ft_strncpy(colors[5], CYAN, 10);
	i = -1;
	while (++i < g_argv.n_philos)
	{
		philo[i].x = i + 1;
		philo[i].n_eaten = 0;
		philo[i].t_last_meal = 0;
		philo[i].dead = false;
		ft_strncpy(philo[i].color, colors[i % 6], 10);
	}
}
