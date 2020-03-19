/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 15:46:16 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/19 23:54:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "hash_table.h"
#include "queue.h"
#include <stdlib.h>
#include "ft_printf.h"

int	bfs(t_graph *g, int *parent, int source_id, int sink_id)
{
	t_bfs_queue	*q;
	int		visited[g->num_nodes];
	int		i;

	i = 0;
	while (i < g->num_nodes)
		visited[i++] = FALSE;
	q = bfs_queue_create(g->num_nodes);
	visited[source_id] = TRUE;
	bfs_queue_enqueue(q, source_id);
	parent[source_id] = -1;
	while (!bfs_queue_isempty(q))
	{
		int id = bfs_queue_dequeue(q);
		i = 0;
		while (i < g->num_nodes)
		{
			if (!visited[i] && g->capacity[id][i] - g->flow[id][i] > 0)
			{
				bfs_queue_enqueue(q, i);
				visited[i] = TRUE;
				parent[i] = id;
			}
			i++;
		}
	}
	bfs_queue_destroy(q);
	return (visited[sink_id] == TRUE);
}

void	calc_flow(t_lem_env *lem_env, t_graph *g)
{
	int max_flow;
	int parent[g->num_nodes];
	int i;

	i = 0;
	while (i < g->num_nodes)
		parent[i++] = 0;

	max_flow = 0;
	while (bfs(g, parent, lem_env->end->id, lem_env->start->id))
	{
		int increment = INT32_MAX;
		i = g->num_nodes - 1;
		while (parent[i] >= 0)
		{
			increment = ft_min(increment, g->capacity[parent[i]][i] - g->flow[parent[i]][i]);
			i = parent[i];
		}
		i = lem_env->start->id;
		while (parent[i] >= 0)
		{

			g->flow[parent[i]][i] += increment;
			g->flow[i][parent[i]] -= increment;
			t_room *r = (t_room*)(ft_lstat(*lem_env->rooms, i))->content;
			ft_printf("[%s]", r->name);
			i = parent[i];
		}
		t_room *r = (t_room*)(ft_lstat(*lem_env->rooms, i))->content;
			ft_printf("[%s]\n", r->name);
		max_flow += increment;
	}
	ft_printf("max flow: %d\n", max_flow);
}
