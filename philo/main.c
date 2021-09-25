#include "philo.h"

static void	philo_routine(t_philos *philo)
{
	pthread_mutex_lock(&g_fork[philo->fork_a]);
	ft_print(philo->x, "has taken a fork", philo->color);
	pthread_mutex_lock(&g_fork[philo->fork_b]);
	ft_print(philo->x, "has taken a fork", philo->color);
	philo->t_last_meal = ft_time();
	ft_print(philo->x, "is eating", philo->color);
	philo->n_eaten += 1;
	if (philo->n_eaten == g_argv.n_to_eat)
		g_argv.philo_finished += 1;
	ft_sleep(g_argv.eating);
	pthread_mutex_unlock(&g_fork[philo->fork_a]);
	pthread_mutex_unlock(&g_fork[philo->fork_b]);
	ft_print(philo->x, "is sleeping", philo->color);
	ft_sleep(g_argv.sleeping);
	ft_print(philo->x, "is thinking", philo->color);
	usleep(50);
}

static void	*ft_philo_thread(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->x % 2 == 1)
		usleep(10000);
	while (!g_argv.all_finished && !g_argv.dead && g_argv.n_philos != 1)
		philo_routine(philo);
	if (g_argv.n_philos == 1)
	{
		ft_print(philo->x, "has taken a fork", philo->color);
		philo->t_last_meal = ft_time();
	}
	return (NULL);
}

static void	*ft_philo_checker(t_philos *philo)
{
	int			i;

	while (!g_argv.all_finished && !g_argv.dead)
	{
		if (g_argv.philo_finished == g_argv.n_philos)
			g_argv.all_finished = true;
		i = -1;
		while (++i < g_argv.n_philos)
		{
			if (philo[i].t_last_meal != 0)
			{
				if (ft_time() - philo[i].t_last_meal > g_argv.life_span)
				{
					ft_print(philo[i].x, "died", RESET);
					g_argv.dead = true;
				}
			}
		}
	}
	return (NULL);
}

static int	ft_exit(t_philos *philo, pthread_t *th)
{
	int	i;

	i = -1;
	while (++i < g_argv.n_philos)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (1);
	}
	i = -1;
	while (++i < g_argv.n_philos)
	{
		if (pthread_mutex_destroy(&g_fork[i]) != 0)
			return (1);
	}
	if (pthread_mutex_destroy(&g_print_lock) != 0)
		return (1);
	free(th);
	free(philo);
	free(g_fork);
	return (0);
}

int	main(int argc, char *argv[])
{
	int			i;
	pthread_t	*th;
	t_philos	*philo;

	if (!(ft_init_arg(argc, argv)))
		return (-1);
	th = malloc(sizeof(pthread_t) * g_argv.n_philos);
	philo = malloc(sizeof(t_philos) * g_argv.n_philos);
	g_fork = malloc(sizeof(pthread_mutex_t) * g_argv.n_philos);
	ft_init_philo(philo);
	pthread_mutex_init(&g_print_lock, NULL);
	i = -1;
	while (++i < g_argv.n_philos)
	{
		if (pthread_create(&th[i], NULL, ft_philo_thread, &philo[i]) != 0)
			return (1);
	}
	ft_philo_checker(philo);
	ft_exit(philo, th);
}
