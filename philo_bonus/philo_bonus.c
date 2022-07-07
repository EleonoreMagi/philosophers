/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:27:19 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 17:06:47 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_process(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->finish)
	{
		usleep(100);
		if (get_timestamp() - philo->last_meal > philo->time_to_die)
		{
			philo->dead = 1;
			sem_wait(philo->block_print);
			printf("%lld %d %s\n", \
					get_timestamp() - philo->last_meal, philo->idx, "died");
			philo->finish = 1;
			break ;
		}
		if (philo->meals_req != -1 && philo->meal_count >= philo->meals_req)
		{
			philo->finish = 1;
			break ;
		}
	}
	if (philo->dead)
		exit (1);
	else
		exit (0);
}

void	start_philo_process(t_philo *philo)
{
	if (pthread_create(&philo->check_process,
			NULL, &check_process, philo))
		ft_error_msg("Error: failed to create the thread");
	if (philo->idx % 2 == 1)
		usleep(1000);
	while (1)
	{
		print_status(philo, "is thinking");
		sem_wait(philo->block_fork);
		print_status(philo, "has taken a fork");
		sem_wait(philo->block_fork);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		upgrade_sleep(philo->time_to_eat, philo);
		philo->last_meal = get_timestamp();
		sem_post(philo->block_fork);
		sem_post(philo->block_fork);
		philo->meal_count += 1;
		print_status(philo, "is sleeping");
		upgrade_sleep(philo->time_to_sleep, philo);
	}
	if (pthread_join(philo->check_process, NULL))
		ft_error_msg("Error: failed to join the thread");
}

void	exit_all(t_philo **philo)
{
	t_philo	*tmp;
	int		i;
	int		status;

	tmp = *philo;
	i = 0;
	while (i < tmp->phil_num)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < tmp->phil_num)
				kill(tmp->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(tmp->block_print);
	sem_close(tmp->block_fork);
	sem_unlink("/block_print");
	sem_unlink("/block_forks");
	free(tmp->pid);
	free(tmp);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;

	philo = init_exchange(argc, argv);
	i = 0;
	philo->start_time = get_timestamp();
	while (i < philo->phil_num)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			ft_error_msg("Error: failed to create fork");
		if (philo->pid[i] == 0)
		{
			philo->idx = i + 1;
			philo->last_meal = get_timestamp();
			start_philo_process(philo);
		}
		i++;
	}
	exit_all(&philo);
	return (0);
}
