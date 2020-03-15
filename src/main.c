/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:38:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/15 14:01:32 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"
#include "hash_table.h"

int main(void)
{
	t_env *env;

	env = init_env();
	read_env(env);
	ft_printf("%d\n", env->num_ants);
	ft_lstiter(env->rooms, print_room);
	ft_lstiter(env->links, print_link);

	t_ht *ht;

	ht = ht_create(20);
	ht_set(ht, "one", "dog");
	ht_set(ht, "two", "cat");
	ht_set(ht, "three", "bird");
	ht_set(ht, "four", "snake");
	ht_set(ht, "world", "snake");
	ht_set(ht, "world", "hello");

	print_ht(ht);
}
