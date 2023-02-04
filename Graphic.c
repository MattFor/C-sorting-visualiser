#define STRICT

#include "Graphic.h"


// Functions "Methods"
const char Graphic_getType(Graphic *shape)
{
    return shape->m_getType((const struct Graphic*)shape);
}

void Graphic_draw(Graphic *shape)
{
    return shape->m_draw((const struct Graphic*)shape);
}

int Graphic_setCoords(Graphic *shape, int coord_arr[], int size_control_param)
{
    return shape->m_setCoords((const struct Graphic*)shape, coord_arr, size_control_param);
}
