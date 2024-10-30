/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:20:32 by moztop            #+#    #+#             */
/*   Updated: 2024/09/02 15:54:24 by moztop           ###   ########.fr       */
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
		else if (size == 8)
			fetcher = *(long long *)data;
		return (pthread_mutex_unlock(mutex), fetcher);
	}
	return (0);
}

unsigned int	ft_atoui(char *str)
{
	unsigned int	result;

	result = 0;
	while (*str == ' ' || (*str <= '\r' && *str >= '\t'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (result);
}

int	init_philo(t_philo *philo, int argc, char **argv, int i)
{
	philo->index = i + 1;
	philo->time_to_die = ft_atoui(argv[2]);
	philo->time_to_eat = ft_atoui(argv[3]);
	philo->time_to_sleep = ft_atoui(argv[4]);
	philo->must_eat_count = -1;
	if (argc == 6)
		philo->must_eat_count = ft_atoui(argv[5]);
	if (pthread_create(&(philo->thread), NULL, philo_routine, (void *)philo) != 0)
		return (0);
	return (1);
}
