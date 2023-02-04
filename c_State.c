#define STRICT

#include "c_State.h"


void new_c_State(c_State *state, int changeSize)
{
    state->colorChanged = 0;

    state->changeLog = malloc(changeSize * sizeof(st_Change));
}


void new_st_Change(st_Change *change, int oldIndex, int newIndex)
{
    change->oldIndex = oldIndex;
    change->newIndex = newIndex;
    change->offset = newIndex - oldIndex;
}
