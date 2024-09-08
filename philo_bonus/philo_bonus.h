/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 07:26:20 by moztop            #+#    #+#             */
/*   Updated: 2024/09/08 07:38:03 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <sys/time.h>

# define MSG_DIE "died"
# define MSG_THINK "is thinking"
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"

typedef unsigned long long	t_timestamp;
typedef struct s_main		t_main;

typedef struct s_philo
{
	int						index;
	int						times_eaten;
	int						satisfied;
	t_main					*main;
	pthread_t				thread;
	t_timestamp				diestamp;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			m_diestamp;
	pthread_mutex_t			m_times_eaten;
}							t_philo;

typedef struct s_main
{
	int						status;
	int						satisfied_philos;
	int						philo_count;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat_count;
	t_timestamp				startstamp;
	pthread_mutex_t			m_status;
	t_philo					*philosophers;
	pthread_mutex_t			*forks;
}							t_main;

t_timestamp	get_timestamp(void);

#endif