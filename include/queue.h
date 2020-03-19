/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 16:16:58 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/19 18:02:13 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "lem_in.h"

typedef struct	s_bfs_queue
{
	int			size;
	int			*items;
	int			front;
	int			rear;
}				t_bfs_queue;

typedef struct	s_queue
{
	int			size;
	t_room		**items;
	int			front;
	int			rear;
}				t_queue;

t_queue			*create_queue(int size);
int				isempty(t_queue *q);
void			enqueue(t_queue *q, t_room *item);
t_room			*dequeue(t_queue *q);
void			print_queue(t_queue *q);

t_bfs_queue		*bfs_queue_create(int size);
void			bfs_queue_destroy(t_bfs_queue *q);
int				bfs_queue_isempty(t_bfs_queue *q);
void			bfs_queue_enqueue(t_bfs_queue *q, int item);
int				bfs_queue_dequeue(t_bfs_queue *q);
void			bfs_queue_print(t_bfs_queue *q);

#endif
