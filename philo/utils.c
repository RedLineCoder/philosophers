/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:20:32 by moztop            #+#    #+#             */
/*   Updated: 2024/08/03 18:41:15 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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

void	dead_checker(t_main *main)
{
	int	i;

	i = 0;
	while (!(main->philosophers[i].died))
	{
		i = (i + 1) % main->philo_count;
	}
}

void	philo_actions(t_philo *philo)
{
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	return (NULL);
}
