/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:20:02 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/30 17:06:33 by dmillan          ###   ########.fr       */
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

typedef struct s_philo
{
	int				phil_num;
	int				forks_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_req;
	int				meal_count;
	int				finish;
	int				dead;
	int				*pid;
	sem_t			*block_print;
	sem_t			*block_fork;
	long long int	start_time;
	int				idx;
	long long int	last_meal;
	pthread_t		check_process;
}	t_philo;

t_philo		*init_exchange(int argc, char **argv);
int			ft_error_msg(char *str);
long long	get_timestamp(void);
void		upgrade_sleep(long long time, t_philo *philo);
int			ft_atoi(const char *str);
void		print_status(t_philo *philo, char *str);

#endif