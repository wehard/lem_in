/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:29:19 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/16 21:19:09 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "lem_in.h"
#include "SDL2/SDL.h"
#include "ft_printf.h"
#include "ft_get_next_line.h"
#include <stdlib.h>
#include <time.h>

void draw_rooms(t_list *rooms, double zoom, SDL_Renderer *renderer)
{
	t_list *cur;
	int size;

	size = 20;
	cur = rooms;
	while (cur)
	{
		t_room r = *(t_room*)cur->content;
		if (r.is_start)
		{
			size *= 2;
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		}
		else if (r.is_end)
		{
			size *= 2;
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		}
		else
		{
			size = 20;
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
		SDL_Rect rect;
		rect.x = ((int)r.coord.x  * zoom) - (size / 2);
		rect.y = ((int)r.coord.y  * zoom) - (size / 2);
		rect.w = size;
		rect.h = size;
		SDL_RenderFillRect(renderer, &rect);
		cur = cur->next;
	}
}

void draw_links(t_list *links, double zoom, SDL_Renderer *renderer)
{
	t_list *cur;

	cur = links;
	while (cur)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		t_link l = *(t_link*)cur->content;
		SDL_RenderDrawLine(renderer, (int)l.r1->coord.x * zoom, (int)l.r1->coord.y * zoom, (int)l.r2->coord.x * zoom, (int)l.r2->coord.y * zoom);
		cur = cur->next;
	}
}

t_ant *create_ants(t_lem_env *env)
{
	t_ant	*ants;
	int		i;

	ants = (t_ant*)malloc(sizeof(t_ant) * env->num_ants);
	i = 0;
	while (i < env->num_ants)
	{
		ants[i].pos = env->start->coord;
		ants[i].target = env->end->coord;
		ants[i].target_room = env->end;
		i++;
	}
	return (ants);
}

void	draw_ants(t_ant *ants, double zoom, t_lem_env *env, SDL_Renderer *renderer)
{
	int size;
	int	i;
	SDL_Rect dest_rect;

	size = 10;
	i = 0;
	while (i < env->num_ants)
	{
		//SDL_SetRenderDrawColor(renderer, 50, 50, 0, 255);
		dest_rect.x = (ants[i].pos.x * zoom) - size / 2;
		dest_rect.y = (ants[i].pos.y * zoom) - size / 2;
		dest_rect.w = size;
		dest_rect.h = size;
		SDL_RenderFillRect(renderer, &dest_rect);
		i++;
	}
}

void	update_ants(t_ant *ants, t_lem_env *env, double delta_time)
{
	int speed;
	t_vec2 dir;
	int	i;

	speed = 10;
	i = 0;
	while (i < env->num_ants)
	{
		t_vec2 target = ants[i].target_room->coord;
		dir = ft_normalize_vec2(ft_sub_vec2(target, ants[i].pos));
		ants[i].pos = ft_add_vec2(ants[i].pos, ft_mul_vec2(dir, delta_time * speed));
		i++;
	}
}

void	update_turn(t_ant *ants, t_lem_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_ants)
	{
		//ft_printf("\nstart links\n");
		//t_room *r = (t_room*)(ft_lstat(ants[i].target_room->links, 0)->content);
		ft_printf("r: %s\n", ants[i].target_room->name);
		//ft_lstiter(r->links, print_link);
		//ants[i].target_room = r;
		//ft_printf("ant %d target: %.2f %.2f\n", i, ants[i].target.x, ants[i].target.y);
		i++;
	}
}

int main(void)
{
	SDL_Window *win;
	SDL_Renderer *renderer;

	t_ant *ants;
	t_lem_env *env;
	double zoom;

	uint64_t now = SDL_GetPerformanceCounter();
	uint64_t last = 0;
	double delta_time = 0;

	srand(time(NULL));

	env = init_env();
	read_env(env);
	ants = create_ants(env);
	ft_printf("ants: %d\n", env->num_ants);
	ft_printf("start: %s %.2f %.2f\n", env->start->name, env->start->coord.x, env->start->coord.y);
	ft_printf("end: %s %.2f %.2f\n", env->end->name,  env->end->coord.x, env->end->coord.y);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		ft_printf("error initializing SDL: %s\n", SDL_GetError());
	win = SDL_CreateWindow("lem_in", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	int quit = 0;
	zoom = 50;
	while (!quit)
	{
		last = now;
		now = SDL_GetPerformanceCounter();
		delta_time = (double)((now - last)*1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;
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
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
					update_turn(ants, env);
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{
				if (event.wheel.y > 0)
					zoom *= 1.1;
				else if (event.wheel.y < 0)
					zoom *= 0.9;
			}
		}
		update_ants(ants, env, delta_time);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		draw_links(env->links, zoom, renderer);
		draw_rooms(env->rooms, zoom, renderer);
		draw_ants(ants, zoom, env, renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return (0);
}
