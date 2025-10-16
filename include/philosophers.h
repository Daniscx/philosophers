/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:56:36 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/16 19:16:02 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include "list.h"
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "sys/time.h"

typedef struct s_ttime
{
	int				time_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				times_to_eat;
}					t_ttime;

typedef enum e_someone_is_dead
{
	LIVE,
	DIED,
}					t_enum;
typedef struct s_checker
{
	int				left_to_check;
	t_enum			someone_is_dead;
}					t_checker;

typedef struct philo_s
{
	int				nbph;
	t_ttime			time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*status_door;
	t_checker		*checker;
	struct timeval	since_eat;

}					t_philo;

int					ft_atoi(char *nb);
void				error_manager(char *error);
t_philo				*init_philos(t_ttime asignation, int nbph);
void				*philos(void *pn);
int					action_checker(struct timeval first_one, t_philo *pn,
						char *messsage);
int					table(int phnb, t_philo *philo);
long				get_timestamp_in_ms(struct timeval start,
						struct timeval current);
int					action_protection(struct timeval first_one, t_philo *pn,
						char *message);
int					another_died(t_philo *philo);
int					some_one_is_dead(t_philo *pnb);
int				eat_left(t_philo *philo, int i);
t_checker			*init_checker(int pnb);
struct timeval		init_timeval(int i);
void				forks_creator(t_philo *philo);
t_checker			*init_checker(int pnb);
int					eating_for_unpair(t_philo *philo);
int					eating_for_pair(t_philo *philo);
int					fork_for_max(t_philo *philo);
void				only_one_philo_routine(t_philo *philo,
						struct timeval since_eat);
int					taking_fork( struct timeval since_eat, t_philo *philo);
void				release_fork(int *table, int phnb);
void				destroy_philo(t_philo *philo);

#endif