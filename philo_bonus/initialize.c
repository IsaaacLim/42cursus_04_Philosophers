#include "philo_bonus.h"

void	ft_init_philo(t_philos *philo)
{
	int		i;
	char	colors[6][10];

	ft_strncpy(colors[0], RED, 10);
	ft_strncpy(colors[1], GREEN, 10);
	ft_strncpy(colors[2], YELLOW, 10);
	ft_strncpy(colors[3], BLUE, 10);
	ft_strncpy(colors[4], PURPLE, 10);
	ft_strncpy(colors[5], CYAN, 10);
	i = -1;
	while (++i < 4)
	{
		philo[i].x = i + 1;
		philo[i].n_eaten = 0;
		philo[i].t_last_meal = 0;
		ft_strncpy(philo[i].color, colors[i % 6], 10);
	}
}
