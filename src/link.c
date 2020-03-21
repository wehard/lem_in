/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:27:43 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/21 12:47:12 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include "ft_printf.h"

t_link	*new_link(t_room *r1, t_room *r2)
{
	t_link *link;

	link = (t_link*)malloc(sizeof(t_link));
	link->r1 = r1;
	link->r2 = r2;
	return (link);
}

void	read_link(t_lem_env *env, char *line)
{
	t_room *r1;
	t_room *r2;
	char	**split;

	split = ft_strsplit(line, '-');
	r1 = get_room(*env->rooms, split[0]);
	r2 = get_room(*env->rooms, split[1]);
	//ft_lstappend(r1->links, ft_lstnew((void*)new_link(r1, r2), sizeof(t_link)));
	//ft_lstappend(r2->links, ft_lstnew((void*)new_link(r2, r1), sizeof(t_link)));
	ft_lstappend(env->links, ft_lstnew((void*)new_link(r1, r2), sizeof(t_link)));
	env->num_links++;
}

void	print_link(t_list *l)
{
	t_link *link;

	link = (t_link*)l->content;
	ft_printf("%s-%s\n", link->r1->name, link->r2->name);
}
