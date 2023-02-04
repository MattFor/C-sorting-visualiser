#define STRICT

#ifndef C_LOGIC_H_INCLUDED
#define C_LOGIC_H_INCLUDED

#include "Settings.h"
#include "Utilities.h"
#include "c_State.h"
#include "g_Rectangle.h"


typedef struct {
    c_State *history;       // Responsible for being able to see the entire course of the sort
    int historySize;

    int batchSize;      // Size of the number array to generate/sort

    int sortType;             // Bubble sort, radix LSD etc
    int simVisType;        // Currently only pillars available more to come
    int simSection;         // Decides whether it's f.e the first pass of sorting or rather the last pass checking if it's sorted
    int simStep;              // Current step of the section
    int totalMoves;
    int indexesAffected;
    int currentMove;
    int *numArray;          // The array to be sorted
    int *numArrayCopyForPresort;
    int *walkableArray;
    int *randomSortArray;

    int savedMode;
    int savedMsDelay;

    int finishAnimationStep;
    char sortAnimationStep;
    char showSorting;

    int *addArgs;             // Additional arguments specific to the sortType

    char mode;              // If 0 then auto and complete the action automatically once every msDelay ms
    int msDelay;           // If 1 then manual, person can click a button to go forwards or backwards
    int msDelayCount;

    // Shape holders
    g_Rectangle *visualRepRandomPresort;
    int visualRepRandomPresortSize;

    g_Rectangle *visualRepRectangle;
} Logic;


typedef enum Status {
    CRITICAL_ERROR = -1,
    SUCCESS,                // 0
    TIMESTOP,
    END_OF_ANIMATION,
    SPECIAL_CASE,
    END_OF_SIMULATION
} Status;


int stepForward(Logic *logic, Settings *settings);
int stepBackward(Logic *logic, Settings *settings);

void randomSort(Logic *logic, Settings *settings);
void sortAnimation(Logic *logic, Settings *settings);
void mapSort(Logic *logic, Settings *settings);
void randomSortAnimationForward(Logic *logic, Settings *settings);

// Creator
int setLogic(Logic *logic, Settings *settings);


#endif // C_LOGIC_H_INCLUDED
