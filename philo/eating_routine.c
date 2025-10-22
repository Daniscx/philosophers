/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:32:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/21 19:49:23 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int	eating_for_pair(t_philo *philo)
{
	int	i;

	
	pthread_mutex_lock(philo->right_fork);
	taking_fork(philo);
	pthread_mutex_lock(philo->left_fork);
	taking_fork(philo);
	i = action_protection(philo, "is eating");
	 i = eat_left(philo, i);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (i);
}

int	eating_for_unpair(t_philo *philo)
{
	int	i;
	
	pthread_mutex_lock(philo->left_fork);
	taking_fork(philo);
	pthread_mutex_lock(philo->right_fork);
	taking_fork(philo);
	i = action_protection(philo, "is eating");
	i = eat_left(philo, i);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (i);
}

void	only_one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->status_door);
	if (philo->checker->left_to_check == 1)
	{
		pthread_mutex_unlock(philo->status_door);
		action_protection(philo, "has taken a fork");
		usleep(philo->time.time_to_die * 1000);
		pthread_exit(0);
	}
	pthread_mutex_unlock(philo->status_door);
}

