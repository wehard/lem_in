/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:38:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/23 17:00:17 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"
#include "ft_hashtable.h"
#include "debug.h"

int move_ant(t_ant *ant, t_room *room)
{
	if (ant->cur_room->type == END)
		return (0);
	else if (room->type != END && room->occupied)
	{
		debug_log("move_ant: room occupied! ant %d tried room %s\n", ant->id, room->name);
		return (0);
	}
	ant->cur_room->occupied = 0;
	ant->cur_room = room;
	if (room->type == END)
		ant->cur_room->occupied++;
	else
		ant->cur_room->occupied = 1;
	ft_printf("L%d-%s ", ant->id, ant->cur_room->name);
	debug_log("ant [%d] moved to room [%s]\n", ant->id, ant->cur_room->name);

	return (1);
}

void print_line(t_list *line)
{
	ft_printf("%s\n", (char*)(line->content));
}

int main(void)
{
	// init_logger("debug.log", "a+");
	t_lem_env *lem_env;

	lem_env = init_env();
	read_env(lem_env);
	lem_env->ants = create_ants(lem_env);

	ft_lstiter(*lem_env->lines, print_line);

	// ft_printf("%d\n", lem_env->num_ants);
	// ft_lstiter(*lem_env->rooms, print_room);
	// ft_lstiter(*lem_env->links, print_link);
	// ft_printf("\n");

	// int turn  = 0;
	// while (lem_env->end->occupied != lem_env->num_ants)
	// {
	// 	int i = 0;
	// 	debug_log("\033[0;%dm", 34 + turn % 2);
	// 	while (i < lem_env->num_ants)
	// 	{
	// 		t_ant *ant;
	// 		ant = &lem_env->ants[i];
	// 		ant->path = find_path(lem_env, ant->cur_room, lem_env->end);
	// 		if (ant->path)
	// 			move_ant(ant, path_get_room(ant->path, 0));
	// 		i++;
	// 	}
	// 	debug_log("\033[0m");
	// 	ft_printf("\n");
	// 	if (lem_env->end->occupied == lem_env->num_ants)
	// 		debug_log("all ants are home!\n");
	// 	turn++;
	// }


	//t_graph *g = create_graph(lem_env);
	//ft_printf("edges\n");
	//print_matrix(g->edges, g->num_nodes);
	//ft_printf("capacity\n");
	//print_matrix(g->capacity, g->num_nodes);
	//ft_printf("flow\n");
	//print_matrix(g->flow, g->num_nodes);
	//calc_flow(lem_env, g);
	del_lem_env(lem_env);
	// close_logger();
}
