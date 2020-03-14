/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:29:19 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/14 13:55:20 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "SDL2/SDL.h"
#include "ft_printf.h"
#include "ft_get_next_line.h"

void draw_rooms(t_list *rooms, SDL_Renderer *renderer)
{
	t_list *cur;
	int zoom;
	int size;

	size = 20;
	zoom = 30;
	cur = rooms;
	while (cur)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		t_room r = *(t_room*)cur->content;
		SDL_Rect rect;
		rect.x = ((int)r.coord.x  * zoom) - (size / 2);
		rect.y = ((int)r.coord.y  * zoom) - (size / 2);
		rect.w = size;
		rect.h = size;
		SDL_RenderFillRect(renderer, &rect);
		cur = cur->next;
	}
}

void draw_links(t_list *links, SDL_Renderer *renderer)
{
	t_list *cur;
	int zoom;

	zoom = 30;
	cur = links;
	while (cur)
	{
		SDL_SetRenderDrawColor(renderer, 127, 127, 255, 255);
		t_link l = *(t_link*)cur->content;
		SDL_RenderDrawLine(renderer, (int)l.r1->coord.x * zoom, (int)l.r1->coord.y * zoom, (int)l.r2->coord.x * zoom, (int)l.r2->coord.y * zoom);
		cur = cur->next;
	}
}

int main(void)
{
	SDL_Window *win;
	SDL_Renderer *renderer;

	t_env *env;

	env = init_env();
	read_env(env);
	ft_printf("ants: %d\n", env->num_ants);
	ft_printf("start: %s %.2f %.2f\n", env->start->name, env->start->coord.x, env->start->coord.y);
	ft_printf("end: %s %.2f %.2f\n", env->end->name,  env->end->coord.x, env->end->coord.y);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		ft_printf("error initializing SDL: %s\n", SDL_GetError());
	win = SDL_CreateWindow("lem_in", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
		draw_links(env->links, renderer);
		draw_rooms(env->rooms, renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return (0);
}
