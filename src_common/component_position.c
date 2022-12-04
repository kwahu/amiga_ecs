typedef struct _tComponentTypePosition
{
    int x;
    int y;
} tComponentTypePosition;

void ComponentPositionUpdate(tComponentTypePosition *component)
{
    component->x += 1;
    component->y += 2;

    //*((tComponentTypePosition *)current_component->component->data) = (tComponentTypePosition){1, 1};
}
