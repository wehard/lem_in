/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:35:31 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/18 14:28:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"
#include "ft_get_next_line.h"

t_lem_env	*init_env(void)
{
	t_lem_env *env;

	if (!(env= malloc(sizeof(t_lem_env))))
		ft_panic("init_env: ERROR");
	env->num_ants = -1;
	env->ants = NULL;
	env->rooms = malloc(sizeof(t_list*));
	env->num_rooms = 0;
	env->start = NULL;
	env->end = NULL;
	env->links = malloc(sizeof(t_list*));;
	return (env);
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
		ants[i].path = malloc(sizeof(t_path));
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

void	read_env(t_lem_env *env)
{
	char *line;

	while (ft_get_next_line(0, &line) == 1)
	{
		if (ft_strncmp(line, "", 1) == 0)
			break ;
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
	set_start_end(env);
}

void	ft_panic(char *err)
{
	ft_printf("panic: %s\n", err);
	exit(EXIT_FAILURE);
}
