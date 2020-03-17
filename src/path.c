/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 15:40:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/17 19:56:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h> //
#include "ft_printf.h"
#include "queue.h"
#include "hash_table.h"

// create a queue Q
// mark v as visited and put v into Q
// while Q is non-empty
//     remove the head u of Q
//     mark and enqueue all (unvisited) neighbours of u

t_path *create_path(int length)
{
	t_path *p;
	int i;

	p = malloc(sizeof(t_path));
	p->length = length;
	p->rooms = malloc(sizeof(t_room*) * length);
	i = 0;
	while (i < p->length)
	{
		p->rooms[i] = NULL;
		i++;
	}
	return (p);
}

t_path *find_path(t_lem_env *lem_env)
{
	t_queue *q;
	t_ht *visited;
	int	step;

	visited = ht_create(lem_env->num_rooms);
	q = create_queue(lem_env->num_rooms);
	ht_set(visited, lem_env->end->name, "1");
	enqueue(q, lem_env->end);
	step = 0;
	lem_env->end->hcost = step++;
	while (!isempty(q))
	{
		t_room *r = dequeue(q);
		t_list *n = *r->links;
		while (n)
		{
			t_room *c = ((t_link*)n->content)->r2;
			if (!ht_get(visited, c->name))
			{
				ht_set(visited, c->name, "1");
				enqueue(q, c);
				c->hcost = step;
				ft_printf("visited: %s cost: %d\n", c->name, c->hcost);
			}
			n = n->next;
		}
		step++;
	}
	t_path *p;

	t_room *cur_room;
	cur_room = lem_env->start;
	p = create_path(cur_room->hcost);
	ft_printf("pathlen: %d\n", p->length);
	step = 0;
	int score = INT32_MAX;
	while (cur_room != lem_env->end)
	{
		t_list *cur_link = *cur_room->links;
		while (cur_link)
		{
			t_room *r = ((t_link*)cur_link->content)->r2;
			if (r->hcost < score)
			{
				cur_room = r;
				score = r->hcost;
			}
			cur_link = cur_link->next;
		}
		p->rooms[step] = cur_room;
		step++;
	}
	return (p);
}
