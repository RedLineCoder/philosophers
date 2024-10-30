/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:20:49 by moztop            #+#    #+#             */
/*   Updated: 2024/08/06 18:50:13 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_action(t_philo *philo, char *msg)
{
	printf("%llu Philosopher %i %s\n", get_timestamp()
		- (unsigned long long)fetch_data(philo->m_main, \
			philo->startstamp, 8), philo->index, msg);
}

int	check_end(t_philo *philo)
{
	if (philo->diestamp < get_timestamp()
		&& fetch_data(philo->m_main, philo->status, 4) == START)
	{
		print_action(philo, MSG_DIE);
		pthread_mutex_lock(philo->m_main);
		*(philo->status) = END;
		pthread_mutex_lock(philo->m_main);
	}
	if ((int)fetch_data(philo->m_main, philo->satisfied_philos, 4) == philo->philo_count)
	{
		pthread_mutex_lock(philo->m_main);
		*(philo->status) = END;
		pthread_mutex_lock(philo->m_main);
	}
	if ((int)fetch_data(philo->m_main, philo->status, 4) == END)
		return (1);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->index % 2)
	{
		pthread_mutex_lock(philo->l_fork);
		if (check_end(philo))
			return (pthread_mutex_unlock(philo->l_fork), 0);
		print_action(philo, MSG_FORK);
	}
	pthread_mutex_lock(philo->r_fork);
	if (check_end(philo) && philo->index % 2)
		return (pthread_mutex_unlock(philo->r_fork),
			pthread_mutex_unlock(philo->l_fork), 0);
	if (check_end(philo) && !(philo->index % 2))
		return (pthread_mutex_unlock(philo->r_fork), 0);
	print_action(philo, MSG_FORK);
	if (!(philo->index % 2))
	{
		pthread_mutex_lock(philo->l_fork);
		if (check_end(philo))
			return (pthread_mutex_unlock(philo->r_fork),
				pthread_mutex_unlock(philo->l_fork), 0);
		print_action(philo, MSG_FORK);
	}
	return (1);
}

int	philo_actions(t_philo *philo)
{
	if (!take_forks(philo))
		return (END);
	print_action(philo, MSG_EAT);
	philo->diestamp = get_timestamp() + philo->time_to_die;
	philo->times_eaten++;
	if (philo->times_eaten == philo->must_eat_count)
	{
		pthread_mutex_lock(philo->m_main);
		philo->satisfied_philos++;
		pthread_mutex_unlock(philo->m_main);
	}
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (check_end(philo))
		return (END);
	print_action(philo, MSG_SLEEP);
	ft_usleep(philo->time_to_sleep);
	if (check_end(philo))
		return (END);
	print_action(philo, MSG_THINK);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo *const	philo = (t_philo *)arg;

	while (1)
	{
		if ((int)fetch_data(philo->m_main, philo->status, 4))
		{
			pthread_mutex_lock(philo->m_main);
			philo->diestamp = *(philo->startstamp) + philo->time_to_die;
			pthread_mutex_unlock(philo->m_main);
			break ;
		}
	}
	while (1)
	{
		if (philo_actions(philo))
			break ;
	}
	printf("Philo %i ended", philo->index);
	pthread_mutex_destroy(philo->l_fork);
	return (NULL);
}
