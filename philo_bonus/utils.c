#include "philo_bonus.h"

char *ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int ft_atoi(const char *str)
{
	int		i;
	int		flag;
	long	tot;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	flag = 1;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			flag *= -1;
		i++;
	}
	tot = 0;
	while (str[i] >= '0' && str[i] <= '9')
		tot = tot * 10 + (str[i++] - '0');
	return (tot * (long)flag);
}

int	ft_time(void)
{
	struct timeval	time;
	long			milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = time.tv_sec % 1000 * 1000 + time.tv_usec / 1000;
	return ((int)milliseconds);
}

void	ft_sleep(int duration)
{
	int	time;

	time = ft_time();
	while (ft_time() - time < duration)
		usleep(500);
}

void	ft_print(t_philos philo, char *str)
{
	printf("%06d %s%i %s%s\n", ft_time(), philo.color, philo.x, str, RESET);
}
