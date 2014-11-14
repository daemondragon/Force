#include <stdlib.h>

#include "force.h"

t_force *create_permanent_force(t_force_container *container, float x, float y)
{
	t_force *add = malloc(sizeof(*add));
	if (add != NULL)
	{
		add->x = x;
		add->y = y;

		add->next = container->permanent_force;
		container->permanent_force = add;
	}
	return (add);
}

void delete_permanent_force(t_force_container *container, t_force *remove)
{
	if (container != NULL)
	{
		if (container->permanent_force != NULL)
		{
			t_force *search = container->permanent_force;
			char finish = 0;
			if (search == remove)
			{
				container->permanent_force = remove->next;
				free(remove);
				finish = 1;
			}
			while (search->next != NULL && !finish)
			{
				if (search->next == remove)
				{
					search->next = search->next->next;
					free(remove);
					finish = 1;
				}
			}
		}
	}
}

void add_contact_force(t_force_container *container, float x, float y)
{
	if (container != NULL)
	{
		container->contact_force.x += x;
		container->contact_force.y += y;
	}
}

void set_contact_force(t_force_container *container, float x, float y)
{
	if (container != NULL)
	{
		container->contact_force.x = x;
		container->contact_force.y = y;
	}
}

void calc_total_force(t_force_container *container)
{
	if (container != NULL)
	{
		float x = 0;
		float y = 0;
		t_force *force = container->permanent_force;
		while (force != NULL)
		{
			x += force->x;
			y += force->y;
			force = force->next;
		}
		x += container->contact_force.x;
		y += container->contact_force.y;

		container->total_force.x = x;
		container->total_force.y = y;
	}
}
