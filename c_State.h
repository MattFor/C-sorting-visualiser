#define STRICT

#ifndef C_STATE_H_INCLUDED
#define C_STATE_H_INCLUDED


typedef struct {
    int oldIndex;
    int newIndex;
    int offset;
} st_Change;

typedef struct {
    st_Change *changeLog;
    char colorChanged;
} c_State;


void new_c_State(c_State *state, int changeSize);
void new_st_Change(st_Change *change, int oldIndex, int newIndex);

/*
    If both attributes are set to 0 it means this is the start of the program
    Likewise the index 0 in history should also mean that
*/

#endif // C_STATE_H_INCLUDED
