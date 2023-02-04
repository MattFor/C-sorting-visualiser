#define STRICT

#include "g_Rectangle.h"


// Functions "Methods"
void g_Rectangle_draw(g_Rectangle *rect)
{
    switch(rect->color)
    {
    case Green:
        {
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        }
    case Red:
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        }
    }

    glBegin(GL_QUADS);

    glEnable(GL_TEXTURE_2D);

    glVertex2i(rect->m_coords[0], rect->m_coords[1]);
    glVertex2i(rect->m_coords[2], rect->m_coords[3]);
    glVertex2i(rect->m_coords[4], rect->m_coords[5]);
    glVertex2i(rect->m_coords[6], rect->m_coords[7]);

    glEnd();

    if (rect->color > 0)
        glColor3f(1.0f, 1.0f, 1.0f);
}

int g_Rectangle_setCoords(g_Rectangle *rect, int coordinates[], int size_param)
{
    if (size_param != 8)
        return -1;

    for (int i = 0; i < 8; i++)
    {
        rect->m_coords[i] = coordinates[i];
    }

    return 0;
}

static const char *  g_Rectangle_getType(g_Rectangle *rect)
{
    return "rectangle";
}

// Constructor
void new_g_Rectangle(g_Rectangle *rect)
{
    for (int i = 0; i < 8; i++)
    {
        rect->m_coords[i] = 0;
    }

    rect->color = 0;
    rect->shape.m_draw = g_Rectangle_draw;
    rect->shape.m_getType = g_Rectangle_getType;
    rect->shape.m_setCoords = g_Rectangle_setCoords;
}
