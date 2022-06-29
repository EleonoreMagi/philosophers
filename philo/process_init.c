/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:46:05 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 01:20:07 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_data(t_info **info, int argc, char **argv)
{
	t_info	*tmp;

	tmp = (t_info *)malloc(sizeof(t_info));
	if (!tmp)
		return (ft_error_msg("Error: failed to malloc data\n", NULL));
	tmp->phil_num = ft_atoi(argv[1]);
	tmp->forks_num = tmp->phil_num;
	tmp->t_die = ft_atoi(argv[2]);
	tmp->time_to_eat = ft_atoi(argv[3]);
	tmp->time_to_sleep = ft_atoi(argv[4]);
	if (tmp->phil_num < 1 || tmp->phil_num > 250 || tmp->t_die == -1
		|| tmp->time_to_eat == -1 || tmp->time_to_sleep == -1)
		return (ft_error_msg("Error: incorrect arguments\n", NULL));
	tmp->meals_req = -1;
	if (argc == 6)
	{
		tmp->meals_req = ft_atoi(argv[5]);
		if (tmp->meals_req == -1)
			return (ft_error_msg("Error: Wrong arguments\n", NULL));
	}
	tmp->finish = 0;
	*info = tmp;
	return (0);
}

static int	mutex_fork_init(t_info *info)
{
	int	i;

	info->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->forks_num);
	if (!info->mutex_fork)
		return (ft_error_msg("Error: Failed to malloc forks\n", NULL));
	i = 0;
	while (i < info->forks_num)
	{
		if (pthread_mutex_init(info->mutex_fork + i, NULL))
			return (ft_error_msg("Error in pthread_mutex_fork\n", NULL));
		i++;
	}
	return (0);
}

static void	philo_init(t_philo *philo, int i,
		t_info *info, pthread_mutex_t *fork)
{
	philo->idx = i + 1;
	philo->meal_count = 0;
	philo->last_meal = 0;
	philo->info = info;
	if (i == 0)
	{
		philo->left_fork = fork + info->phil_num - 1;
		philo->right_fork = fork + i;
	}
	else
	{
		philo->left_fork = fork + i - 1;
		philo->right_fork = fork + i;
	}
}

int	initiate_process(t_philo **philos, int argc, char **argv)
{
	t_info	*info;
	t_philo	*tmp;
	int		i;

	if (init_data(&info, argc, argv) == -1)
		return (FAILURE);
	if (pthread_mutex_init(&info->mutex_print, NULL))
		return (ft_error_msg("Error in pthread_mutex_print\n", NULL));
	if (mutex_fork_init(info) == -1)
		return (FAILURE);
	tmp = (t_philo *)malloc(sizeof(t_philo) * info->phil_num);
	if (!tmp)
		return (ft_error_msg("Error: Failed to malloc philos\n", NULL));
	i = 0;
	while (i < info->phil_num)
	{
		philo_init(tmp + i, i, info, info->mutex_fork);
		i++;
	}
	*philos = tmp;
	return (SUCCESS);
}
