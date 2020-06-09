/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 15:40:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/09 15:46:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h> //
#include "ft_printf.h"
#include "ft_queue.h"
#include "ft_hashtable.h"
#include "debug.h"

// create a queue Q
// mark v as visited and put v into Q
// while Q is non-empty
//     remove the head u of Q
//     mark and enqueue all (unvisited) neighbours of u

t_path *path_create()
{
	t_path *p;

	p = (t_path*)malloc(sizeof(t_path));
	p->rooms = NULL; //malloc(sizeof(t_list*));
	p->size = 0;
	return (p);
}

void	path_add_room(t_path *p, t_room *room)
{
	t_list *l;

	l = (t_list*)malloc(sizeof(t_list));
	l->content = room;
	l->content_size = sizeof(t_room*);
	ft_lstadd(&(p->rooms), l);
	p->size++;
}

t_room *path_get_room(t_path *p, int i)
{
	t_list *cur;
	int c;

	c = 0;
	cur = p->rooms;
	while (cur)
	{
		if (c == i)
			return ((t_room*)cur->content);
		c++;
		cur = cur->next;
	}
	return (NULL);
}

void	sort_paths(t_list *paths)
{
	t_list	*cur;
	void	*tmp;
	int		cur_size;
	int		next_size;

	cur = paths;
	while (cur)
	{
		if (cur->next)
		{
			cur_size = ((t_path*)cur->content)->size;
			next_size = ((t_path*)cur->next->content)->size;
			if (next_size < cur_size)
			{
				tmp = cur->next->content;
				cur->next->content = cur->content;
				cur->content = tmp;
				cur = paths;
			}
		}
		cur = cur->next;
	}
}

void	print_path(t_path *p)
{
	t_list *cur;
	t_room *cur_room;

	ft_printf("path: ");
	cur = p->rooms;
	while (cur)
	{
		cur_room = (t_room*)cur->content;
		ft_printf("[%s:%d]", cur_room->name, cur_room->id);
		cur = cur->next;
	}
	ft_printf(" length: %d\n", p->size);
}
