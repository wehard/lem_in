/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 16:16:58 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/17 16:21:24 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "lem_in.h"

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
#endif
