/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 07:26:24 by moztop            #+#    #+#             */
/*   Updated: 2024/09/08 15:12:08 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

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

unsigned int	ft_atoui32(char *str)
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

void	destroy_sem_all(t_main *main)
{
	if (main->forks)
	{
		if (sem_close(&main->forks) == -1)
			exit(EXIT_FAILURE);
		if (sem_unlink("/forks") == -1)
			exit(EXIT_FAILURE);
	}
	if (main->satisfied)
	{
		if (sem_close(&main->satisfied) == -1)
			exit(EXIT_FAILURE);
		if (sem_unlink("/satisfied") == -1)
			exit(EXIT_FAILURE);
	}
	if (main->on_death)
	{
		if (sem_close(&main->on_death) == -1)
			exit(EXIT_FAILURE);
		if (sem_unlink("/on_death") == -1)
			exit(EXIT_FAILURE);
	}
}

void	init_main(int argc, char **argv, t_main *main)
{
	main->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, main->philo_count);
	if (main->forks == SEM_FAILED)
		return (destroy_sem_all(main));
	main->satisfied = sem_open("/satisfied", O_CREAT | O_EXCL, 0644, main->philo_count);
	if (main->satisfied == SEM_FAILED)
		return (destroy_sem_all(main));
	main->on_death = sem_open("/on_death", O_CREAT | O_EXCL, 0644, 1);
	if (main->on_death == SEM_FAILED)
		return (destroy_sem_all(main));
	if (!check_args(argc, argv))
		return (destroy_sem_all(main), exit(EXIT_FAILURE));
	main->philo_count = ft_atoui32(argv[1]);
	main->time_to_die = ft_atoui32(argv[2]);
	main->time_to_eat = ft_atoui32(argv[3]);
	main->time_to_sleep = ft_atoui32(argv[4]);
	main->must_eat_count = -1;
	if (argc == 6)
		main->must_eat_count = ft_atoui32(argv[5]);
	main->startstamp = get_timestamp();
}

int	main(int argc, char **argv)
{
	t_main *const	main = &(t_main){0};
	t_philo			*philo;
	int				index;

	init_main(argc, argv, main);
	index = 1;
	while (index <= main->philo_count)
	{
		if (fork() == 0)
		{
			philo = &(t_philo){index, main};
			if (!pthread_create(&(philo->thread), NULL, philo_routine, (void *)&(philo)) != 0)
				exit (1); //handle error
		}
		index++;
	}
	destroy_sem_all(main);
	return (0);
}
