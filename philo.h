#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct s_argv
{
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
};

struct s_argv g_argv;

int ft_atoi(const char *str);
int	ft_time(void);

#endif
