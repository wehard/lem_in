/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:38:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/15 13:50:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"
#include "hash_table.h"



/*
void	print_links(t_list *l)
{
	t_room *r;
	t_list *cur;

	r = (t_room*)l->content;
	cur = r->links;
	while (cur)
	{
		ft_printf("%s-%s\n", r->name, ((t_room*)cur->content)->name);
		cur = cur->next;
	}
}
*/

void print_ht(t_ht *ht) {
	for (unsigned int i = 0; i < ht->size; ++i) {
		t_ht_entry *entry = ht->entries[i];
		if (entry == NULL) {
			continue;
		}
		ft_printf("slot[%4d]: ", i);
		for(;;) {
			ft_printf("%s=%s ", entry->key, entry->value);

			if (entry->next == NULL) {
				break;
			}
			entry = entry->next;
		}
		ft_printf("\n");
	}
}

int main(void)
{
	t_env *env;

	env = init_env();
	read_env(env);
	ft_printf("%d\n", env->num_ants);
	ft_lstiter(env->rooms, print_room);
	ft_lstiter(env->links, print_link);

	t_ht *ht;

	ht = ht_create(40);
	ht_set(ht, "one", "dog");
	ht_set(ht, "two", "cat");
	ht_set(ht, "three", "bird");
	ht_set(ht, "four", "snake");

	print_ht(ht);
}
