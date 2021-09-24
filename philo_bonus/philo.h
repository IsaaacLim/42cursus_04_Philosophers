#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

struct s_argv {
	int		n_philos;
	int		life_span;
	int		eating;
	int		sleeping;
	int		n_to_eat;
	int		philo_finished;
	bool	all_finished;
	bool	dead;
};

struct s_argv g_argv;

typedef struct s_philos {
	int	x;
	int	fork_a;
	int	fork_b;
	int	t_last_meal;
	int	n_eaten;
}	t_philos;

bool	ft_init_arg(int argc, char *argv[]);
int		ft_time(void);

#endif
