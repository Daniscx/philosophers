/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:18:53 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/16 20:09:33 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	action_checker(struct timeval first_one, t_philo *pn, char *messsage)
{
	struct timeval	another_one;
	struct timeval	initial_time;

	initial_time = init_timeval(0);
	gettimeofday(&another_one, NULL);
	if (pn->checker->someone_is_dead == DIED)
		return (another_died(pn));
	if (get_timestamp_in_ms(first_one, another_one) > pn->time.time_to_die)
		return (some_one_is_dead(pn));
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
	printf("%ld %d %s\n", get_timestamp_in_ms(initial_time, timeofdeath),
		pnb->nbph, "died");
	pnb->checker->someone_is_dead = DIED;
	pnb->checker->left_to_check--;
	return (1);
}

int	another_died(t_philo *philo)
{
	philo->checker->left_to_check--;
	return (1);
}

int	eat_left(t_philo *philo, int i)
{
	philo->time.times_to_eat--;
	i = 0;
	if (philo->time.times_to_eat == 0)
	{
		pthread_mutex_lock(philo->status_door);
		i = 1;
		pthread_mutex_unlock(philo->status_door);
	}
	else if (i == 0)
	{
		gettimeofday(&(philo->since_eat), NULL);
		usleep(philo->time.time_to_eat * 1000L);
	
	}
	return(i);
}
