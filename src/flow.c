/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 15:46:16 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/21 17:16:41 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_hashtable.h"
#include "bfs_queue.h"
#include <stdlib.h>
#include "ft_printf.h"
#include "ft_queue.h"

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
	int max_flow;
	//int parent[g->num_nodes];
	t_ht *parent_map;
	parent_map = ft_ht_create(g->num_nodes, ft_ht_hash_int, sizeof(int), sizeof(int));
	int parent_id;

	max_flow = 0;
	while (bfs(g, parent_map, lem_env->start->id, lem_env->end->id))
	{
		int increment = INT32_MAX;
		int id = lem_env->end->id;
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
			id = parent_id;
			t_room *r = (t_room*)(ft_lstat(*lem_env->rooms, id))->content;
			ft_printf("[%s]", r->name);
		}
		ft_printf("\n");
		max_flow += increment;
	}
	ft_printf("max flow: %d\n", max_flow);
}
