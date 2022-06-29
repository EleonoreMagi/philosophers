/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:27:19 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 01:41:07 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	initiate_process(int argc, char **argv, t_info *info)
{
	info->meals_required = -1;
	if (argc > 4 && argc < 7)
	{
		info->phil_num = ft_atoi(argv[1]);
		info->time_to_die = ft_atoi(argv[2]);
		info->time_to_eat = ft_atoi(argv[3]);
		info->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			info->meals_required = ft_atoi(argv[5]);
	}
	else
		return (FAIL);
	if (info->phil_num < 1 || info->time_to_die == -1
		|| info->time_to_eat == -1 || info->time_to_sleep == -1)
		return (FAIL);
	if (argc == 6 && info->meals_required < 1)
		return (FAIL);
	return (SUCCESS);
}

void	*check_philos(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	while (philo->dead)
	{
		usleep(500);
		if (get_timestamp() - philo->last_meal > philo->info->time_to_die)
		{
			sem_wait(philo->info->print);
			printf("%lld %d %s\n", get_timestamp() - philo->info->start_time,
				philo->idx + 1, "died");
			philo->dead = 0;
			stop_all(philo, 0);
		}
		if (philo->info->meals_required != -1
			&& philo->meal_count >= philo->info->meals_required)
			philo->dead = 0;
	}
	return (0);
}

void	philo_process_loop(t_philo *philo)
{
	if (pthread_create(&philo->check_process,
			NULL, &check_philos, philo) != 0)
		ft_error_msg("Error while creating a thread\n", NULL);
	pthread_detach(philo->check_process);
	while (philo->dead)
	{
		print_status(philo, "is thinking");
		sem_wait(philo->info->forks);
		print_status(philo, "has taken a fork");
		sem_wait(philo->info->forks);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		upgrade_sleep(philo->info->time_to_eat, philo);
		philo->last_meal = get_timestamp();
		philo->meal_count++;
		print_status(philo, "is sleeping");
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
		upgrade_sleep(philo->info->time_to_sleep, philo);
	}
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (initiate_process(argc, argv, &info) == -1)
		ft_error_msg("Error: incorrect arguments\n", NULL);
	if (initiate_philos(&philo, &info) == -1)
		return (0);
	create_threads(philo);
	return (0);
}
