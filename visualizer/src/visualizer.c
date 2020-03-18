/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:29:19 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/18 02:10:43 by wkorande         ###   ########.fr       */
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
		if (r.type == START)
		{
			size = 30;
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		}
		else if (r.type == END)
		{
			size = 30;
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
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
		SDL_RenderDrawRect(renderer, &rect);
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

	speed = 20;
	i = 0;
	while (i < env->num_ants)
	{
		t_vec2 target = ants[i].target_room->coord;
		if (ft_len_vec2(ft_sub_vec2(target, ants[i].pos)) > 0.2)
		{
			dir = ft_normalize_vec2(ft_sub_vec2(target, ants[i].pos));
			ants[i].pos = ft_add_vec2(ants[i].pos, ft_mul_vec2(dir, delta_time * speed));
		}
		else
			ants[i].pos = ants[i].target_room->coord;
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
		t_list *l = ft_lstat(*ants[i].target_room->links, rand() % ft_lstsize(*ants[i].target_room->links));
		t_room *r = ((t_link*)l->content)->r2;
		//ft_printf("r: %s\n", r->name);
		//ft_lstiter(*r->links, print_link);
		ants[i].target_room = r;
		//ft_printf("ant %d target: %.2f %.2f\n", i, ants[i].target_room->coord.x, ants[i].target_room->coord.y);
		i++;
	}
}

t_vis_env	*init_vis_env(const char *title)
{
	t_vis_env *e;

	if (!(e = (t_vis_env*)malloc(sizeof(t_vis_env))))
		return (NULL);
	e->zoom = 50;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		ft_printf("error initializing SDL: %s\n", SDL_GetError());
	e->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
	e->renderer = SDL_CreateRenderer(e->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	return (e);
}

int main(void)
{

	t_ant *ants;
	t_lem_env *env;
	t_vis_env *v_env;

	uint64_t now = SDL_GetPerformanceCounter();
	uint64_t last = 0;
	double delta_time = 0;

	srand(time(NULL));

	env = init_env();
	read_env(env);

	v_env = init_vis_env("lem_in");
	// ft_printf("%d\n", env->num_ants);
	// ft_lstiter(env->rooms, print_room);
	// ft_lstiter(env->links, print_link);


	ants = create_ants(env);
	// ft_printf("start: %s %.2f %.2f\n", env->start->name, env->start->coord.x, env->start->coord.y);
	// ft_printf("end: %s %.2f %.2f\n", env->end->name,  env->end->coord.x, env->end->coord.y);


	int quit = 0;
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
					v_env->zoom *= 1.1;
				else if (event.wheel.y < 0)
					v_env->zoom *= 0.9;
			}
		}
		update_ants(ants, env, delta_time);

		SDL_SetRenderDrawColor(v_env->renderer, 255, 255, 255, 255);
		SDL_RenderClear(v_env->renderer);
		draw_links(*env->links, v_env->zoom, v_env->renderer);
		draw_rooms(*env->rooms, v_env->zoom, v_env->renderer);
		draw_ants(ants, v_env->zoom, env, v_env->renderer);
		SDL_RenderPresent(v_env->renderer);
	}
	SDL_DestroyWindow(v_env->win);
	SDL_DestroyRenderer(v_env->renderer);
	SDL_Quit();
	return (0);
}
