/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:18:24 by moztop            #+#    #+#             */
/*   Updated: 2024/08/06 18:19:11 by moztop           ###   ########.fr       */
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
		if ((int)fetch_data(&philo->main->m_status, &philo->main->status,
				4) != INIT)
			break ;
	}
	while (1)
	{
		if ((int)fetch_data(&philo->main->m_status, &philo->main->status,
				4) != START)
			break ;
		philo_actions(philo);
	}
	return (NULL);
}
