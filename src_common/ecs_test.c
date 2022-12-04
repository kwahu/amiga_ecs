#include "ecs.c"

tEntityList* CreateECSTest()
{

    // Create an entity
    tEntity *entity = allocateMemory(sizeof(tEntity));
    entity->id = 1;
    entity->components = NULL;

    // create an entity list
    tEntityList *entities = allocateMemory(sizeof(tEntityList));
    entities->entity = entity;
    entities->next = NULL;

    // Create a component position
    tComponent *component = allocateMemory(sizeof(tComponent));
    component->type = COMPONENT_TYPE_POSITION;
    component->data = allocateMemory(sizeof(tComponentTypePosition));
    *((tComponentTypePosition *)component->data) = (tComponentTypePosition){0, 0};

    // Add the component to the entity
    add_component(entity, component);

    return entities;
}