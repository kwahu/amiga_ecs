#include <stdlib.h>
#include "ecs.h"
#include "component_types.h"



// adding a component to an entity.
void add_component(tEntity *entity, tComponent *component)
{
    tComponentList *new_node = allocateMemory(sizeof(tComponentList));
    new_node->component = component;
    new_node->next = entity->components;
    entity->components = new_node;
}

// retrieving a component from an entity.
tComponent *get_component(tEntity *entity, int type)
{
    tComponentList *current = entity->components;
    while (current != NULL)
    {
        if (current->component->type == type)
        {
            return current->component;
        }
        current = current->next;
    }
    return NULL;
}

// updating the entities and their components.
void update_entities(tEntityList *entities)
{
    tEntityList *current = entities;
    while (current != NULL)
    {
        tComponentList *current_component = current->entity->components;
        while (current_component != NULL)
        {
            // update the component based on its type.
            switch (current_component->component->type)
            {
            case COMPONENT_TYPE_POSITION:
                ComponentPositionUpdate((tComponentTypePosition *)current_component->component->data);
                break;
            }
            
            current_component = current_component->next;
        }
        current = current->next;
    }
}


//func