/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:20:49 by moztop            #+#    #+#             */
/*   Updated: 2024/08/03 21:04:09 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	join_philos(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->philo_count)
		pthread_join(main->philosophers[i].thread, NULL);
}

void	take_forks(t_philo *philo)
{
	if (philo->index % 2)
	{
		pthread_mutex_lock(&philo->l_fork);
		printf("%lld Philosopher %i %s\n", get_timestamp()
			- philo->main->started, philo->index + 1, MSG_FORK);
	}
	pthread_mutex_lock(philo->r_fork);
	printf("%lld Philosopher %i %s\n", get_timestamp() - philo->main->started,
		philo->index + 1, MSG_FORK);
	if (!(philo->index % 2))
	{
		pthread_mutex_lock(&philo->l_fork);
		printf("%lld Philosopher %i %s\n", get_timestamp()
			- philo->main->started, philo->index + 1, MSG_FORK);
	}
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	printf("%lld Philosopher %i %s\n", get_timestamp() - philo->main->started,
		philo->index + 1, MSG_EAT);
	pthread_mutex_lock(&philo->m_diestamp);
	philo->diestamp = get_timestamp() + philo->main->time_to_die;
	pthread_mutex_unlock(&philo->m_diestamp);
	pthread_mutex_lock(&philo->m_times_eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->m_times_eaten);
	ft_usleep(philo->main->time_to_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_think(t_philo *philo)
{
	printf("%lld Philosopher %i %s\n", get_timestamp() - philo->main->started,
		philo->index + 1, MSG_THINK);
}

void	philo_sleep(t_philo *philo)
{
	printf("%lld Philosopher %i %s\n", get_timestamp() - philo->main->started,
		philo->index + 1, MSG_SLEEP);
	ft_usleep(philo->main->time_to_sleep);
}
