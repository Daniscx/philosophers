/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:18:53 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/16 05:30:27 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		action_checker(struct timeval first_one, t_philo *pn, char *messsage)
{
	struct timeval	another_one;

	gettimeofday(&another_one, NULL);
	if (pn->checker->someone_is_dead == DIED)
		return (another_died(pn));
	if (get_timestamp_in_ms(first_one, another_one) > pn->time.time_to_die)
		return (some_one_is_dead(pn));
	if (messsage)
		printf("%li %d %s\n", (another_one.tv_sec * 1000L)
			+ (another_one.tv_usec / 1000L), pn->nbph, messsage);
	return (0);
}

int	some_one_is_dead(t_philo *pnb)
{
	struct timeval	timeofdeath;

	gettimeofday(&timeofdeath, NULL);
	printf("%ld %d %s\n", (timeofdeath.tv_sec * 1000L) + (timeofdeath.tv_usec
			/ 1000L), pnb->nbph, "died");
	pnb->checker->someone_is_dead = DIED;
	pnb->checker->left_to_check--;
	return (1);
}

int	another_died(t_philo *philo)
{
	philo->checker->left_to_check--;
	return (1);
}

void	eat_left(t_philo *philo, int i)
{
	philo->time.times_to_eat--;
	if (philo->time.times_to_eat == 0)
	{
		pthread_mutex_lock(philo->status_door);
		philo->checker->someone_is_dead = DIED;
		pthread_mutex_unlock(philo->status_door);
	}
	else if (i == 0)
	{
		gettimeofday(&(philo->since_Eat), NULL);
		usleep(philo->time.time_to_eat * 1000L);
	}
	 
}
