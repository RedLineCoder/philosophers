/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:18:24 by moztop            #+#    #+#             */
/*   Updated: 2024/08/08 16:36:50 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_philos(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->philo_count)
		pthread_join(main->philosophers[i].thread, NULL);
}

int	init_philo(t_main	*main, int i)
{
	main->philosophers[i].index = i + 1;
	main->philosophers[i].main = main;
	main->philosophers[i].l_fork = &main->forks[i];
	main->philosophers[i].r_fork = &main->forks[(i + 1)
		% main->philo_count];
	main->philosophers[i].diestamp = get_timestamp() + main->time_to_die;
	if (pthread_mutex_init(&main->philosophers[i].m_diestamp, NULL) != 0
		|| pthread_mutex_init(&main->philosophers[i].m_times_eaten,
			NULL) != 0 || pthread_create(&(main->philosophers[i].thread),
			NULL, philo_routine, (void *)&(main->philosophers[i])) != 0)
		return (destroy_philos(main, i), 0);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo *const	philo = (t_philo *)arg;

	while (1)
	{
		if ((int)fetch_data(&philo->main->m_status, &philo->main->status,
				4) != INIT)
			break ;
	}
	while (1)
	{
		if ((int)fetch_data(&philo->main->m_status, &philo->main->status,
				4) != START)
			break ;
		philo_eat(philo);
		philo_sleep_think(philo);
	}
	return (NULL);
}
