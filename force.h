#ifndef FORCE_H
#define FORCE_H

typedef struct s_force
{
	float x;
	float y;
	struct s_force *next;
}t_force;

typedef struct s_force_container
{
	t_force *permanent_force;
	t_force contact_force;
	t_force total_force;
}t_force_container;

t_force *create_permanent_force(t_force_container *container, float x, float y);
void delete_permanent_force(t_force_container *container, t_force *remove);
void add_contact_force(t_force_container *container, float x, float y);
void set_contact_force(t_force_container *container, float x, float y);
void calc_total_force(t_force_container *container);

#endif
