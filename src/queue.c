/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 16:15:48 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/18 00:01:21 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include "lem_in.h"
#include "ft_printf.h"

t_queue *create_queue(int size)
{
	t_queue *q;

	if (!(q = malloc(sizeof(t_queue))))
		return (NULL);
	if (!(q->items = malloc(sizeof(t_room *) * size)))
		return (NULL);
	q->size = size;
	q->front = -1;
	q->rear = -1;
	return (q);
}

int isempty(t_queue *q)
{
	if (q->rear == -1)
		return (1);
	return (0);
}

void enqueue(t_queue *q, t_room *item)
{
	if (q->rear == q->size - 1)
	{
		// ft_printf("queue is full\n");
		return;
	}
	else
	{
		if (q->front == -1)
			q->front = 0;
		q->rear++;
		q->items[q->rear] = item;
	}
}

t_room *dequeue(t_queue *q)
{
	t_room *item;

	if (isempty(q))
		item = NULL;
	else
	{
		item = q->items[q->front];
		q->front++;
		if (q->front > q->rear)
		{
			// ft_printf("resetting queue\n");
			q->front = -1;
			q->rear = -1;
		}
	}
	return (item);
}

void print_queue(t_queue *q)
{
	int i;

	i = q->front;
	if (isempty(q))
		ft_printf("queue is empty\n");
	else
	{
		ft_printf("queue:\n");
		while (i <= q->rear)
		{
			ft_printf("%s ", q->items[i]->name);
			i++;
		}
		ft_printf("\n");
	}
}
