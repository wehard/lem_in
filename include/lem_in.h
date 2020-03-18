/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:40:56 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/18 12:19:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "vector.h"

// # define START 0
// # define END 1
// # define NORMAL 2

typedef enum
{
	UNSET,
	START,
	END,
	NORMAL
}				t_room_type;

typedef struct	s_room
{
	t_room_type	type;
	char		*name;
	t_vec2		coord;
	t_list		**links;
	int			occupied;
	int			hcost;
	int			visited;
}				t_room;

typedef struct	s_link
{
	t_room		*r1;
	t_room		*r2;
}				t_link;

typedef struct	s_path
{
	t_list		**rooms;
	int			size;
}				t_path;

typedef struct	s_ant
{
	int			id;
	int			pi;
	t_vec2		pos;
	t_path		*path;
	t_room		*target_room;
	t_room		*cur_room;
}				t_ant;

typedef struct	s_lem_env
{
	int			num_ants;
	t_ant		*ants;
	t_room		*start;
	t_room		*end;
	t_list		**rooms;
	int			num_rooms;
	t_list		**links;
}				t_lem_env;

t_lem_env			*init_env(void);
void			read_env(t_lem_env *env);
t_ant			*create_ants(t_lem_env *env);
void			ft_panic(char *err);

t_room			*new_room(char *name, t_vec2 coord);
void			read_room(t_lem_env *env, char *line);
t_room			*get_room(t_list *rooms, char *name);
void			print_room(t_list *l);

t_link			*new_link(t_room *r1, t_room *r2);
void			read_link(t_lem_env *env, char *line);
void			print_link(t_list *l);

t_path			*find_path(t_lem_env *lem_env, t_room *start, t_room *end);
t_room			*path_get_room(t_path *p, int i);
void			path_add_room(t_path *p, t_room *room);
#endif
