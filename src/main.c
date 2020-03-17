/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:38:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/18 00:08:24 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"
#include "hash_table.h"
#include "queue.h"

int main(void)
{
	t_lem_env *env;

	env = init_env();
	read_env(env);
	env->ants = create_ants(env);

	ft_printf("%d\n", env->num_ants);
	ft_lstiter(*env->rooms, print_room);
	ft_lstiter(*env->links, print_link);

	// t_ht *ht;

	// ht = ht_create(15);
	// ht_set(ht, "one", "dog");
	// ht_set(ht, "two", "cat");
	// ht_set(ht, "three", "bird");
	// ht_set(ht, "four", "snake");
	// ht_set(ht, "world", "snake");
	//ht_del(ht, "four");

	//print_ht(ht);
	// t_room *r = (t_room*)ft_lstat(*env->rooms, 6)->content;
	// ft_printf("\n%s\n", r->name);
	// ft_lstiter(*r->links, print_room);

	// ft_printf("start: %p\n", env->start);
	// t_list *tmp = *env->rooms;
	// while (tmp)
	// {
	// 	t_room *rt = (t_room*)tmp->content;
	// 	if (ft_strcmp(rt->name, "st") == 0)
	// 		ft_printf("lst start: %p\n", rt);
	// 	tmp = tmp->next;
	// }


	t_path *p = find_path(env);
	if (p != NULL)
	{
		int i = 0;
		while (i < p->length)
		{
			if (p->rooms[i])
				ft_printf("%s > ", p->rooms[i]->name);
			i++;
		}
		ft_printf("\n");
	}
}
