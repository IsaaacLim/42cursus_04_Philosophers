#include "philo_bonus.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void	ft_philo_process(sem_t *forks, int id)
{
	sem_wait(forks);
	printf("Help from %d\n", id);
	sleep(1);
	sem_post(forks);
}

int	main()
{
	int id_1;
	int id_2;


	sem_unlink("spoon");
	sem_t *forks;
	// char forks_name[5];

	// ft_strncpy(forks_name, "spoon", 5);
	forks = sem_open("spoon", O_CREAT, 0660, 1);
	if (forks == SEM_FAILED)
	{
		printf("Sem_open failed\n");
		exit (0);
	}
	
	id_1 = fork();
	sem_unlink("spoon");

	if (id_1 == 0)
	{
		ft_philo_process(forks, id_1);
		return (0);
	}
	id_2 = fork();
	if (id_2 == 0)
	{
		ft_philo_process(forks, id_2);
		return (0);
	}

	waitpid(-1, NULL, 0);
	sem_close(forks);

	printf("%d\n", ft_atoi("  -608"));
	ft_sleep(200);
	ft_print(3, "Hello", CYAN);
}
