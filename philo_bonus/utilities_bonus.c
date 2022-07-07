/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:48:48 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 17:07:31 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, char *str)
{
	sem_wait(philo->block_print);
	if (!philo->finish)
		printf("%lld %d %s\n", get_timestamp()
			- philo->start_time, philo->idx, str);
	sem_post(philo->block_print);
}

int	ft_error_msg(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	exit(0);
}

long long	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	upgrade_sleep(long long time, t_philo *philo)
{
	long long	t;

	t = get_timestamp();
	while (!philo->finish)
	{
		if (get_timestamp() - t >= time)
			break ;
		usleep(500);
	}
}

int	ft_atoi(const char *str)
{
	long int	num;
	int			i;

	num = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || \
			str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && num != -1)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num = num * 10 + str[i] - '0';
		}
		else
			num = -1;
		if (num > 2147483647)
			num = -1;
		i++;
	}
	return (num);
}
