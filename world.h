#ifndef WORLD_H
#define WORLD_H

typedef struct s_physic_world
{
	t_body *static_body;
	t_body *dynamic_body;
}t_physic_world;

t_physic_world *create_physic_world();
void delete_physic_world(t_physic_world *world);
char add_to_physic_world(t_physic_world *world, t_body *body);
void update_force(t_body *body, int millisecond_time);
void update_physic_world(t_physic_world *world, int millisecond_time);

#endif
