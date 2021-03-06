#include "philo_bonus.h"

void	ft_error(int errno)
{
	if (errno == 1)
		printf("\033[0;31mrun: ./philo\033[0m number_of_philosophers\033[0;33m "
			"time_to_die\033[0m time_to_eat\033[0;33m time_to_sleep\033[0m "
			"[number_of_times_each_philosopher_must_eat]\n");
	else if (errno == 2)
		printf("\033[0;31mInput positive values only\033[0m\n");
	else if (errno == 3)
		printf("main.c: Sem_open failed\n");
	else if (errno == 4)
		printf("main.c: Malloc for philo failed\n");
	else if (errno == 5)
		printf("ft_philo_process: pthread_create error\n");
	else if (errno == 6)
		printf("ft_philo_process: pthread_join error\n");
	else if (errno == 7)
		printf("ft_philo_checker: kill error\n");
	exit (0);
}

static void	ft_exit(t_philos *philo, sem_t *forks)
{
	int	i;

	i = -1;
	while (++i < g_argv.n_philos)
		waitpid(philo[i].parent_pid, NULL, 0);
	sem_close(forks);
	sem_close(g_print_lock);
	free(philo);
}

/*
** 1. Store arguments globally
** 2. Create semaphores (forks)
** 3. Malloc for # of philosophers & initialize their values
** 4. Create processes (philosophers)
** 5. Wait for all child processes before exiting program
*/
int	main(int argc, char *argv[])
{
	t_philos	*philo;
	sem_t		*forks_pointer;
	char		forks_name[15];
	char		print_lock_name[16];

	ft_init_arg(argc, argv);
	ft_strncpy(forks_name, "fork_semaphore", 15);
	ft_strncpy(print_lock_name, "print_semaphore", 16);
	sem_unlink(forks_name);
	sem_unlink(print_lock_name);
	forks_pointer = sem_open(forks_name, O_CREAT, 0600, g_argv.n_philos);
	g_print_lock = sem_open(print_lock_name, O_CREAT, 0600, 1);
	if (forks_pointer == SEM_FAILED || g_print_lock == SEM_FAILED)
		ft_error(3);
	philo = malloc(sizeof(t_philos) * g_argv.n_philos);
	if (!philo)
		ft_error(4);
	ft_init_philo(philo);
	ft_init_processes(philo, forks_pointer);
	ft_exit(philo, forks_pointer);
	system("leaks philo_bonus");
}
