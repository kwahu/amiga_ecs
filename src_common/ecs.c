#include <stdlib.h>
#include "ecs.h"
#include "component_types.h"
/*
// Create an entity list
tEntityList * init_entity_list()
{
    tEntityList *list = allocateMemory(sizeof(tEntityList));
    //create a root entity here so that we do not have to check if the list is empty in the future
    tEntity *root = allocateMemory(sizeof(tEntity));
    root->id = 0;
    root->components = NULL;

    list->entity = root;
    list->next = NULL;
    
    return list;
}*/

// Add an entity to the list
void add_entity(tEntity *entities, tEntity *entity)
{
    tEntity *current = entities;
    // Find the last entity
    while (current->next != NULL)
    {
        current = current->next;
    }
    //set the current last entity to the new entity
    current->next = entity;

    //set new entity as the last entity
    entity->next = NULL;

    /*entities->next = allocateMemory(sizeof(tEntityList));
    entities->next->entity = entity;
    entities->next->next = NULL;*/
}


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
void update_entities(tEntity *entities)
{
    tEntity *current = entities;
    while (current != NULL)
    {
        tComponentList *current_component = current->components;
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