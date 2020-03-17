/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 15:40:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/18 01:03:16 by wkorande         ###   ########.fr       */
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

t_path *create_path(int size)
{
	t_path *p;
	int i;

	p = malloc(sizeof(t_path));
	p->size = size;
	p->rooms = malloc(sizeof(t_room*) * size);
	i = 0;
	while (i < p->size)
	{
		p->rooms[i] = NULL;
		i++;
	}
	return (p);
}

void	bfs_calc_cost(t_lem_env *lem_env, t_room *from)
{
	t_ht	*visited;
	t_queue	*q;
	int		level;

	visited = ht_create(lem_env->num_rooms);
	q = create_queue(lem_env->num_rooms);
	ht_set(visited, from->name, "1");
	enqueue(q, from);
	level = 0;
	from->hcost = level++;
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
				c->hcost = level;
				// ft_printf("visited: %s cost: %d\n", c->name, c->hcost);
			}
			n = n->next;
		}
		level++;
	}
}

t_path *find_path(t_lem_env *lem_env, t_room *start, t_room *end)
{
	t_path	*path;
	t_room	*cur_room;
	t_room	*temp;
	int		lowest_cost;
	int		i;

	if (start->hcost == -1)
		bfs_calc_cost(lem_env, end);

	cur_room = start;
	path = create_path(cur_room->hcost);
	path->size = 0;
	i = 0;
	lowest_cost = INT32_MAX;
	while (cur_room != end)
	{
		t_list *cur_link = *cur_room->links;
		while (cur_link)
		{
			temp = ((t_link*)cur_link->content)->r2;
			if (temp->hcost < lowest_cost)
			{
				lowest_cost = temp->hcost;
				cur_room = temp;
			}
			cur_link = cur_link->next;
		}
		path->rooms[i] = cur_room;
		path->size++;
		i++;
	}
	return (path);
}
