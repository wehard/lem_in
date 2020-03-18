/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:25:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/18 14:24:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include "ft_get_next_line.h"
#include "ft_printf.h"

t_room *new_room(char *name, t_vec2 coord)
{
	t_room *r;

	if (!(r = malloc(sizeof(t_room))))
		ft_panic("new_room: ERROR");
	r->type = UNSET;
	r->name = ft_strdup(name);
	r->coord = coord;
	r->links = malloc(sizeof(t_list*));
	r->occupied = 0;
	r->hcost = -1;
	r->visited = 0;
	return (r);
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

int		ft_strarray_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	read_room(t_lem_env *env, char *line)
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
	if (ft_strarray_len(split) != 3)
	{
		ft_printf("line: %s\n", line);
		ft_panic("read_room: split ERROR");
	}
	room = new_room(split[0], ft_make_vec2(ft_atoi(split[1]), ft_atoi(split[2])));
	if (is_start)
		room->type = START;
	else if (is_end)
		room->type = END;
	else
		room->type = NORMAL;
	ft_lstappend(env->rooms, ft_lstnew(room, sizeof(t_room)));
	env->num_rooms++;
}

void	print_room(t_list *l)
{
	t_room *r;

	r = (t_room*)l->content;
	if (r->type == START)
		ft_printf("##start\n");
	else if (r->type == END)
		ft_printf("##end\n");
	ft_printf("%s %d %d\n", r->name, (int)r->coord.x, (int)r->coord.y);
}
