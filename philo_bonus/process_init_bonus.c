/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:46:05 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 01:44:23 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_data(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->phil_num)
	{
		philo[i].last_meal = 0;
		philo[i].info = info;
		philo[i].idx = i;
		philo[i].meal_count = 0;
		philo[i].dead = 1;
		i++;
	}
}

int	initiate_philos(t_philo **philo, t_info *info)
{
	int	i;

	i = 0;
	info->finish = 1;
	*philo = malloc(sizeof(t_philo) * info->phil_num);
	if (!philo)
		ft_error_msg("Error malloc", NULL);
	sem_unlink("print");
	sem_unlink("forks");
	info->forks = sem_open("forks", O_CREAT, 0644, info->phil_num);
	info->print = sem_open("print", O_CREAT, 0644, 1);
	if (info->forks <= 0 || info->print <= 0)
		ft_error_msg("Error: semaphore open error", *philo);
	set_data(*philo, info);
	return (0);
}

void	forks_wait(t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	while (i < philo->info->phil_num)
	{
		waitpid(philo[i].fk_id, &status, 0);
		if (status)
			stop_all(philo, 1);
		i++;
	}
	sem_close(philo->info->forks);
	sem_close(philo->info->print);
	sem_unlink("print");
	sem_unlink("forks");
	free(philo);
}

int	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	philo->info->start_time = get_timestamp();
	while (i < philo->info->phil_num)
	{
		philo[i].fk_id = fork();
		philo[i].last_meal = get_timestamp();
		if (philo[i].fk_id == 0)
			philo_process_loop(&philo[i]);
		usleep(100);
		i++;
	}
	forks_wait(philo);
	return (0);
}

void	stop_all(t_philo *philo, int a)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	tmp = philo - philo->idx;
	while (i < philo->info->phil_num)
	{
		if (tmp[i].fk_id != 0 && tmp[i].fk_id != philo->fk_id)
			kill(tmp[i].fk_id, SIGKILL);
		i++;
	}
	if (a == 0)
		exit(1);
}
