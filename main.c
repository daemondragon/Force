#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "force.h"
#include "body.h"
#include "world.h"
#include "collision.h"

//gcc -o test main.c force.c body.c world.c collision.c $(sdl-config --cflags --libs) -lSDL_image

int main()
{
	if	(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		exit(0);
	}
	SDL_Surface* screen = SDL_SetVideoMode(512, 512, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("F.O.R.C.E", NULL);
	
	t_physic_world *world = create_physic_world();
	if (world == NULL)
	{
		exit(0);
	}
	t_body *personnage = create_dynamic_body(5.5, 7.3, 1, 2);
	add_weight(personnage, 40);
	t_force *gravity = create_permanent_force(&(personnage->force), 40, 0);
	if (gravity == NULL)
	{
		fprintf(stderr, "fail : don't alloc\n");
	}
	t_body *bloc = create_static_body(1., 6.5, 1, 1);
	t_body *caisse = create_dynamic_body(10, 6, 1, 1);
	add_weight(caisse, 20);
	add_to_physic_world(world, personnage);
	add_to_physic_world(world, bloc);
	add_to_physic_world(world, caisse);
	SDL_Surface *img_bloc = IMG_Load("bloc.png");
	SDL_Surface *img_perso = IMG_Load("perso.png");
	SDL_Surface *img_caisse = IMG_Load("caisse.png");
	SDL_Rect position;
	
	float time = SDL_GetTicks();
	
	SDL_Event event;
	char quit = 0;
	while (!quit)
	{
		SDL_PollEvent(&event);

		switch(event.type)
		{
			case SDL_QUIT:
			quit = 1;
			break;
			
			case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				quit = 1;
				break;
				
				case SDLK_UP:
				
				break;
				
				case SDLK_RIGHT:
		
				break;
				
				case SDLK_LEFT:

				break;
				
				default:
				break;

			}
			break;
		}
		update_physic_world(world, 40);
		time = SDL_GetTicks();
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		position.x = (personnage->box.x - personnage->box.w) * 16 ;
		position.y = (32 - (personnage->box.y + personnage->box.h)) * 16;
		SDL_BlitSurface(img_perso, NULL, screen, &position);
		position.x = (bloc->box.x - bloc->box.w) * 16;
		position.y = (32 - (bloc->box.y + bloc->box.h)) * 16;
		SDL_BlitSurface(img_bloc, NULL, screen, &position);
		position.x = (caisse->box.x - caisse->box.w) * 16;
		position.y = (32 - (caisse->box.y + caisse->box.h)) * 16;
		SDL_BlitSurface(img_caisse, NULL, screen, &position);
		SDL_Flip(screen);
		SDL_Delay(30);
	}
	
	
	
	delete_physic_world(world);
	return (0);
}
