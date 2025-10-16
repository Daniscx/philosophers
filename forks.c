/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:42:37 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/16 19:09:47 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "unistd.h"

static int	forks_everyone(int phnb, t_philo *philo);

int	table(int phnb, t_philo *philo)
{
	return (forks_everyone(phnb, philo));
}

static int	forks_everyone(int phnb, t_philo *philo)
{
	if (phnb % 2 == 0)
		return (eating_for_pair( philo));
	else
		return (eating_for_unpair(philo));
}

int	taking_fork(struct timeval since_eat, t_philo *philo)
{
	int	i;

	i = 0;
	i = action_protection(since_eat, philo, "has taken a fork");
	return (i);
}
