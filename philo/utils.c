/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:20:32 by moztop            #+#    #+#             */
/*   Updated: 2024/08/06 18:19:43 by moztop           ###   ########.fr       */
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

long long	fetch_data(pthread_mutex_t *mutex, void *data, int size)
{
	long long	fetcher;

	if (!pthread_mutex_lock(mutex))
	{
		if (size == 4)
			fetcher = *(int *)data;
		if (size == 8)
			fetcher = *(long long *)data;
		return (pthread_mutex_unlock(mutex), fetcher);
	}
	return (0);
}

int	eat_checker(t_main *main, int i)
{
	if ((int)fetch_data(&main->philosophers[i].m_times_eaten,
			&main->philosophers[i].times_eaten, 4) == main->must_eat_count)
	{
		if (!main->philosophers[i].satisfied)
			main->satisfied_philos++;
		main->philosophers[i].satisfied = 1;
		if (main->satisfied_philos == main->philo_count)
		{
			pthread_mutex_lock(&main->m_status);
			main->status = END;
			pthread_mutex_unlock(&main->m_status);
			return (1);
		}
	}
	return (0);
}

void	end_checker(t_main *main)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((t_timestamp)fetch_data(&main->philosophers[i].m_diestamp,
				&main->philosophers[i].diestamp, 8) < get_timestamp())
		{
			printf("%lld Philosopher %i %s\n", get_timestamp()
				- main->startstamp, main->philosophers[i].index, MSG_DIE);
			pthread_mutex_lock(&main->m_status);
			main->status = END;
			pthread_mutex_unlock(&main->m_status);
			return ;
		}
		if (eat_checker(main, i))
			return ;
		i = (i + 1) % main->philo_count;
	}
}
