/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 16:29:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/19 17:09:06 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

void print_matrix(int **matrix, int size)
{
	int r;
	int c;

	r = 0;
	while (r < size)
	{
		c = 0;
		while (c < size)
		{
			ft_putnbr(matrix[r][c]);
			ft_putchar(' ');
			c++;
		}
		ft_putchar('\n');
		r++;
	}
}

t_graph *create_graph(t_lem_env *lem_env)
{
	t_graph *g;
	int i;
	int j;

	g = (t_graph*)malloc(sizeof(t_graph));
	g->augmented_paths = (t_list**)malloc(sizeof(t_list*));
	g->num_nodes = lem_env->num_rooms;
	g->num_edges = lem_env->num_links;
	g->edges = (int**)malloc(sizeof(int*) * g->num_nodes);
	g->capacity = (int**)malloc(sizeof(int*) * g->num_nodes);
	g->flow = (int**)malloc(sizeof(int*) * g->num_nodes);
	i = 0;
	while (i < g->num_nodes)
	{
		g->edges[i] = (int*)malloc(sizeof(int) * g->num_nodes);
		g->capacity[i] = (int*)malloc(sizeof(int) * g->num_nodes);
		g->flow[i] = (int*)malloc(sizeof(int) * g->num_nodes);
		i++;
	}
	i = 0;
	while (i < g->num_nodes)
	{
		j = 0;
		while (j < g->num_nodes)
		{
			g->edges[i][j] = 0;
			g->capacity[i][j] = 0;
			g->flow[i][j] = 0;
			j++;
		}
		i++;
	}
	t_list *l;
	l = *lem_env->links;
	while (l)
	{
		t_link *ln = (t_link*)l->content;
		g->edges[ln->r1->id][ln->r2->id] = 1;
		g->edges[ln->r2->id][ln->r1->id] = 1;
		g->capacity[ln->r1->id][ln->r2->id] = 1;
		g->capacity[ln->r2->id][ln->r1->id] = 1;
		l = l->next;
	}
	return (g);
}
