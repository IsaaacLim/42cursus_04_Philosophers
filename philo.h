#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0;0m"


struct s_argv {
	int	n_philos;
	int	dying;
	int	eating;
	int	sleeping;
	int	n_to_eat;
	int	philo_finished;
	bool	all_finished;
	bool	dead;
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
	int fork_a;
	int fork_b;
	int	t_last_meal;
	int	n_eaten;
}	t_philos;


bool	ft_init_arg(int argc, char *argv[]);
int		ft_atoi(const char *str);
int		ft_time(void);
//void	ft_print(int philo, char *str, char *color);


#endif
