/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 16:15:48 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/20 14:46:04 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bfs_queue.h"
#include "lem_in.h"
#include "ft_printf.h"

t_bfs_queue *bfs_queue_create(int size)
{
	t_bfs_queue *q;

	if (!(q = malloc(sizeof(t_bfs_queue))))
		return (NULL);
	if (!(q->items = malloc(sizeof(int) * size)))
		return (NULL);
	q->size = size;
	q->front = -1;
	q->rear = -1;
	return (q);
}

void		bfs_queue_destroy(t_bfs_queue *q)
{
	free(q->items);
	free(q);
}

int bfs_queue_isempty(t_bfs_queue *q)
{
	if (q->rear == -1)
		return (1);
	return (0);
}

void bfs_queue_enqueue(t_bfs_queue *q, int item)
{
	if (q->rear == q->size - 1)
		return;
	else
	{
		if (q->front == -1)
			q->front = 0;
		q->rear++;
		q->items[q->rear] = item;
	}
}

int bfs_queue_dequeue(t_bfs_queue *q)
{
	int item;

	if (bfs_queue_isempty(q))
		item = -1;
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

void bfs_queue_print(t_bfs_queue *q)
{
	int i;

	i = q->front;
	if (bfs_queue_isempty(q))
		ft_printf("queue is empty\n");
	else
	{
		ft_printf("bfs queue:\n");
		while (i <= q->rear)
		{
			ft_printf("%d ", q->items[i]);
			i++;
		}
		ft_printf("\n");
	}
}
