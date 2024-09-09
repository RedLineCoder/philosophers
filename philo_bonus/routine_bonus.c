/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:52:44 by moztop            #+#    #+#             */
/*   Updated: 2024/09/08 14:49:24 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_philo *philo, char *msg)
{
	printf("%llu Philosopher %i %s\n", get_timestamp()
		- philo->main->startstamp, philo->index, msg);
}

void	philo_eat(t_philo *philo)
{
	if (philo->index % 2)
	{
		sem_wait(philo->main->sem);
		print_action(philo, MSG_FORK);
	}
	sem_wait(philo->main->sem);
	print_action(philo, MSG_FORK);
	if (!(philo->index % 2))
	{
		sem_wait(philo->main->sem);
		print_action(philo, MSG_FORK);
	}
	print_action(philo, MSG_EAT);
	philo->diestamp = get_timestamp() + philo->main->time_to_die;
	philo->times_eaten++;
	ft_usleep(philo->main->time_to_eat);
	sem_post(philo->main->sem);
	sem_post(philo->main->sem);
}

void	philo_sleep_think(t_philo *philo)
{
	print_action(philo, MSG_SLEEP);
	ft_usleep(philo->main->time_to_sleep);
	print_action(philo, MSG_THINK);
}

void	*philo_routine(void *arg)
{
	t_philo *const	philo = (t_philo *)arg;

	philo->diestamp = get_timestamp() + philo->main->time_to_die;
	while (1)
	{
		if (philo->times_eaten >= philo->main->must_eat_count)
			exit (0);
		if (philo->diestamp < get_timestamp())
			exit (1);
		philo_eat(philo);
		philo_sleep_think(philo);
	}
}
