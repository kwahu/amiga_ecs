#include "ecs.c"

void CreateECSTest(tEntity *entities)
{
    //tEntityList *entities = NULL;
    // create an entity list
    //entities = init_entity_list();  

    for(int c=1;c<20;c++)
    {
        // Create an entity
        tEntity *entity = allocateMemory(sizeof(tEntity));
        entity->id = c;
        entity->components = NULL;

        add_entity(entities, entity);

        // Create a component position
        tComponent *component = allocateMemory(sizeof(tComponent));
        component->type = COMPONENT_TYPE_POSITION;
        component->data = allocateMemory(sizeof(tComponentTypePosition));
        *((tComponentTypePosition *)component->data) = (tComponentTypePosition){c, c};

        // Add the component to the entity
        add_component(entity, component);
    }
}