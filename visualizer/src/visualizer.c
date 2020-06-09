/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:29:19 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/09 13:44:38 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "lem_in.h"
#include "SDL2/SDL.h"
#include "ft_printf.h"
#include "ft_get_next_line.h"
#include <stdlib.h>
#include <time.h>
#include "debug.h"

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

void	update_turn(t_ant *ants, t_lem_env *lem_env, t_vis_env *vis_env)
{
	int	i;
	t_list *cur;

	if (vis_env->turn_index < 0)
	{
		i = 0;
		while (i < lem_env->num_ants)
		{
			ants[i].target_room = lem_env->start;
			i++;
		}
		vis_env->turn_index++;
		return ;
	}

	if (vis_env->turn_index < vis_env->num_turns)
	{
		cur = ft_lstat(*vis_env->turn_lst, vis_env->turn_index);
		char *line =  (char*)cur->content;
		ft_printf("turn %d: %s\n", vis_env->turn_index, line);
		char **split = ft_strsplit(line, ' ');
		i = 0;
		while (split[i])
		{
			int id = ft_atoi(ft_strchr(split[i], 'L') + 1);
			t_room *room = get_room(lem_env->rooms, ft_strchr(split[i], '-') + 1);
			ants[id - 1].target_room = room;
			i++;
		}

	}
	vis_env->turn_index++;
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
	e->num_turns = 0;
	e->turn_index = 0;
	return (e);
}

void	print_turn(t_list *l)
{
	char *turn;

	turn = (char*)l->content;
	ft_printf("turn: %s\n", turn);
}

/* void read_moves(t_vis_env *vis_env)
{
	char *line;
	vis_env->num_turns = 0;
	vis_env->turn_lst = (t_list**)malloc(sizeof(t_list*));
	*vis_env->turn_lst = NULL;
	while (ft_get_next_line(0, &line) == 1)
	{
		ft_printf("line: %s\n", line);
		t_list *l = ft_lstnew(line, ft_strlen(line) + 1);
		ft_printf("content %s size %d\n", (char*)l->content, l->content_size);
		ft_lstadd(vis_env->turn_lst, l);
		free(line);
		vis_env->num_turns++;
	}
	ft_printf("size: %d\n", ft_lstsize(*vis_env->turn_lst));
} */

void read_turns(t_lem_env *lem_env, t_vis_env *vis_env)
{
	t_list *turns_begin;
	char *line;
	vis_env->num_turns = 0;
	vis_env->turn_lst = (t_list**)malloc(sizeof(t_list*));

	turns_begin = lem_env->lines;
	while (turns_begin)
	{
		line = (char*)turns_begin->content;
		ft_printf("line: %s\n", line);
		if (line[0] == 'L')
		{
			ft_printf("First move found!\n");
			*vis_env->turn_lst = turns_begin;
			vis_env->num_turns = ft_lstsize(*vis_env->turn_lst);
			return ;
		}
		turns_begin = turns_begin->next;
	}

}

int main(void)
{
	t_ant *ants;
	t_lem_env *lem_env;
	t_vis_env *vis_env;

	uint64_t now = SDL_GetPerformanceCounter();
	uint64_t last = 0;
	double delta_time = 0;

	srand(time(NULL));

	lem_env = init_env();
	read_env(lem_env);


	vis_env = init_vis_env("lem_in");
	// ft_printf("%d\n", env->num_ants);
	// ft_lstiter(env->rooms, print_room);
	// ft_lstiter(env->links, print_link);
	read_turns(lem_env, vis_env);

	ants = create_ants(lem_env);
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
				// ft_printf("key: %s %d\n", SDL_GetKeyName(event.key.keysym.sym), event.key.keysym.scancode);
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					quit = 1;
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
					update_turn(ants, lem_env, vis_env);
				if (event.key.keysym.scancode == SDL_SCANCODE_R)
				{
					vis_env->turn_index = -1;
					update_turn(ants, lem_env, vis_env);
				}
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{
				if (event.wheel.y > 0)
					vis_env->zoom *= 1.1;
				else if (event.wheel.y < 0)
					vis_env->zoom *= 0.9;
			}
		}
		update_ants(ants, lem_env, delta_time);

		SDL_SetRenderDrawColor(vis_env->renderer, 255, 255, 255, 255);
		SDL_RenderClear(vis_env->renderer);
		draw_links(lem_env->links, vis_env->zoom, vis_env->renderer);
		draw_rooms(lem_env->rooms, vis_env->zoom, vis_env->renderer);
		draw_ants(ants, vis_env->zoom, lem_env, vis_env->renderer);
		SDL_RenderPresent(vis_env->renderer);
	}
	SDL_DestroyWindow(vis_env->win);
	SDL_DestroyRenderer(vis_env->renderer);
	SDL_Quit();
	return (0);
}
