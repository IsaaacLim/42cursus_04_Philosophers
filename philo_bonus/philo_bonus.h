#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <pthread.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0;0m"

typedef struct s_philos {
	int		x;
	int		t_last_meal;
	int		n_eaten;
	bool	dead;
	char	color[10];
	pid_t	parent_pid;
}	t_philos;

struct s_argv {
	int		n_philos;
	int		life_span;
	int		eating;
	int		sleeping;
	int		n_to_eat;
};
struct s_argv	g_argv;

/* INITIALIZE.C */
void	ft_init_arg(int argc, char *argv[]);
void	ft_init_philo(t_philos *philo);

/* MAIN.C */
void	ft_error(int errno);

/* PHILOSOPHERS.c */
int		ft_init_processes(t_philos *philo, sem_t *forks_pointer);

/* UTILS.C */
int		ft_atoi(const char *str);
int		ft_time(void);
void	ft_sleep(int duration);
void	ft_print(t_philos philo, char *str);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

#endif
