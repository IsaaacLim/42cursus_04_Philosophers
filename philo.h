#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define RESET "\033[0;0m"

struct s_argv {
	int	dying;
	int	eating;
	int	sleeping;
	int	n_philos;
};

struct s_argv	g_argv;

typedef struct s_test {
	int	data;
} t_test;

struct s_philo_info {
	int	x;
};

typedef struct s_philos {
	int	x;
	int	t_last_meal;
	int	n_eaten;
}	t_philos;


bool	ft_init_arg(int argc, char *argv[]);
int		ft_atoi(const char *str);
int		ft_time(void);

#endif
