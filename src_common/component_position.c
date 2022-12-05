#ifndef _ECS_COMPONENT_TYPE_POSITION_C_
#define _ECS_COMPONENT_TYPE_POSITION_C_

#include "component_position.h"

void ComponentPositionUpdate(tComponentTypePosition *component)
{
    component->x += 1;
    component->y += 2;
}
#endif