/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:32:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/16 20:22:16 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int	eating_for_pair(t_philo *philo)
{
	int	i;


	pthread_mutex_lock(philo->right_fork);
	taking_fork(philo->since_eat, philo);
	pthread_mutex_lock(philo->left_fork);
	taking_fork(philo->since_eat, philo);
	i = action_protection(philo->since_eat, philo, "is eating");
	 i = eat_left(philo, i);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (i);
}

int	eating_for_unpair(t_philo *philo)
{
	int	i;
	pthread_mutex_lock(philo->left_fork);
	taking_fork(philo->since_eat, philo);
	pthread_mutex_lock(philo->right_fork);
	taking_fork(philo->since_eat, philo);
	i = action_protection(philo->since_eat, philo, "is eating");
	i = eat_left(philo, i);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (i);
}

void	only_one_philo_routine(t_philo *philo, struct timeval since_eat)
{
	pthread_mutex_lock(philo->status_door);
	if (philo->checker->left_to_check == 1)
	{
		pthread_mutex_unlock(philo->status_door);
		gettimeofday(&since_eat, NULL);
		action_checker(since_eat, philo, "has taken a fork");
		usleep(philo->time.time_to_die * 1000);
		some_one_is_dead(philo);
		destroy_philo(philo);
	}
	pthread_mutex_unlock(philo->status_door);
}
