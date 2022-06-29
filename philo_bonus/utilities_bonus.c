/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:48:48 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 01:46:22 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, char *str)
{
	sem_wait(philo->info->print);
	if (!philo->info->finish)
		printf("%lld %d %s\n",
			get_timestamp() - philo->info->start_time, philo->idx + 1, str);
	sem_post(philo->info->print);
}

int	ft_error_msg(char *str, t_philo *ptr)
{
	printf("%s\n", str);
	if (!ptr)
		free(ptr);
	exit(0);
}

long long	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	upgrade_sleep(long long ms, t_philo *philo)
{
	long long int	start;
	long long int	end;

	start = get_timestamp();
	end = get_timestamp();
	while (philo->info->finish && end - start < ms)
	{
		usleep(500);
		end = get_timestamp();
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
