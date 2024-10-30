/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:11:06 by moztop            #+#    #+#             */
/*   Updated: 2024/09/08 07:32:30 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	check_args(int argc, char **argv)
{
	int	index;
	int	loop;

	if (argc != 5 && argc != 6)
		return (write(2, "Argument count error!\n", 22), 0);
	index = 0;
	while (argv[++index])
	{
		loop = -1;
		while (argv[index][++loop])
		{
			if (argv[index][loop] > '9' || argv[index][loop] < '0')
				return (write(2, "Argument type <int(+)::miliseconds>\n", 36),
					0);
		}
	}
	return (1);
}

int	init_philos(t_main *main, t_philo *philos, int argc, char **argv)
{
	pthread_mutex_t *const	forks = malloc(sizeof(pthread_mutex_t) * main->philo_count);
	int						i;

	if (!forks)
		return (0);
	if (!main->philo_count)
		return (0);
	i = -1;
	while (++i < main->philo_count)
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (0);
	i = -1;
	while (++i < main->philo_count)
	{
		philos[i].philo_count = main->philo_count;
		philos[i].satisfied_philos = &(main->satisfied_philos);
		philos[i].status = &(main->status);
		philos[i].startstamp = &(main->startstamp);
		philos[i].m_main = &(main->m_main);
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % main->philo_count];
		if (!init_philo(&philos[i], argc, argv, i))
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_main *const	main = &(t_main){0};
	t_philo *const	philos = malloc(sizeof(t_philo) * ft_atoui(argv[1]));
	int				i;

	if (!philos)
		return (write(2, "Philosopher initialization error!\n", 34), 1);
	if (!check_args(argc, argv))
		return (free(philos), 1);
	main->philo_count = ft_atoui(argv[1]);
	memset(philos, 0, sizeof(t_philo) * main->philo_count);
	if (pthread_mutex_init(&main->m_main, NULL))
		return (free(philos), 1);
	if (!init_philos(main, philos, argc, argv))
		return (free(philos), 1);
	pthread_mutex_lock(&(main->m_main));
	main->startstamp = get_timestamp();
	main->status = START;
	pthread_mutex_unlock(&(main->m_main));
	i = -1;
	while (++i < main->philo_count)
		pthread_join(philos[i].thread, NULL);
	return (0);
}
