/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:20:49 by moztop            #+#    #+#             */
/*   Updated: 2024/08/03 18:22:51 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	philo_eat(t_philo *philo)
{
	if (philo->index % 2)
	{
		pthread_mutex_lock(&philo->l_fork);
		printf("%lld Philosopher %i %s\n", philo->main->started - get_timestamp(),
			philo->index + 1, MSG_FORK);
	}
	pthread_mutex_lock(philo->r_fork);
	printf("%lld Philosopher %i %s\n", philo->main->started - get_timestamp(),
			philo->index + 1, MSG_FORK);
	if (!(philo->index % 2))
	{
		pthread_mutex_lock(&philo->l_fork);
		printf("%lld Philosopher %i %s\n", philo->main->started - get_timestamp(),
			philo->index + 1, MSG_FORK);
	}
	printf("%lld Philosopher %i %s\n", philo->main->started - get_timestamp(),
		philo->index + 1, MSG_EAT);
	ft_usleep(philo->main->time_to_eat);
}
