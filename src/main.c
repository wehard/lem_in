/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:38:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/18 01:27:37 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"
#include "hash_table.h"
#include "queue.h"
#include "debug.h"

int move_ant(t_ant *ant, t_room *room)
{
	if (ant->cur_room->type == END)
	{
		debug_log("move_ant: ant is in end room\n");
		return (0);
	}
	if (room->type != END && room->occupied)
	{
		debug_log("move_ant: room occupied!\n");
		return (0);
	}
	ant->cur_room->occupied = 0;
	ant->cur_room = room;
	if (room->type == END)
		ant->cur_room->occupied++;
	else
		ant->cur_room->occupied = 1;
	ft_printf("L%d-%s ", ant->id, ant->cur_room->name);
	return (1);
}

int main(void)
{
	init_logger("debug.log", "a+");
	t_lem_env *env;

	env = init_env();
	read_env(env);
	env->ants = create_ants(env);

	ft_printf("%d\n", env->num_ants);
	ft_lstiter(*env->rooms, print_room);
	ft_lstiter(*env->links, print_link);
	ft_printf("\n");

	t_path *p = find_path(env, env->start, env->end);
	// if (p != NULL)
	// {
	// 	int i = 0;
	// 	while (i < p->size)
	// 	{
	// 		if (p->rooms[i])
	// 			ft_printf("%s > ", p->rooms[i]->name);
	// 		i++;
	// 	}
	// 	ft_printf("\n");
	// }
	while (env->end->occupied != env->num_ants)
	{
		int i = 0;
		while (i < env->num_ants)
		{
			if (move_ant(&env->ants[i], p->rooms[env->ants[i].pi]))
				env->ants[i].pi++;
			i++;
		}
		ft_printf("\n");
	}
	close_logger();
}
