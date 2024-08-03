/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:11:10 by moztop            #+#    #+#             */
/*   Updated: 2024/08/04 02:32:15 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

typedef enum e_action
{
	INIT,
	STARTED,
	ENDED
}			t_action;

# define MSG_DIE "died"
# define MSG_THINK "is thinking"
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"

// sysctl kern.num_taskthreads for MacOS
# define MAX_PHILO 2048

typedef unsigned long long	t_timestamp;
typedef struct s_main		t_main;

typedef struct s_philo
{
	int						index;
	int						times_eaten;
	t_main					*main;
	pthread_t				thread;
	t_timestamp				diestamp;
	pthread_mutex_t			l_fork;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			m_diestamp;
	pthread_mutex_t			m_times_eaten;
}							t_philo;

typedef struct s_main
{
	t_timestamp				started;
	pthread_mutex_t			m_ended;
	t_philo					philosophers[MAX_PHILO];
	int						philo_count;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat_count;
	int						ended;
}							t_main;

t_timestamp					get_timestamp(void);
void						ft_usleep(t_timestamp ms);
void						*philo_routine(void *arg);
void						end_checker(t_main *main);
void						philo_eat(t_philo *philo);
void						philo_think(t_philo *philo);
void						philo_sleep(t_philo *philo);
void						join_philos(t_main *main);

#endif
