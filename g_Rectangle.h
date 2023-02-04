#define STRICT

#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "Graphic.h"


typedef struct {
    Graphic shape;
    Color color;
    int m_coords[8];
} g_Rectangle;


void g_Rectangle_draw(g_Rectangle *rect);
static const char *  g_Rectangle_getType(g_Rectangle *rect);
int g_Rectangle_setCoords(g_Rectangle *rect, int coordinates[], int size_param);

// Constructor
void new_g_Rectangle(g_Rectangle *rect);


#endif // RECTANGLE_H_INCLUDED
