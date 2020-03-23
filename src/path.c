/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 15:40:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/23 22:20:52 by wkorande         ###   ########.fr       */
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

	p = malloc(sizeof(t_path));
	p->rooms = malloc(sizeof(t_list*));
	p->size = 0;
	return (p);
}

void	path_add_room(t_path *p, t_room *room)
{
	t_list *l;

	l = malloc(sizeof(t_list));
	l->content = room;
	l->content_size = sizeof(t_room*);
	ft_lstappend(p->rooms, l);
	p->size++;
}

t_room *path_get_room(t_path *p, int i)
{
	t_list *cur;
	int c;

	c = 0;
	cur = *p->rooms;
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
	t_list *cur;
	void *tmp;

	cur = paths;
	while (cur)
	{
		if (cur->next)
		{
			int cur_size = ((t_path*)cur->content)->size;
			int next_size = ((t_path*)cur->next->content)->size;
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

/*
void	bfs_calc_cost(t_lem_env *lem_env, t_room *from)
{
	t_ht	*visited;
	t_queue	*q;
	int		level;

	visited = ft_ht_create(lem_env->num_rooms, ft_ht_hash_str, 10, 10);
	q = ft_queue_create(QUEUE_REF, lem_env->num_rooms, sizeof(t_room*));
	ft_ht_set(visited, from->name, "1");
	ft_queue_enqueue(q, from);
	level = 0;
	from->hcost = level++;
	while (!ft_queue_isempty(q))
	{
		t_room *r = ft_queue_dequeue(q);
		t_list *n = *r->links;
		while (n)
		{
			t_room *c = ((t_link*)n->content)->r2;
			if (!ft_ht_get(visited, c->name))
			{
				ft_ht_set(visited, c->name, "1");
				ft_queue_enqueue(q, c);
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
	int		blocked;

	blocked = 0;

	if (start->hcost == -1)
		bfs_calc_cost(lem_env, end);

	path = path_create();
	cur_room = start;
	i = 0;
	lowest_cost = INT32_MAX;
	while (cur_room != end)
	{
		t_list *cur_link = *cur_room->links;
		while (cur_link)
		{
			temp = ((t_link*)cur_link->content)->r2;
			if (temp->type != END && temp->occupied)
				blocked = 1;
			else if (temp->hcost < lowest_cost)
			{
				blocked = 0;
				lowest_cost = temp->hcost;
				cur_room = temp;
			}
			cur_link = cur_link->next;
		}
		if (path->size == 1 && blocked)
			return (NULL);
		path_add_room(path, cur_room);
		i++;
	}
	return (path);
}
*/
