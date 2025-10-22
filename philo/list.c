/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:57:25 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/21 19:53:22 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "stdlib.h"

static void	phtread_destroyer(t_node *head);

t_list	*init_list(int size)
{
	t_list	*aux;

	aux = malloc(sizeof(t_list));
	aux->head = NULL;
	aux->size = 0;
	aux->array_of_mutex = malloc(size * (sizeof(pthread_mutex_t *)));
	return (aux);
}

void	list_destroyer(t_list *list)
{
	size_t	i;

	i = 0;
	phtread_destroyer(list->head);
	while (i < list->size)
	{
		pthread_mutex_destroy(list->array_of_mutex[i]);
		free(list->array_of_mutex[i]);
		i++;
	}
	free(list->array_of_mutex);
	free(list);
}

void	add_element_to_list(t_list *list, t_node *new_element,
		pthread_mutex_t *new_mutex)
{
	t_node	*aux;

	if (!list->head)
	{
		list->size++;
		list->array_of_mutex[0] = new_mutex;
		list->head = new_element;
		return ;
	}
	aux = list->head;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new_element;
	list->array_of_mutex[list->size] = new_mutex;
	list->size++;
}

t_node	*create_new_node(pthread_t *pthread, t_philo *philo)
{
	t_node	*result;

	result = NULL;
	result = malloc(sizeof(t_node));
	result->next = NULL;
	result->thread = pthread;
	result->philo = philo;
	return (result);
}

static void	phtread_destroyer(t_node *head)
{
	t_node	*aux;
	t_node	*next_aux;

	aux = head;
	while (aux != NULL)
	{
		next_aux = aux->next;
		pthread_join(*aux->thread, NULL);
		free(aux->thread);
		free(aux->philo);
		free(aux);
		aux = next_aux;
	}
}
