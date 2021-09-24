#include "philo.h"

// int	main()
// {
// 	int id_1;
// 	int id_2;

// 	id_1 = fork();
// 	id_2 = fork();
// 	printf("Hellp from %d-%d\n", id_1, id_2);

// 	// if (id_1 != 0)
// 	// {
// 	// 	if (id_2 != 0)
// 	// 		printf("Hello from %d-%d\n", id_1, id_2);
// 	// 	else
// 	// 		printf("Hellp from %d-%d\n", id_1, id_1);
// 	// }
// 	// else
// 	// {
// 	// 	if (id_2 != 0)
// 	// 		printf("Hellp from %d-%d\n", id_1, id_2);
// 	// 	else
// 	// 		printf("Hellp from %d-%d\n", id_1, id_1);
// 	// }
// }

void *ft_philo_checker(void *arg)
{
	t_philos *philo;
	philo = (t_philos *)arg;

	for (int i = 0; i < g_argv.n_philos; i++)
		printf("From checker %d\n", philo[i].x);
	return (NULL);
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

void *ft_philo_thread(void *arg)
{
	t_philos *philo;
	philo = (t_philos *)arg;

	printf("Thread %d\n", philo->x);
	return (NULL);
}

//test with 0 philo input
int main(int argc, char *argv[])
{
	int			i;
	pthread_t	*th;
	t_philos	*philo;
	pthread_t	checker;

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
	if (pthread_create(&checker, NULL, ft_philo_checker, philo) != 0)
		return (1);
	ft_exit(philo, th, checker);
}
