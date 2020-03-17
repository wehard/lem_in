/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 18:54:23 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/16 20:23:44 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

#include "vector.h"
#include "lem_in.h"

typedef struct	s_ant
{
	t_vec2		pos;
	t_vec2		target;
	t_room		*target_room;
}				t_ant;

#endif
