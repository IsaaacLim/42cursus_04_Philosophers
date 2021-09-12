#include "philo.h"

pthread_mutex_t *fork_x;
pthread_mutex_t print_lock;
pthread_mutex_t death_lock;

void	ft_print(int philo, char *str, char *color)
{
	if (!g_argv.all_finished && !g_argv.dead)
	{
		pthread_mutex_lock(&print_lock);
		printf("%d %s%i %s%s\n", ft_time(), color, philo, str, RESET);
		pthread_mutex_unlock(&print_lock);
	}
}

void	philo_routine(t_philos *philo, char *color)
{
	pthread_mutex_lock(&fork_x[philo->x - 1]);
	ft_print(philo->x, "has taken a fork", color);
	philo->t_last_meal = ft_time();
	pthread_mutex_lock(&fork_x[philo->x % g_argv.n_philos]);
	ft_print(philo->x, "has taken a fork", color);
	ft_print(philo->x, "is eating", color);
	philo->n_eaten += 1;
	if (philo->n_eaten == g_argv.n_to_eat)
		g_argv.philo_finished += 1;
	usleep(g_argv.eating);
	philo->t_last_meal = ft_time();
	pthread_mutex_unlock(&fork_x[philo->x - 1]);
	pthread_mutex_unlock(&fork_x[philo->x % g_argv.n_philos]);
	ft_print(philo->x, "is sleeping", color);
	usleep(g_argv.sleeping);
	ft_print(philo->x, "is thinking", color);
}

void *philo_thread(void *arg)
{
	t_philos *philo;
	philo = (t_philos *)arg;

	char colors[6][10] = {RED, GREEN, YELLOW, BLUE, PURPLE, CYAN};
	if (philo->x % 2 == 0)
		usleep (150000);
	while (!g_argv.all_finished && !g_argv.dead)
	{
		philo_routine(philo, colors[(philo->x - 1) % 6]);
	}
	return (NULL);
}

void	*ft_philo_checker(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!philo->t_last_meal)
		;
	while (!g_argv.all_finished && !g_argv.dead)
	{
		if (g_argv.philo_finished == g_argv.n_philos)
			g_argv.all_finished = true;
		pthread_mutex_lock(&death_lock);
		if (ft_time() - philo->t_last_meal > g_argv.dying / 1000)
		{
			ft_print(philo->x, "died", RESET);
			g_argv.dead = true;
		}
		pthread_mutex_unlock(&death_lock);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int n;
	int	i;
	pthread_t *th;
	t_philos	**philo;

	if (!(ft_init_arg(argc, argv)))
		return (-1);

	th = malloc(sizeof(pthread_t) * g_argv.n_philos);
	fork_x = malloc(sizeof(pthread_mutex_t) * g_argv.n_philos);
	philo = malloc(sizeof(t_philos *) * g_argv.n_philos);
	n = 0;
	while (n < g_argv.n_philos)
	{
		pthread_mutex_init(&fork_x[n], NULL);
		philo[n] = malloc(sizeof(t_philos));
		philo[n]->x = n + 1;
		philo[n]->n_eaten = 0;
		philo[n]->t_last_meal = 0;
		n++;
	}
	pthread_mutex_init(&print_lock, NULL);
	pthread_mutex_init(&death_lock, NULL);
	n = 0;
	while (n < g_argv.n_philos)
	{
		if (pthread_create(&th[n], NULL, philo_thread, &(philo[n]->x)) != 0)
			return (1);
		n++;
	}
	pthread_t *checker;
	checker = malloc(sizeof(pthread_t) * g_argv.n_philos);
	n = 0;
	while (n < g_argv.n_philos)
	{
		if (pthread_create(&checker[n], NULL, ft_philo_checker, &(philo[n]->x)) != 0)
			return (1);
		n++;
	}
	i = 0;
	while (i < g_argv.n_philos)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (1);
		if (pthread_join(checker[i], NULL) != 0)
			return (1);
		i++;
	}
	n = -1;
	while (++n < g_argv.n_philos)
	{
		pthread_mutex_destroy(&fork_x[n]);
		printf("%d %d t_last_meal\n", philo[n]->t_last_meal, n + 1);
		free(philo[n]);
	}
	pthread_mutex_destroy(&print_lock);
	pthread_mutex_destroy(&death_lock);
	free(fork_x);
	free(th);
	free(checker);
	free(philo);
}
