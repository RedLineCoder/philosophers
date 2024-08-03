/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:20:49 by moztop            #+#    #+#             */
/*   Updated: 2024/08/03 18:30:44 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_diestamp);
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
	philo->diestamp = get_timestamp() + philo->main->time_to_die;
	philo->times_eaten++;
	ft_usleep(philo->main->time_to_eat);
	pthread_mutex_unlock(&philo->m_diestamp);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
