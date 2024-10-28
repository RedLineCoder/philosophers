/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 07:26:20 by moztop            #+#    #+#             */
/*   Updated: 2024/09/08 14:49:57 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>

# define MSG_DIE "died"
# define MSG_THINK "is thinking"
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"

typedef unsigned long long	t_timestamp;

typedef struct s_main
{
	int						philo_count;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat_count;
	sem_t					*forks;
	sem_t					*satisfied;
	sem_t					*on_death;
	t_timestamp				startstamp;
}							t_main;

typedef struct s_philo
{
	int						index;
	t_main					*main;
	int						times_eaten;
	pthread_t				thread;
	t_timestamp				diestamp;
}							t_philo;

t_timestamp	get_timestamp(void);
void		ft_usleep(t_timestamp ms);
void		*philo_routine(void *arg);

#endif
