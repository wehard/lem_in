/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:35:31 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/08 17:05:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"
#include "ft_get_next_line.h"

t_lem_env	*init_env(void)
{
	t_lem_env *env;

	if (!(env = malloc(sizeof(t_lem_env))))
		ft_panic("init_env: ERROR");
	env->num_ants = -1;
	env->ants = NULL;
	env->rooms = (t_list**)malloc(sizeof(t_list*));
	env->num_rooms = 0;
	env->start = NULL;
	env->end = NULL;
	env->links = (t_list**)malloc(sizeof(t_list*));
	// env->lines = (t_list**)malloc(sizeof(t_list*));
	env->num_links = 0;
	return (env);
}

void	link_del(void *link, size_t s)
{
	t_link *l = (t_link*)link;
	free(l);
	s = 0;
}

void	room_del(void *room, size_t s)
{
	t_room *r = (t_room*)room;
	free(r->name);
	ft_lstdel(r->links, link_del);
	s = 0;
	free(r->links);
	free(room);
}

void	del_lem_env(t_lem_env *lem_env)
{
	ft_lstdel(lem_env->rooms, room_del);
	ft_lstdel(lem_env->links, link_del);
	free(lem_env->rooms);
	free(lem_env->links);
	int i = 0;
	while (i < lem_env->num_ants)
	{
		free(lem_env->ants[i].path);
		i++;
	}
	free(lem_env->ants);
	t_list *cur_line = lem_env->lines;
	while(cur_line)
	{
		char *l = (char*)cur_line->content;
		free(l);
		free(cur_line);
		cur_line = cur_line->next;
	}
	free(lem_env->lines);
	free(lem_env);
}

t_ant *create_ants(t_lem_env *env)
{
	t_ant	*ants;
	int		i;

	ants = (t_ant*)malloc(sizeof(t_ant) * env->num_ants);
	i = 0;
	while (i < env->num_ants)
	{
		ants[i].id = i + 1;
		ants[i].pi = 0;
		ants[i].pos = env->start->coord;
		ants[i].cur_room = env->start;
		ants[i].target_room = env->start;
		ants[i].path = NULL; //malloc(sizeof(t_path));
		i++;
	}
	return (ants);
}

static void set_start_end(t_lem_env *env)
{
	t_list *cur;
	t_room *r;

	cur = *env->rooms;
	while (cur)
	{
		r = (t_room*)cur->content;
		if (r->type == START)
			env->start = r;
		else if (r->type == END)
			env->end = r;
		cur = cur->next;
	}
}

static int		validate_line(char *line)
{
	if (!line)
		return (0);
	if (line[0] == '\n' || line[0] == '\0')
		return (0);
	return (1);
}

void	read_env(t_lem_env *env)
{
	char *line;
	t_room_type type;

	type = NORMAL;
	line = NULL;
	while (ft_get_next_line(0, &line) == 1)
	{
		// ft_putstr(line);
		if (line[0] != '\0')
		{
			ft_lstappend(&(env->lines), ft_lstnew(line, ft_strlen(line)));
			free(line);
		}
	}
	t_list *cur_line;
	cur_line = env->lines;
	while(cur_line)
	{
		char *lst_line = (char*)(cur_line->content);
		if (!validate_line(lst_line))
			break;
		if (env->num_ants < 0)
			env->num_ants = ft_atoi(lst_line);
		else if (ft_strncmp(lst_line, "##", 2) == 0)
		{
			if (ft_strncmp(lst_line + 2, "start", 5) == 0)
				type = START;
			else if (ft_strncmp(lst_line + 2, "end", 3) == 0)
				type = END;
			cur_line = cur_line->next;
			lst_line = (char*)(cur_line->content);
			read_room(env, type, lst_line);
		}
		else if (ft_strncmp(lst_line, "#", 1) == 0);
		else if (ft_strchr(lst_line, '-'))
			read_link(env, lst_line);
		else
			read_room(env, NORMAL, lst_line);
		cur_line = cur_line->next;
	}
	set_start_end(env);
}

void	ft_panic(char *err)
{
	ft_printf("panic: %s\n", err);
	exit(EXIT_FAILURE);
}
