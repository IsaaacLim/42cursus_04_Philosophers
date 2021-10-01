#include "philo_bonus.h"

/*
** 1. Store arguments globally
** 2. Malloc for # of philos & initialize their values
** 3. Create semaphores (forks)
** 4. Create processes (philosophers)
** 5. Wait for child processes before exiting program
*/
int	main(int argc, char *argv[])
{
	t_philos	*philo;
	sem_t 		*forks_pointer;
	int			i;
	char		forks_name[15];

	ft_init_arg(argc, argv);
	philo = malloc(sizeof(t_philos) * g_argv.n_philos);
	if (!philo)
		return (1);
	ft_init_philo(philo);
	ft_strncpy(forks_name, "fork_semaphore", 15);
	sem_unlink(forks_name);
	forks_pointer = sem_open(forks_name, O_CREAT, 0600, g_argv.n_philos);
	if (forks_pointer == SEM_FAILED)
		ft_error(3);
	ft_init_processes(philo, forks_pointer);
	i = -1;
	while (++i < g_argv.n_philos)
		waitpid(philo[i].parent_pid, NULL, 0);
	sem_close(forks_pointer);
	free(philo);
}
