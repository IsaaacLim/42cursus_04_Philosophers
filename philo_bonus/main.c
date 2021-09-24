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

void *philo_thread(void *arg)
{
	t_philos *philo;
	philo = (t_philos *)arg;

	for (int i = 0; i < 2; i++)
		printf("Thread %d\n", philo[i].fork_a);
	return (NULL);
}

void philo_init(t_philos *philo)
{
	int i;

	i = 0;
	while (i < g_argv.n_philos)
	{
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

//test with 0 philo input
int main(int argc, char *argv[])
{
	int n;
	pthread_t th[3];
	t_philos *philo;

	if (!(ft_init_arg(argc, argv)))
		return (-1);
	philo = malloc(sizeof(t_philos) * g_argv.n_philos);
	philo_init(philo);
	printf("%d\n", philo[3].fork_b);
	pthread_create(&th[0], NULL, philo_thread, philo);
	pthread_join(th[0], NULL);
	free(philo);
}
