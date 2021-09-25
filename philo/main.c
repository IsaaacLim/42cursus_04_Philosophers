#include "philo.h"

void *ft_philo_checker(t_philos *philo)
{
	int			i;

	while (!g_argv.all_finished && !g_argv.dead)
	{
		if (g_argv.philo_finished == g_argv.n_philos)
			g_argv.all_finished = true;
		i = 0;
		while (i < g_argv.n_philos)
		{
			if (philo[i].t_last_meal != 0)
			{
				if (ft_time() - philo[i].t_last_meal > g_argv.life_span)
				{
					ft_print(philo[i].x, "died", RESET);
					g_argv.dead = true;
				}
			}
			i++;
		}
	}
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

void	ft_sleep(int duration)
{
	int	time;

	time = ft_time();
	while (ft_time() - time < duration)
		usleep(500);
}

void	philo_routine(t_philos *philo, char *color)
{
	pthread_mutex_lock(&g_fork[philo->fork_a]);
	ft_print(philo->x, "has taken a fork", color);
	pthread_mutex_lock(&g_fork[philo->fork_b]);
	ft_print(philo->x, "has taken a fork", color);
	philo->t_last_meal = ft_time();
	ft_print(philo->x, "is eating", color);
	philo->n_eaten += 1;
	if (philo->n_eaten == g_argv.n_to_eat)
		g_argv.philo_finished += 1;
	ft_sleep(g_argv.eating);
	pthread_mutex_unlock(&g_fork[philo->fork_a]);
	pthread_mutex_unlock(&g_fork[philo->fork_b]);
	ft_print(philo->x, "is sleeping", color);
	ft_sleep(g_argv.sleeping);
	ft_print(philo->x, "is thinking", color);
	usleep(50);
}

void *ft_philo_thread(void *arg)
{
	t_philos *philo;
	philo = (t_philos *)arg;

	char colors[6][10] = {RED, GREEN, YELLOW, BLUE, PURPLE, CYAN};
	if (philo->x % 2 == 1)
		usleep(10000);
	while (!g_argv.all_finished && !g_argv.dead && g_argv.n_philos != 1)
		philo_routine(philo, colors[(philo->x - 1) % 6]);
	if (g_argv.n_philos == 1)
	{
		ft_print(philo->x, "has taken a fork", RED);
		philo->t_last_meal = ft_time();
	}
	return (NULL);
}

int main(int argc, char *argv[])
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
