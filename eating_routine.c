/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:32:13 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/16 16:38:42 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
static	int which_is_the_fail(int i, int j);

int	fork_for_max(int *table, int phnb, t_philo *philo)
{
	int	i;
	int j;

	pthread_mutex_lock(philo->right_fork);
	j = taking_fork(table, 0, philo->since_Eat , philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	i = taking_fork(table, phnb - 1, philo->since_Eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	if (i == 0 && j == 0)
	{
		i = action_protection(philo->since_Eat, philo, "is eating");
		eat_left(philo, i);
	}
	if (i == 1)
		return (1);
	pthread_mutex_lock(philo->left_fork);
	release_fork(table, phnb - 1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	release_fork(table, 0);
	pthread_mutex_unlock(philo->right_fork);
	return(which_is_the_fail(i, j));
}

int	eating_for_pair(int *table, int phnb, t_philo *philo)
{
	int	i;
	int j;

	pthread_mutex_lock(philo->right_fork);
	j = taking_fork(table, phnb, philo->since_Eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	i = taking_fork(table, phnb - 1, philo->since_Eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	if (i == 0 && j == 0)
	{
		i = action_protection(philo->since_Eat, philo, "is eating");
		eat_left(philo, i);
	}
	if (i == 1)
		return (1);
	pthread_mutex_lock(philo->left_fork);
	release_fork(table, phnb - 1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	release_fork(table, phnb);
	pthread_mutex_unlock(philo->right_fork);
	return(which_is_the_fail(i, j));
}

int	eating_for_unpair(int *table, int phnb, t_philo *philo)
{
	int	i;
	int j;

	pthread_mutex_lock(philo->left_fork);
	j  = taking_fork(table, phnb - 1, philo->since_Eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	i = taking_fork(table, phnb, philo->since_Eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	if (i == 0 && j == 0)
	{
		i = action_protection(philo->since_Eat, philo, "is eating");
		eat_left(philo, i);
	}
	if (i == 1)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	release_fork(table, phnb);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	release_fork(table, phnb - 1);
	pthread_mutex_unlock(philo->left_fork);
	return(which_is_the_fail(i, j));
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
static	int which_is_the_fail(int i, int j)
{
	if(i == 0)
		return(j);
	else	
		return(i);
}