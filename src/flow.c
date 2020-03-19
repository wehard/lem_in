/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 15:46:16 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/19 18:24:59 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "hash_table.h"
#include "queue.h"

int	bfs(t_graph *g, int source_id, int sink_id)
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
			}
			i++;
		}
	}
	bfs_queue_destroy(q);
	return (visited[sink_id] == TRUE);
}

void	calc_flow(t_graph *g, int source_id, int sink_id)
{
	int residual_capacity[g->num_nodes][g->num_nodes];

	while (bfs(g, source_id, sink_id))
	{
		// need hashtable id to id to get parent and then augmented path

	}

}
