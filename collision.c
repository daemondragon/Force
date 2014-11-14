#include <stdlib.h>

#include "collision.h"
#include "body.h"
#include "force.h"

float mlb_abs(float number)
{
	if (number < 0)
	{
		number *= -1;
	}
	return (number);
}

float penetration_x(t_body *f_body, t_body *s_body)
{
	return (mlb_abs(f_body->box.x - s_body->box.x) - (f_body->box.w + s_body->box.w));
}

float penetration_y(t_body *f_body, t_body *s_body)
{
	return (mlb_abs(f_body->box.y - s_body->box.y) - (f_body->box.h + s_body->box.h));
}

char is_collide(t_body *f_body, t_body *s_body)
{
	if (penetration_x(f_body, s_body) <= 0.)
	{
		if (penetration_y(f_body, s_body) <= 0.)
		{
			return (1);
		}
	}
	return (0);
}

void correct_static_collision(t_body *static_body, t_body *dynamic_body)
{
	if (penetration_x(static_body, dynamic_body) > penetration_y(static_body, dynamic_body))
	{
		/*x axis penetration*/
		float direction = dynamic_body->force.total_force.x / mlb_abs(dynamic_body->force.total_force.x);
		dynamic_body->box.x = static_body->box.x - (dynamic_body->box.w + static_body->box.w) * direction;

		add_contact_force(&(dynamic_body->force), -dynamic_body->force.total_force.x, static_body->force.contact_force.y);
	}
	else
	{
		/*y axis penetration*/
		float direction = dynamic_body->force.total_force.y / mlb_abs(dynamic_body->force.total_force.y);
		dynamic_body->box.y = static_body->box.y - ((dynamic_body->box.h + static_body->box.h) * direction);

		add_contact_force(&(dynamic_body->force), static_body->force.contact_force.x, -dynamic_body->force.total_force.y);
	}
}

void correct_dynamic_collision(t_body *f_body, t_body *s_body)
{
	t_force common_force;
	t_force total_force;
	float weight;
	if (penetration_x(f_body, s_body) > penetration_y(f_body, s_body))
	{
		/*x axis penetration*/
		/*calculate the total force for the total body and divise it*/
		calc_total_force(&(f_body->force));
		calc_total_force(&(s_body->force));
		total_force.x = f_body->force.total_force.x;
		total_force.y = s_body->force.total_force.x;
		
		common_force.x = total_force.x + total_force.y;
		weight = f_body->weight + s_body->weight;
		common_force.y = common_force.x / weight * s_body->weight;
		common_force.x = common_force.x / weight * f_body->weight;
		
		add_contact_force(&(f_body->force), common_force.x - total_force.x, 0);
		add_contact_force(&(s_body->force), common_force.y - total_force.y, 0);

		/*correct collision*/
		float average_x = (f_body->box.x + s_body->box.x) / 2;
		float direction = average_x - f_body->box.x;
		if (direction < 0)
		{
			direction = -1;
		}
		else
		{
			direction = 1;
		}
		f_body->box.x = average_x - (f_body->box.w * direction);
		s_body->box.x = average_x + (s_body->box.w * direction);
	}
	else
	{
		/*y axis penetration*/
		/*calculate the total force for the total body and divise it*/
		calc_total_force(&(f_body->force));
		calc_total_force(&(s_body->force));
		total_force.x = f_body->force.total_force.y;
		total_force.y = s_body->force.total_force.y;
		
		common_force.y = total_force.x + total_force.y;
		weight = f_body->weight + s_body->weight;
		common_force.x = common_force.y / weight * f_body->weight;
		common_force.y = common_force.y / weight * s_body->weight;

		add_contact_force(&(f_body->force), 0, common_force.x - total_force.x);
		add_contact_force(&(s_body->force), 0, common_force.y - total_force.y);

		/*correct collision*/
		float average_y = (f_body->box.y + s_body->box.y) / 2;
		float direction = average_y - f_body->box.y;
		if (direction < 0)
		{
			direction = -1;
		}
		else
		{
			direction = 1;
		}
		f_body->box.y = average_y - (f_body->box.h * direction);
		s_body->box.y = average_y + (s_body->box.h * direction);
	}
}

void correct_collision(t_body *f_body, t_body *s_body)
{
	if (f_body->dynamic && !s_body->dynamic)
	{
		correct_static_collision(s_body, f_body);
	}
	else if (!f_body->dynamic && s_body->dynamic)
	{
		correct_static_collision(f_body, s_body);
	}
	else if (f_body->dynamic && s_body->dynamic)
	{
		correct_dynamic_collision(f_body, s_body);
	}	
}

