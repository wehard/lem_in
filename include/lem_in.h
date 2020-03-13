/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:40:56 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/13 15:37:47 by wkorande         ###   ########.fr       */
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
}				t_room;

typedef struct	s_link
{
	t_room		*r1;
	t_room		*r2;
}				t_link;

typedef struct	s_env
{
	int			num_ants;
	t_room		*start;
	t_room		*end;
	t_list		*rooms;
}				t_env;

#endif
