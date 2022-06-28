/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:27:19 by dmillan           #+#    #+#             */
/*   Updated: 2022/06/28 22:33:43 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philosopher;

	if (argc < 5 || argc > 6)
		return (ft_error_msg("Error: Incorrect number of arguments"));
	if (initiate_philo_process(&philosopher, argc, argv) == -1)
		return (0);
	start_simulation(philosopher);
	return (0);
}