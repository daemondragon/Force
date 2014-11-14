#ifndef COLLISION_H
#define COLLISION_H

#include "body.h"

float mlb_abs(float number);
float penetration_x(t_body *f_body, t_body *s_body);
float penetration_y(t_body *f_body, t_body *s_body);
char is_collide(t_body *f_body, t_body *s_body);
void correct_static_collision(t_body *static_body, t_body *dynamic_body);
void correct_dynamic_collision(t_body *f_body, t_body *s_body);
void correct_collision(t_body *f_body, t_body *s_body);

#endif
