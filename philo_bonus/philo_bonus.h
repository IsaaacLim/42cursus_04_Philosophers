#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0;0m"

int		ft_atoi(const char *str);
int		ft_time(void);
void	ft_print(int philo_x, char *str, char *color);
void	ft_sleep(int duration);
//not sure if needed
char	*ft_strncpy(char *dest, char *src, unsigned int n);

#endif
