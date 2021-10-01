#include "philo_bonus.h"

/*
** A thread for each processes that checks if its philosopher has died
** Run only if the philosohper has started eating
*/
static void	*ft_philo_checker(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!philo->dead && philo->n_eaten != g_argv.n_to_eat)
	{
		if (philo->t_last_meal != 0)
		{
			if (ft_time() - philo->t_last_meal > g_argv.life_span)
			{
				philo->dead = true;
				ft_print(*philo, "died");
				kill(0, SIGTERM);
			}
		}
	}
	return (NULL);
}

/*
** Microsleep after thinking to prevent a philosopher from being greedy
*/
static void	ft_philo_routine(t_philos *philo, sem_t *forks)
{
	sem_wait(forks);
	ft_print(*philo, "has taken a fork");
	sem_wait(forks);
	ft_print(*philo, "has taken a fork");
	philo->t_last_meal = ft_time();
	ft_print(*philo, "is eating");
	philo->n_eaten += 1;
	ft_sleep(g_argv.eating);
	sem_post(forks);
	sem_post(forks);
	ft_print(*philo, "is sleeping");
	ft_sleep(g_argv.sleeping);
	ft_print(*philo, "is thinking");
	usleep(50);
}

/*
** Each process will create individual thread to check for dead philosopher
** Run ft_philo_routine only if there are more than 1 philosopher present
*/
static void	ft_philo_process(t_philos *philo, sem_t *forks)
{
	pthread_t	checker;

	if (pthread_create(&checker, NULL, ft_philo_checker, philo) != 0)
		ft_error(5);
	if (g_argv.n_philos == 1)
	{
		ft_print(*philo, "has taken a fork");
		philo->t_last_meal = ft_time();
	}
	else
	{
		if (philo->x % 2 == 1) //test if needed or not
			usleep(10000);
		while (!philo->dead && philo->n_eaten != g_argv.n_to_eat)
			ft_philo_routine(philo, forks);
		if (pthread_join(checker, NULL) != 0)
			ft_error(6);
	}
}

/*
** Only child processes will act as a philosopher
*/
int	ft_init_processes(t_philos *philo, sem_t *forks_pointer)
{
	int	i;

	i = -1;
	while (++i < g_argv.n_philos)
	{
		philo[i].parent_pid = fork();
		if (philo[i].parent_pid == 0)
		{
			ft_philo_process(&philo[i], forks_pointer);
			return (0);
		}
	}
	return (0);
}
