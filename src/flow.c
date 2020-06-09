/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 15:46:16 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/09 13:22:40 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_hashtable.h"
#include "bfs_queue.h"
#include <stdlib.h>
#include "ft_printf.h"
#include "ft_queue.h"
#include "ft_stack.h"

int dfs(t_graph *g, t_ht *parent_map, int source_id, int sink_id)
{
	int	i;
	int	visited[g->num_nodes];
	t_stack *s;

	s = ft_stack_create(g->num_nodes, sizeof(int));
	i = 0;
	while (i < g->num_nodes)
		visited[i++] = FALSE;
	ft_stack_push(s, &source_id);
	while (!ft_stack_isempty(s))
	{
		int cur = *(int*)ft_stack_pop(s);
		if (!visited[cur])
			visited[cur] = TRUE;

		i = 0;
		while (i < g->num_nodes)
		{
			if (!visited[i] && g->capacity[cur][i] - g->flow[cur][i] > 0)
			{
				ft_ht_set(parent_map, &i, &cur);
				ft_stack_push(s, &i);
				visited[i] = TRUE;
				if (i == sink_id)
				{
					ft_stack_destroy(s);
					return (1);
				}
			}
			i++;
		}
	}
	ft_stack_destroy(s);
	return (0);
}

int	bfs(t_graph *g, t_ht *parent_map, int source_id, int sink_id)
{
	int		visited[g->num_nodes];
	int		i;
	t_queue *q;

	if (!(q = ft_queue_create(QUEUE_COPY, g->num_nodes, sizeof(int))))
		ft_panic("queue create failed!");

	i = 0;
	while (i < g->num_nodes)
		visited[i++] = FALSE;
	visited[source_id] = TRUE;
	ft_queue_enqueue(q, &source_id);
	while (!ft_queue_isempty(q))
	{
		int id = *(int*)ft_queue_dequeue(q);
		i = 0;
		while (i < g->num_nodes)
		{
			if (!visited[i] && g->capacity[id][i] - g->flow[id][i] > 0)
			{
				ft_queue_enqueue(q, &i);
				visited[i] = TRUE;
				ft_ht_set(parent_map, &i, &id);
			}
			i++;
		}
	}
	ft_queue_destroy(q);
	return (visited[sink_id] == TRUE);
}

void	calc_flow(t_lem_env *lem_env, t_graph *g)
{
	t_ht	*parent_map;
	int		parent_id;
	int		increment;
	int		id;
	t_path *path;

	parent_map = ft_ht_create(g->num_nodes, ft_ht_hash_int, sizeof(int), sizeof(int));
	while (dfs(g, parent_map, lem_env->start->id, lem_env->end->id))
	{
		path = path_create();
		increment = INT32_MAX;
		id = lem_env->end->id;
		while (ft_ht_get(parent_map, &id))
		{
			parent_id = *(int*)ft_ht_get(parent_map, &id);
			increment = ft_min(increment, g->capacity[parent_id][id] - g->flow[parent_id][id]);
			id = parent_id;
		}
		id = lem_env->end->id;
		while (ft_ht_get(parent_map, &id))
		{
			parent_id = *(int*)ft_ht_get(parent_map, &id);
			g->flow[parent_id][id] += increment;
			g->flow[id][parent_id] -= increment;
			t_room *r = (t_room*)(ft_lstat(lem_env->rooms, id))->content;
			// ft_printf("[%s]", r->name);
			path_add_room(path, r);
			id = parent_id;
		}
		// ft_printf("\n");
		ft_lstappend(g->augmented_paths, ft_lstnewptr(path));
		g->max_flow += increment;
	}
	ft_ht_destroy(parent_map);
}
