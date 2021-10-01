#include "philo.h"

/*
** Function ran by the main process
** Checks if all philosophers can ate at least nth times or
**	Checks if a philosopher has died (ran only after they have started eating)
*/
void	ft_philo_checker(t_philos *philo)
{
	int	i;

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
}

/*
** Microsleep after thinking to prevent a philosopher from being greedy
*/
static void	ft_philo_routine(t_philos *philo)
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

/*
** Threads created for each philosophers
** Philosopher routine will only execute if there is more than 1 philo present
** Odd numbered philosopher be delayed to have proper thread execution order
*/
void	*ft_philo_thread(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->x % 2 == 1)
		usleep(10000);
	while (!g_argv.all_finished && !g_argv.dead && g_argv.n_philos != 1)
		ft_philo_routine(philo);
	if (g_argv.n_philos == 1)
	{
		ft_print(philo->x, "has taken a fork", philo->color);
		philo->t_last_meal = ft_time();
	}
	return (NULL);
}
