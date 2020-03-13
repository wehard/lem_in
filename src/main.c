/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:38:35 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/13 13:48:25 by wkorande         ###   ########.fr       */
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
	return (r);
}

void	read_room(t_env *env, char *line)
{
	int		is_start;
	int		is_end;
	t_room *room;
	char	**split;

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
	split = ft_strsplit(line, ' ');
	room = new_room(split[0], ft_make_vec2(ft_atoi(split[1]), ft_atoi(split[2])));
	ft_lstadd(&env->rooms, ft_lstnew(room, sizeof(t_room)));
	if (is_start)
		env->start = room;
	else if (is_end)
		env->end = room;
	ft_printf("room: %s\n", line);
}

void	read_link(t_env *env, char *line)
{
	env = (void*)0;
	ft_printf("link: %s\n", line);
}

void	print_room(t_list *l)
{
	t_room *r;

	r = (t_room*)l->content;
	ft_printf("room: %s (%.2f, %.2f)\n", r->name, r->coord.x, r->coord.y);
}

int main(void)
{
	char *line;
	t_env *env;

	env = init_env();

	while (ft_get_next_line(0, &line))
	{

		if (ft_strncmp(line, "##", 2) == 0)
			read_room(env, line);
		else if (ft_strncmp(line, "#", 1) == 0)
			ft_printf("comment: %s\n", line);
		else if (ft_strncmp(line + 1, "-", 1) == 0)
			read_link(env, line);
		else
			read_room(env, line);
		free(line);
	}
	ft_lstiter(env->rooms, print_room);
}
