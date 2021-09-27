#include "philo_bonus.h"


void	ft_philo_process(sem_t *forks, int id)
{
	sem_wait(forks);
	sem_wait(forks);
	printf("Help from %d\n", id);
	sleep(1);
	sem_post(forks);
	sem_post(forks);
}

int	main()
{
	t_philos	*philo;
	sem_t 		*forks_pointer;
	int			i;
	char		forks_name[15];

	ft_strncpy(forks_name, "fork_semaphore", 15);
	sem_unlink(forks_name);
	forks_pointer = sem_open(forks_name, O_CREAT, 0660, 3);
	if (forks_pointer == SEM_FAILED)
	{
		printf("Sem_open failed\n");
		exit (0);
	}
	philo = malloc(sizeof(t_philos) * 4);
	if (!philo)
		return (1);
	ft_init_philo(philo);
	i = -1;
	while (++i < 4)
	{
		philo[i].parent_pid = fork();
		if (philo[i].parent_pid == 0)
		{
			ft_philo_process(forks_pointer, philo[i].parent_pid);
			return (0);
		}
	}
	i = -1;
	while (++i < 4)
	{
		waitpid(philo[i].parent_pid, NULL, 0);
	}
	
	sem_close(forks_pointer);
	free(philo);
}
