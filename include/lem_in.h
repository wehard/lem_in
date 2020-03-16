/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:40:56 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/16 19:33:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "vector.h"

typedef struct	s_room
{
	char		*name;
	t_vec2		coord;
	t_list		*links;
	int			occupied;
	int			is_start;
	int			is_end;
}				t_room;

typedef struct	s_link
{
	t_room		*r1;
	t_room		*r2;
}				t_link;

typedef struct	s_lem_env
{
	int			num_ants;
	t_room		*start;
	t_room		*end;
	t_list		*rooms;
	int			num_rooms;
	t_list		*links;
}				t_lem_env;

t_lem_env			*init_env(void);
void			read_env(t_lem_env *env);
void			ft_panic(char *err);

t_room			*new_room(char *name, t_vec2 coord);
void			read_room(t_lem_env *env, char *line);
t_room			*get_room(t_list *rooms, char *name);
void			print_room(t_list *l);

t_link			*new_link(t_room *r1, t_room *r2);
void			read_link(t_lem_env *env, char *line);
void			print_link(t_list *l);

#endif
