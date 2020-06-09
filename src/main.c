/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:38:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/09 15:11:47 by wkorande         ###   ########.fr       */
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

	debug_log("ant [%d] moved to room [%s]\n", ant->id, ant->cur_room->name);

	return (1);
}

void print_line(t_list *line)
{
	ft_printf("%s\n", (char*)(line->content));
}

void print_lines(t_list *lines)
{
	char *line;
	t_list *l = lines;
	while (l)
	{
		line = (char*)l->content;
		ft_printf("%s\n", line);
		l = l->next;
	}
}

t_path *find_path(t_list **paths)
{
	t_list *cur;
	t_path *cur_path;
	t_room *first_room;

	cur = *paths;
	while (cur)
	{
		cur_path = (t_path*)cur->content;
		first_room = (t_room*)(*cur_path->rooms)->content;
		if (!first_room->occupied)
			return (cur_path);
		cur = cur->next;
	}
	return (NULL);
}

int main(void)
{
	init_logger("debug.log", "a+");
	t_lem_env *lem_env;

	lem_env = init_env();
	read_env(lem_env);
	lem_env->ants = create_ants(lem_env);

	ft_lstiter(lem_env->lines, print_line);
	ft_printf("\n");

	// print_lines(lem_env->lines);
	t_graph *g = create_graph(lem_env);
	calc_flow(lem_env, g);
	// sort_paths(*(g->augmented_paths));
	// t_list *p = *(g->augmented_paths);
	// while (p)
	// {
	// 	// t_path *c = (t_path*)p->content;
	// 	// print_path(c);
	// 	p = p->next;
	// }
	// int turn  = 0;
	// while (lem_env->end->occupied != lem_env->num_ants)
	// {
	// 	int i = 0;
	// 	debug_log("\033[0;%dm", 34 + turn % 2);
	// 	while (i < lem_env->num_ants)
	// 	{
	// 		t_ant *ant;
	// 		ant = &lem_env->ants[i];
	// 		if (!ant->path && ant->cur_room != lem_env->end)
	// 			ant->path = find_path(g->augmented_paths);
	// 		if (ant->path)
	// 		{
	// 			if (move_ant(ant, path_get_room(ant->path, ant->pi)))
	// 			{
	// 				ft_printf("L%d-%s ", ant->id, ant->cur_room->name);
	// 				ant->pi++;
	// 			}
	// 		}
	// 		i++;
	// 	}
	// 	debug_log("\033[0m");
	// 	ft_printf("\n");
	// 	if (lem_env->end->occupied == lem_env->num_ants)
	// 		debug_log("all ants are home!\n");
	// 	turn++;
	// }
	// destroy_graph(g);
	// del_lem_env(lem_env);
	close_logger();
}
