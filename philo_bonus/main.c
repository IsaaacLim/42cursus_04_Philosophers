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
	int			i;
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!g_argv.all_finished && !g_argv.dead)
	{
		if (g_argv.all_finished == g_argv.n_philos)
			g_argv.all_finished = true;
		i = 0;
		while (i < g_argv.n_philos)
		{
			if (philo[i].t_last_meal != 0)
			{
				if (ft_time() - philo[i].t_last_meal > (g_argv.life_span / 1000))
				{
					ft_print(philo[i].x, "died", RESET);
					g_argv.dead = true;
				}
			}
			i++;
		}
	}
	// for (int i = 0; i < g_argv.n_philos; i++)
		// printf("From checker %d\n", philo[i].x);
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

void	philo_routine(t_philos *philo, char *color)
{
		pthread_mutex_lock(&g_fork[philo->fork_a]);
		// ft_print(philo->x, "has taken a fork");
		ft_print(philo->x, "has taken a fork", color);
	//	printf("\t%d\n", philo->fork_a);
		pthread_mutex_lock(&g_fork[philo->fork_b]);
		// ft_print(philo->x, "has taken a fork");
		ft_print(philo->x, "has taken a fork", color);
	//	printf("\t%d\n", philo->fork_b);
	//	usleep(50);
		philo->t_last_meal = ft_time();
		// ft_print(philo->x, "is eating");
		ft_print(philo->x, "is eating", color);
		philo->n_eaten += 1;
		if (philo->n_eaten == g_argv.n_to_eat)
			g_argv.philo_finished += 1;
		usleep(g_argv.eating);
		pthread_mutex_unlock(&g_fork[philo->fork_a]);
		pthread_mutex_unlock(&g_fork[philo->fork_b]);
		// ft_print(philo->x, "is sleeping");
		ft_print(philo->x, "is sleeping", color);
		usleep(g_argv.sleeping);
		// ft_print(philo->x, "is thinking");
		ft_print(philo->x, "is thinking", color);
		usleep(50);
}

void *ft_philo_thread(void *arg)
{
	t_philos *philo;
	philo = (t_philos *)arg;

	char colors[6][10] = {RED, GREEN, YELLOW, BLUE, PURPLE, CYAN};
	if (philo->x % 2 == 1 && philo->x != 1)
		usleep (15000);
	while (!g_argv.all_finished && !g_argv.dead)
	{
		philo_routine(philo, colors[(philo->x - 1) % 6]);
		i++;
	}
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
