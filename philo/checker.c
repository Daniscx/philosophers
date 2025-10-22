/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:18:53 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/21 19:56:46 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	action_checker_for_actions(t_philo *pn, char *messsage)
{
	struct timeval	another_one;
	struct timeval	initial_time;

	initial_time = init_timeval(0);
	gettimeofday(&another_one, NULL);
	if (pn->checker->someone_is_dead == DIED)
		return (1);
	if (messsage)
		printf("%li %d %s\n", get_timestamp_in_ms(initial_time, another_one),
			pn->nbph, messsage);
	return (0);
}

int	some_one_is_dead(t_philo *pnb)
{
	struct timeval	timeofdeath;
	struct timeval	initial_time;

	initial_time = init_timeval(0);
	gettimeofday(&timeofdeath, NULL);
	if(pnb->checker->left_to_check == 0)
		return(1);
	printf("%ld %d %s\n", get_timestamp_in_ms(initial_time, timeofdeath),
		pnb->nbph, "died");
	pnb->checker->someone_is_dead = DIED;
	pnb->checker->left_to_check--;
	return (1);
}

int	eat_left(t_philo *philo, int i)
{
	philo->time.times_to_eat--;
	i = 0;
	
	if (i == 0)
	{
		gettimeofday(&(philo->since_eat), NULL);
		usleep_better(philo, philo->time.time_to_eat * 1000L);
	}
	if (philo->time.times_to_eat == 0)
	{
		pthread_mutex_lock(philo->status_door);
		i = 1;
		philo->checker->left_to_check--;
		pthread_mutex_unlock(philo->status_door);
	}
	return(i);
}
int	action_checker_for_dead(struct timeval first_one, t_philo *pn)
{
	struct timeval	another_one;

	gettimeofday(&another_one, NULL);
	if(!pn)
		return(1);
	if (get_timestamp_in_ms(first_one, another_one) >= pn->time.time_to_die)
		return (some_one_is_dead(pn));
	return (0);
}
int	action_protection_for_all(struct timeval first_one, t_philo *pn)
{
	int	i;

	i = 0;
	pthread_mutex_lock(pn->status_door);
	i = action_checker_for_dead(first_one, pn);
	pthread_mutex_unlock(pn->status_door);
	if (i == 1)
		return (1);
	return (0);
}
