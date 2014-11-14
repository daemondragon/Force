#include <stdlib.h>

#include "body.h"
#include "force.h"
#include "world.h"
#include "collision.h"

t_physic_world *create_physic_world()
{
	t_physic_world *world = malloc(sizeof(*world));
	if (world != NULL)
	{
		world->static_body = NULL;
		world->dynamic_body = NULL;
	}
	return (world);
}

void delete_physic_world(t_physic_world *world)
{
	if (world != NULL)
	{
		t_body *remove = world->static_body;
		while (remove != NULL)
		{
			world->static_body = remove->next;
			delete_body(remove);
			remove = world->static_body;
		}
		remove = world->dynamic_body;
		while (remove != NULL)
		{
			world->dynamic_body = remove->next;
			delete_body(remove);
			remove = world->dynamic_body;
		}
		free(world);
	}
}

char add_to_physic_world(t_physic_world *world, t_body *body)
{
	if (world != NULL && body != NULL)
	{		
		if (body->dynamic)
		{
			body->next = world->dynamic_body;
			world->dynamic_body = body;
		}
		else
		{
			body->next = world->static_body;
			world->static_body = body;
		}
		return (1);
	}
	else
	{
		return (0);
	}
}

void update_force(t_body *body, int millisecond_time)
{
	calc_total_force(&(body->force));
	
	body->force.total_force.x *= (millisecond_time / 1000.0) / body->weight;
	body->force.total_force.y *= (millisecond_time / 1000.0) / body->weight;
	
	body->box.x += body->force.total_force.x;
	body->box.y += body->force.total_force.y;
	
	set_contact_force(&(body->force), 0, 0);
}

void update_physic_world(t_physic_world *world, int millisecond_time)
{
	t_body *update = world->dynamic_body;
	while (update != NULL)
	{
		update_force(update, millisecond_time);
		update = update->next;
	}
	/*now, we have to detect all the collision*/
	t_body *collide_with = world->static_body;;
	update = world->dynamic_body;
	while (update != NULL)
	{
		/*collide with static body*/
		while (collide_with != NULL)
		{
			if (is_collide(update, collide_with))
			{
				correct_collision(update, collide_with);
			}
			collide_with = collide_with->next;
		}
		/*collide with dynamic body*/
		collide_with = update->next;
		while (collide_with != NULL)
		{
			if (is_collide(update, collide_with))
			{
				correct_collision(update, collide_with);
			}
			collide_with = collide_with->next;
		}
		
		update = update->next;
	}
	
}
