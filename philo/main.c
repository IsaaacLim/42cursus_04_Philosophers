#include "philo.h"

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
	if (g_argv.n_to_eat == 0)
		return (0);
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
