/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:20:49 by moztop            #+#    #+#             */
/*   Updated: 2024/08/04 10:01:19 by moztop           ###   ########.fr       */
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

int	check_end(t_philo *philo)
{
	if (philo->main->philo_count == 1)
		return (1);
	pthread_mutex_lock(&philo->main->m_status);
	if (philo->main->status == END)
	{
		pthread_mutex_unlock(&philo->main->m_status);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->m_status);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->index % 2)
	{
		pthread_mutex_lock(&philo->l_fork);
		if (check_end(philo))
			return (pthread_mutex_unlock(&philo->l_fork), 0);
		printf("%lld Philosopher %i %s\n", get_timestamp()
			- philo->main->startstamp, philo->index, MSG_FORK);
	}
	pthread_mutex_lock(philo->r_fork);
	if (check_end(philo))
			return (pthread_mutex_unlock(philo->r_fork), 0);
	printf("%lld Philosopher %i %s\n", get_timestamp() - philo->main->startstamp,
		philo->index, MSG_FORK);
	if (!(philo->index % 2))
	{
		pthread_mutex_lock(&philo->l_fork);
		if (check_end(philo))
			return (pthread_mutex_unlock(&philo->l_fork), 0);
		printf("%lld Philosopher %i %s\n", get_timestamp()
			- philo->main->startstamp, philo->index, MSG_FORK);
	}
	return (1);
}

void	philo_eat(t_philo *philo)
{
	if (!take_forks(philo))
		return ;
	printf("%lld Philosopher %i %s\n", get_timestamp() - philo->main->startstamp,
		philo->index, MSG_EAT);
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

void	philo_sleep_think(t_philo *philo)
{
	if (check_end(philo))
		return ;
	printf("%lld Philosopher %i %s\n", get_timestamp() - philo->main->startstamp,
		philo->index, MSG_SLEEP);
	ft_usleep(philo->main->time_to_sleep);
	if (check_end(philo))
		return ;
	printf("%lld Philosopher %i %s\n", get_timestamp() - philo->main->startstamp,
		philo->index, MSG_THINK);
}
