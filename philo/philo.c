/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:27:19 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 01:19:35 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->mutex_print);
	if (!philo->info->finish)
		printf("%lld %d %s\n",
			get_timestamp() - philo->info->start_time, philo->idx, str);
	pthread_mutex_unlock(&philo->info->mutex_print);
}

void	*loop_process(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->info->finish)
	{
		print_status(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		upgrade_sleep(philo->info->time_to_eat, philo->info);
		philo->last_meal = get_timestamp();
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (!philo->info->finish)
			philo->meal_count += 1;
		print_status(philo, "is sleeping");
		upgrade_sleep(philo->info->time_to_sleep, philo->info);
	}
	return (0);
}

void	*check_process(void *args)
{
	t_philo	*philos;
	int		i;
	int		finished_eating;

	philos = (t_philo *)args;
	while (!philos->info->finish)
	{
		i = -1;
		finished_eating = 0;
		while (++i < philos->info->phil_num)
		{
			if (get_timestamp() - philos[i].last_meal > philos->info->t_die)
			{
				print_status(philos + i, "died");
				philos->info->finish = 1;
				break ;
			}
			if (philos->info->meals_req != -1 && \
				philos[i].meal_count >= philos->info->meals_req)
				finished_eating++;
		}
		if (finished_eating == philos->info->phil_num)
			philos->info->finish = 1;
	}
	return (0);
}

void	start_simulation(t_philo *philos)
{
	int	i;

	i = 0;
	philos->info->start_time = get_timestamp();
	while (i < philos->info->phil_num)
	{
		philos[i].last_meal = get_timestamp();
		if (pthread_create(&philos[i].pth_id, NULL, &loop_process, &philos[i]))
			ft_error_msg("Error: failed to create the thread\n", NULL);
		pthread_detach(philos[i].pth_id);
		usleep(50);
		i++;
	}
	if (pthread_create(&philos->info->check_process,
			NULL, &check_process, philos))
		ft_error_msg("Error: failed to create the check thread\n", NULL);
	if (pthread_join(philos->info->check_process, NULL))
		ft_error_msg("Error: failed to join the thread\n", NULL);
	i = 0;
	while (i < philos->info->forks_num)
	{
		pthread_mutex_destroy(&philos->info->mutex_fork[i++]);
	}
	pthread_mutex_destroy(&philos->info->mutex_print);
}

int	main(int argc, char **argv)
{
	t_philo	*philosopher;

	if (argc < 5 || argc > 6)
		return (ft_error_msg("Error: incorrect number of arguments\n", NULL));
	if (initiate_process(&philosopher, argc, argv) == FAILURE)
		return (0);
	start_simulation(philosopher);
	return (0);
}
