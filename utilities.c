#include "philo.h"

int	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	return (0);
}