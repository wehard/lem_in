/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:38:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/13 18:02:00 by wkorande         ###   ########.fr       */
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

t_env	*init_env(void)
{
	t_env *env;

	if (!(env= malloc(sizeof(t_env))))
		ft_panic("init_env: ERROR");
	env->num_ants = -1;
	env->rooms = NULL;
	env->start = NULL;
	env->end = NULL;
	env->links = NULL;
	return (env);
}

t_room *new_room(char *name, t_vec2 coord)
{
	t_room *r;

	if (!(r = malloc(sizeof(t_room))))
		exit(EXIT_FAILURE);
	r->name = ft_strnew(ft_strlen(name));
	r->name = ft_strcpy(r->name, name);
	r->coord = coord;
	r->links = NULL;
	r->occupied = 0;
	r->is_start = 0;
	r->is_end = 0;
	return (r);
}

void	read_room(t_env *env, char *line)
{
	int		is_start;
	int		is_end;
	t_room *room;

	is_start = 0;
	is_end = 0;
	if (ft_strncmp(line, "##", 2) == 0)
	{
		if (ft_strncmp(line + 2, "start", 5) == 0)
			is_start = 1;
		if (ft_strncmp(line + 2, "end", 3) == 0)
			is_end = 1;
		ft_get_next_line(0, &line);
		if (ft_strncmp(line, "#", 1) == 0)
			ft_panic("read_room: ERROR");
	}
	room = new_room(ft_strtok(line, " "), ft_make_vec2(ft_atoi(ft_strtok(NULL, " ")), ft_atoi(ft_strtok(NULL, " "))));
	room->is_start = is_start;
	room->is_end = is_end;
	ft_lstadd(&env->rooms, ft_lstnew(room, sizeof(t_room)));
	if (is_start)
		env->start = room;
	else if (is_end)
		env->end = room;
}

t_room	*get_room(t_list *rooms, char *name)
{
	t_room *cur;
	if (!rooms)
		ft_panic("get_room: null");
	while (rooms)
	{
		cur = (t_room*)rooms->content;
		if (ft_strcmp(cur->name, name) == 0)
			return (cur);
		rooms = rooms->next;
	}
	return (NULL);
}

void	read_link(t_env *env, char *line)
{
	t_room *r1;
	t_room *r2;

	r1 = get_room(env->rooms, ft_strtok(line, "-"));
	r2 = get_room(env->rooms, ft_strtok(NULL, "-"));
	ft_lstadd(&r1->links, ft_lstnew((void*)r2, sizeof(t_room*)));
	ft_lstadd(&r2->links, ft_lstnew((void*)r1, sizeof(t_room*)));
	t_link *link;
	link = (t_link*)malloc(sizeof(t_link));
	link->r1 = r1;
	link->r2 = r2;
	ft_lstadd(&env->links, ft_lstnew((void*)link, sizeof(t_link)));
}

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

void	print_link(t_list *l)
{
	t_link *link;

	link = (t_link*)l->content;
	ft_printf("%s-%s\n", link->r1->name, link->r2->name);

}

void	print_room(t_list *l)
{
	t_room *r;

	r = (t_room*)l->content;
	if (r->is_start)
		ft_printf("##start\n");
	if (r->is_end)
		ft_printf("##end\n");
	ft_printf("%s %d %d\n", r->name, (int)r->coord.x, (int)r->coord.y);

}

int main(void)
{
	char *line;
	t_env *env;

	env = init_env();

	while (ft_get_next_line(0, &line))
	{
		if (env->num_ants < 0)
			env->num_ants = ft_atoi(line);
		else if (ft_strncmp(line, "##", 2) == 0)
			read_room(env, line);
		else if (ft_strncmp(line, "#", 1) == 0);
			//ft_printf("comment: %s\n", line);
		else if (ft_strchr(line, '-'))
			read_link(env, line);
		else
			read_room(env, line);
		free(line);
	}
	ft_printf("%d\n", env->num_ants);
	ft_lstiter(env->rooms, print_room);
	ft_lstiter(env->links, print_link);
}
