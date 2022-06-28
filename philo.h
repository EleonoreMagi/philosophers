/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:20:02 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/28 22:26:22 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int				philos_num;
	int				forks_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_counter;
	int				last_meal;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_printf;
	long long int	start_time;
	pthread_t		check_monitor;
}t_info;

typedef struct s_philo
{
	int				idx;
	int				eat_count;
	long long int	t_meal;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		pth_thread;
}t_philo;

int			init_philos(t_philo **philos, int argc, char **argv);
int			ft_error(char *str);
long long	find_time(void);
void		upgrade_sleep(long long time, t_data *data);

#endif