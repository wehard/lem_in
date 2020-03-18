/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 18:54:23 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/18 02:01:44 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

#include "vector.h"
#include "lem_in.h"
#include <SDL2/SDL.h>

typedef struct		s_vis_env
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	double			zoom;
}					t_vis_env;

#endif
