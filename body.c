#include <stdlib.h>

#include "body.h"
#include "force.h"

t_body *create_static_body(float x, float y, float w, float h)
{
	t_body *body = malloc(sizeof(*body));
	if (body != NULL)
	{
		body->box.x = x;
		body->box.y = y;
		body->box.w = w / 2;
		body->box.h = h / 2;
		
		body->dynamic = 0;
		body->weight = 1;
		
		body->force.permanent_force = NULL;
		set_contact_force(&(body->force), 0, 0);
		body->force.total_force.x = 0;
		body->force.total_force.y = 0;
		body->next = NULL;
	}
	return (body);
}

t_body *create_dynamic_body(float x, float y, float w, float h)
{
	t_body *body = malloc(sizeof(*body));
	if (body != NULL)
	{
		body->box.x = x;
		body->box.y = y;
		body->box.w = w / 2;
		body->box.h = h / 2;
		
		body->dynamic = 1;
		body->weight = 1;
		
		body->force.permanent_force = NULL;
		set_contact_force(&(body->force), 0, 0);
		body->force.total_force.x = 0;
		body->force.total_force.y = 0;
		body->next = NULL;
	}
	return (body);
}

void add_weight(t_body *body, float weight)
{
	if (body != NULL)
	{
		if (weight <= 0)
		{
			weight = 1;
		}
		body->weight = weight;
	}
}

void delete_body(t_body *body)
{
	if (body != NULL)
	{
		t_force *remove = body->force.permanent_force;
		while (remove != NULL)
		{
			body->force.permanent_force = remove->next;
			free(remove);
			remove = body->force.permanent_force;
		}
		free(body);
	}
}
