/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:20:49 by moztop            #+#    #+#             */
/*   Updated: 2024/08/06 18:15:24 by moztop           ###   ########.fr       */
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

void	print_action(t_philo *philo, char *msg)
{
	printf("%llu Philosopher %i %s\n", get_timestamp()
		- philo->main->startstamp, philo->index, msg);
}

int	check_end(t_philo *philo)
{
	if ((int)fetch_data(&philo->main->m_status, &philo->main->status, 4) == END)
		return (1);
	if (philo->main->philo_count == 1)
	{
		printf("%llu Philosopher %i %s\n", get_timestamp()
			- philo->main->startstamp, philo->index, MSG_FORK);
		pthread_mutex_lock(&philo->main->m_status);
		philo->main->status = END;
		pthread_mutex_unlock(&philo->main->m_status);
		return (1);
	}
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

void	philo_eat(t_philo *philo)
{
	if (!take_forks(philo))
		return ;
	print_action(philo, MSG_EAT);
	pthread_mutex_lock(&philo->m_diestamp);
	philo->diestamp = get_timestamp() + philo->main->time_to_die;
	pthread_mutex_unlock(&philo->m_diestamp);
	pthread_mutex_lock(&philo->m_times_eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->m_times_eaten);
	ft_usleep(philo->main->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep_think(t_philo *philo)
{
	if (check_end(philo))
		return ;
	print_action(philo, MSG_SLEEP);
	ft_usleep(philo->main->time_to_sleep);
	if (check_end(philo))
		return ;
	print_action(philo, MSG_THINK);
}
