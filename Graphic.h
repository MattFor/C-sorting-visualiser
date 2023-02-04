#define STRICT

#ifndef Graphic_H_INCLUDED
#define Graphic_H_INCLUDED

#include <gl/gl.h>


// Base shape class
typedef struct {
    const char (*m_getType)(const struct Graphic *shape);
    void (*m_draw)(const struct Graphic *shape);
    int (*m_setCoords)(const struct Graphic *shape, int coord_arr[], int size_control_param);
} Graphic;


typedef enum Color {
    White,
    Green,
    Red
} Color;


void Graphic_draw(Graphic *shape);
const char Graphic_getType(Graphic *shape);
int Graphic_setCoords(Graphic *shape, int coord_arr[], int size_control_param);


#endif // Graphic_H_INCLUDED
