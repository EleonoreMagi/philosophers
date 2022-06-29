/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:20:02 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 01:20:42 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define SUCCESS 0
# define FAILURE -1

typedef struct s_info
{
	int				phil_num;
	int				forks_num;
	int				t_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_req;
	int				finish;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_print;
	long long int	start_time;
	pthread_t		check_process;
}	t_info;

typedef struct s_philo
{
	int				idx;
	int				meal_count;
	long long int	last_meal;
	t_info			*info;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		pth_id;
}	t_philo;

int			initiate_process(t_philo **philos, int argc, char **argv);
int			ft_error_msg(char *str, t_philo *philo);
long long	get_timestamp(void);
void		upgrade_sleep(long long time, t_info *info);
int			ft_atoi(const char *str);

#endif