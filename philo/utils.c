/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:20:32 by moztop            #+#    #+#             */
/*   Updated: 2024/08/03 21:06:07 by moztop           ###   ########.fr       */
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
		usleep(1);
}

void	end_checker(t_main *main)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&main->philosophers[i].m_diestamp);
		pthread_mutex_lock(&main->philosophers[i].m_times_eaten);
		if (main->philosophers[i].diestamp >= get_timestamp())
		{
			printf("%lld Philosopher %i %s\n", get_timestamp() - main->started,
				main->philosophers[i].index + 1, MSG_DIE);
			pthread_mutex_unlock(&main->philosophers[i].m_diestamp);
			pthread_mutex_lock(&main->philosophers[i].m_times_eaten);
			break ;
		}
		if (main->philosophers[i].times_eaten >= main->must_eat_count)
		{
			pthread_mutex_unlock(&main->philosophers[i].m_diestamp);
			pthread_mutex_lock(&main->philosophers[i].m_times_eaten);
			break ;
		}
		pthread_mutex_unlock(&main->philosophers[i].m_diestamp);
		pthread_mutex_lock(&main->philosophers[i].m_times_eaten);
		i = (i + 1) % main->philo_count;
	}
}

void	*philo_routine(void *arg)
{
	t_philo *const	philo = (t_philo *)arg;

	while (!(philo->main->ended))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
