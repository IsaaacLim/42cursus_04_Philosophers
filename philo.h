#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

struct s_argv {
	int	dying;
	int	eating;
	int	sleeping;
};

struct s_argv	g_argv;

typedef struct s_philo {
	int	x;
	int fork_left;
	int fork_right;
	int	last_meal;
}	t_philo;

bool	ft_init_arg(int argc, char *argv[]);
int		ft_atoi(const char *str);
int		ft_time(void);

#endif
