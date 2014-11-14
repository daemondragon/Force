#ifndef BODY_H
#define BODY_H

#include "force.h"

typedef struct s_collision_box
{
	float x;
	float y;
	float w;
	float h;
}t_collision_box;

typedef struct s_body
{
	char dynamic;
	float weight;
	t_collision_box box;
	t_force_container force;
	struct s_body *next;
}t_body;

t_body *create_static_body(float x, float y, float w, float h);
t_body *create_dynamic_body(float x, float y, float w, float h);
void add_weight(t_body *body, float weight);
void delete_body(t_body *body);

#endif
