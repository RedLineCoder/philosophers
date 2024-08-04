/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:20:32 by moztop            #+#    #+#             */
/*   Updated: 2024/08/04 10:07:25 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

t_timestamp	get_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(t_timestamp ms)
{
	t_timestamp	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < ms)
		usleep(200);
}

int	eat_checker(t_main *main, int i)
{
	pthread_mutex_lock(&main->philosophers[i].m_times_eaten);
	if (main->philosophers[i].times_eaten == main->must_eat_count)
	{
		pthread_mutex_unlock(&main->philosophers[i].m_times_eaten);
		pthread_mutex_lock(&main->m_satisfied_philos);
		main->satisfied_philos++;
		if (main->satisfied_philos == main->philo_count)
		{
			pthread_mutex_lock(&main->m_status);
			main->status = END;
			pthread_mutex_unlock(&main->m_status);
			return (1);
		}
		pthread_mutex_unlock(&main->m_satisfied_philos);
	}
	else
		pthread_mutex_unlock(&main->philosophers[i].m_times_eaten);
	return (0);
}

void	end_checker(t_main *main)
{
	int	i;

	i = 0;
	while (1 && main->philo_count > 0)
	{
		pthread_mutex_lock(&main->philosophers[i].m_diestamp);
		if (main->philosophers[i].diestamp < get_timestamp())
		{
			printf("%lld Philosopher %i %s\n", get_timestamp() - main->startstamp,
				main->philosophers[i].index, MSG_DIE);
			pthread_mutex_lock(&main->m_status);
			main->status = END;
			pthread_mutex_unlock(&main->m_status);
			pthread_mutex_unlock(&main->philosophers[i].m_diestamp);
			return ;
		}
		pthread_mutex_unlock(&main->philosophers[i].m_diestamp);
		if (eat_checker(main, i))
			return ;
		i = (i + 1) % main->philo_count;
	}
}

void	philo_actions(t_philo *philo)
{
	if (check_end(philo))
		return ;
	philo_eat(philo);
	if (check_end(philo))
		return ;
	philo_sleep_think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo *const	philo = (t_philo *)arg;

	while (1)
	{
		pthread_mutex_lock(&philo->main->m_status);
		if (philo->main->status != INIT)
		{
			pthread_mutex_unlock(&philo->main->m_status);
			break ;
		}
		pthread_mutex_unlock(&philo->main->m_status);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->main->m_status);
		if (philo->main->status != START)
		{
			pthread_mutex_unlock(&philo->main->m_status);
			break ;
		}
		pthread_mutex_unlock(&philo->main->m_status);
		philo_actions(philo);
	}
	return (NULL);
}
