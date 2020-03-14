/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:38:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/14 11:40:52 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"

void	ft_panic(char *err)
{
	ft_printf("panic: %s\n", err);
	exit(EXIT_FAILURE);
}

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


int main(void)
{
	t_env *env;

	env = init_env();
	read_env(env);
	ft_printf("%d\n", env->num_ants);
	ft_lstiter(env->rooms, print_room);
	ft_lstiter(env->links, print_link);
}
