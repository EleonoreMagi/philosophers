/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:43:22 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 17:07:12 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philo	*init_data(int argc, char **argv)
{
	t_philo	*tmp;

	tmp = (t_philo *)malloc(sizeof(t_philo));
	if (!tmp)
		ft_error_msg("Error: failed to malloc philo");
	tmp->phil_num = ft_atoi(argv[1]);
	tmp->forks_num = tmp->phil_num;
	tmp->time_to_die = ft_atoi(argv[2]);
	tmp->time_to_eat = ft_atoi(argv[3]);
	tmp->time_to_sleep = ft_atoi(argv[4]);
	if (tmp->phil_num < 1 || tmp->phil_num > 250 || tmp->time_to_die == -1
		|| tmp->time_to_eat == -1 || tmp->time_to_sleep == -1)
		ft_error_msg("Error: wrong input arguments");
	tmp->meals_req = -1;
	if (argc == 6)
	{
		tmp->meals_req = ft_atoi(argv[5]);
		if (tmp->meals_req == -1)
			ft_error_msg("Error: wrong input arguments");
	}
	tmp->meal_count = 0;
	tmp->finish = 0;
	tmp->dead = 0;
	return (tmp);
}

t_philo	*init_exchange(int argc, char **argv)
{
	t_philo	*tmp;

	if (argc < 5 || argc > 6)
		ft_error_msg("Error: wrong number of arguments");
	tmp = init_data(argc, argv);
	tmp->pid = (int *)malloc(tmp->forks_num * sizeof(int));
	if (!tmp->pid)
		ft_error_msg("Error: malloc error while init pid");
	sem_unlink("/block_print");
	sem_unlink("/block_forks");
	tmp->block_print = sem_open("/block_print", O_CREAT, 0644, 1);
	tmp->block_fork = sem_open("/block_forks", O_CREAT, \
								0644, tmp->forks_num);
	if (tmp->block_print <= 0 || tmp->block_fork <= 0)
		ft_error_msg("Error: semaphore open error");
	return (tmp);
}
