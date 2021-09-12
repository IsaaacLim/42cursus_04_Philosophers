#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		flag;
	long	tot;

	i = 0;
	while (str[i] >= 9 && str[i] <= 13 || str[i] == ' ')
		i++;
	flag = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			flag *= -1;
		i++;
	}
	tot = 0;
	while (str[i] >= '0' && str[i] <= '9')
		tot = tot * 10 + (str[i++] - '0');
	return (tot * (long)flag);
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
	g_argv.dying = ft_atoi(argv[2]) * 1000;
	g_argv.eating = ft_atoi(argv[3]) * 1000;
	g_argv.sleeping = ft_atoi(argv[4]) * 1000;
	if (g_argv.n_philos < 0 || g_argv.dying < 0 || g_argv.eating < 0 || g_argv.sleeping < 0)
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
	return (true);
}

int	ft_time(void)
{
	struct timeval	time;
	long			millisecond;

	gettimeofday(&time, NULL);
	millisecond = time.tv_sec % 1000 * 1000 + time.tv_usec / 1000;
	return ((int)millisecond);
}

void	ft_philo_check(t_philos **philo, pthread_mutex_t death_lock)
{
	int i;

	// sleep(5);
	// if (philo[3]->t_last_meal)
	// 	printf("LAST MEAL\n");
	// else
	// 	printf("NO MEAL\n");
	// while (!g_argv.dead)
	// {
		// if (philo[0]->t_last_meal)
			// if (ft_time() - philo[0]->t_last_meal > g_argv.dying)
		// i = 0;
		// while (i < g_argv.n_philos && philo[i]->t_last_meal)
		// {
		// 	pthread_mutex_lock(&death_lock);
		// 	if (ft_time() - philo[i]->t_last_meal > g_argv.dying)
			// {
				// g_argv.dead = true;
				// printf("DEAD! %d @ %d\n", i + 1, ft_time());
			// }
		// 	pthread_mutex_unlock(&death_lock);
		// 	i++;
		// }
	// }
	// bool done;
	i = 0;
	// while (!g_argv.all_finished)
	// {
		while (i < g_argv.n_philos && g_argv.n_to_eat != -1)
		{
			if (philo[i]->n_eaten >= g_argv.n_to_eat)
				i++;
		}
		if (g_argv.n_to_eat != -1)
			g_argv.all_finished = true;
	// }
}
