/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:32:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/15 19:17:15 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fork_for_max(int *table, int phnb, t_philo *philo, struct timeval since_eat)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philo->right_fork);
	i = taking_fork(table, 0, since_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	i = taking_fork(table, phnb - 1, since_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	if (i == 0)
	{
		i = action_protection(since_eat, philo, "is eating");
		eat_left(philo, i);
		usleep(philo->time.time_to_eat * 1000L);
	}
	if (i == 1)
		return (1);
	gettimeofday(&since_eat, NULL);
	pthread_mutex_lock(philo->left_fork);
	release_fork(table, phnb - 1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	release_fork(table, 0);
	pthread_mutex_unlock(philo->right_fork);
	return (i);
}

int	eating_for_pair(int *table, int phnb, t_philo *philo,
		struct timeval since_eat)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philo->right_fork);
	i = taking_fork(table, phnb, since_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	i = taking_fork(table, phnb - 1, since_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	if (i == 0)
	{
		i = action_protection(since_eat, philo, "is eating");
		eat_left(philo, i);
		usleep(philo->time.time_to_eat * 1000L);
	}
	if (i == 1)
		return (1);
	gettimeofday(&since_eat, NULL);
	pthread_mutex_lock(philo->left_fork);
	release_fork(table, phnb - 1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	release_fork(table, phnb);
	pthread_mutex_unlock(philo->right_fork);
	return (i);
}

int	eating_for_unpair(int *table, int phnb, t_philo *philo,
		struct timeval since_eat)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philo->left_fork);
	i = taking_fork(table, phnb - 1, since_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	i = taking_fork(table, phnb, since_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	if (i == 0)
	{
		i = action_protection(since_eat, philo, "is eating");
		usleep(philo->time.time_to_eat * 1000L);
		eat_left(philo, i);
	}
	if (i == 1)
		return (1);
	gettimeofday(&since_eat, NULL);
	pthread_mutex_lock(philo->right_fork);
	release_fork(table, phnb);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	release_fork(table, phnb - 1);
	pthread_mutex_unlock(philo->left_fork);
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
