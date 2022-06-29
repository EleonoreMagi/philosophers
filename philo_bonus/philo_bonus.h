/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:20:02 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 01:40:38 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>

# define SUCCESS 0
# define FAIL -1

typedef struct s_info
{
	int				phil_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				finish;
	long long int	start_time;
	int				philos_eat;
	sem_t			*forks;
	sem_t			*print;
}	t_info;

typedef struct s_philo
{
	pid_t			fk_id;
	long long int	last_meal;
	int				idx;
	int				meal_count;
	int				dead;
	pthread_t		check_process;
	t_info			*info;
}	t_philo;

int			initiate_philos(t_philo **philo, t_info *info);
int			ft_error_msg(char *str, t_philo *ptr);
long long	get_timestamp(void);
void		upgrade_sleep(long long time, t_philo *philo);
int			ft_atoi(const char *str);
void		print_status(t_philo *philo, char *str);
void		stop_all(t_philo *philo, int a);
int			create_threads(t_philo *philo);
int			ft_atoi(const char *str);
void		philo_process_loop(t_philo *philo);

#endif