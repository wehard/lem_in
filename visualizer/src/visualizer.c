/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:29:19 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/14 12:53:15 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "SDL2/SDL.h"
#include "ft_printf.h"
#include "ft_get_next_line.h"

int main(void)
{
	SDL_Window *win;

	t_env *env;

	env = init_env();
	read_env(env);
	ft_printf("%d\n", env->num_ants);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		ft_printf("error initializing SDL: %s\n", SDL_GetError());
	win = SDL_CreateWindow("lem_in", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
	int quit = 0;
	while (!quit)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				quit = 1;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				ft_printf("key: %s %d\n", SDL_GetKeyName(event.key.keysym.sym), event.key.keysym.scancode);
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					quit = 1;
			}
		}
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}
