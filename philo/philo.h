/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:11:10 by moztop            #+#    #+#             */
/*   Updated: 2024/08/02 10:23:14 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

typedef enum e_action
{
	DIE,
	THINK,
	FORK,
	EAT,
	SLEEP
}							t_action;

# define MSG_DIE "died"
# define MSG_THINK "is thinking"
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"

// sysctl kern.num_taskthreads for MacOS
# define MAX_PHILO 2048

typedef unsigned long long	t_timestamp;

typedef struct s_philo
{
	int						index;
	int						times_eaten;
	pthread_t				thread;
	t_timestamp				diestamp;
	pthread_mutex_t			m_fork;
	pthread_mutex_t			m_diestamp;
}							t_philo;

typedef struct s_main
{
	t_timestamp				started;
	t_philo					philosophers[2048];
	int						philo_count;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat_count;
}							t_main;

t_timestamp					get_timestamp(void);
void						*philo_routine(void *ptr);

#endif
