/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:25:25 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/21 19:13:13 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

struct timeval	init_timeval(int bool)
{
	static struct timeval	result;

	if (bool == 1)
		gettimeofday(&result, NULL);
	return (result);
}

pthread_mutex_t	*init_mutext(void)
{
	pthread_mutex_t	*result;

	result = NULL;
	result = malloc(1 * sizeof(pthread_mutex_t));
	pthread_mutex_init(result, NULL);
	return (result);
}

void	forks_creator(t_philo *philo)
{
	static pthread_mutex_t	*last_fork = NULL;

	if (philo->left_fork == NULL)
		philo->left_fork = init_mutext();
	if (philo->right_fork == NULL)
		philo->right_fork = last_fork;
	last_fork = philo->left_fork;
}

t_checker	*init_checker(int pnb)
{
	t_checker	*result;

	result = NULL;
	result = malloc(sizeof(t_checker));
	result->left_to_check = pnb;
	result->someone_is_dead = LIVE;
	return (result);
}
void dead_checker(t_list *list)
{
	t_node *aux;
	int i;
	i = 0;
	usleep(5200);
	while(1)
	{
		aux = list->head;
		while(aux != NULL)
		{
			i = action_protection_for_all(aux->philo->since_eat, aux->philo);
			aux = aux->next;
			if(i == 1)
				break;
		}
		if(i == 1)
			break;
	}
}
