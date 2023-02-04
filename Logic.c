#define STRICT

#include "Logic.h"


// Functions "Methods"
int stepForward(Logic *logic, Settings *settings)
{
    if (logic->mode == 0 && !(logic->msDelayCount <= 0))
        return TIMESTOP;

    if (logic->currentMove == logic->totalMoves)
    {
        /// Hit the end of the walkable simulation
        if (logic->finishAnimationStep == -1)
        {
            printf("Hit the end of the simulation.\n");
            logic->finishAnimationStep++;
        }

        /// Hit the end of the finish animation
        if (logic->finishAnimationStep == settings->batchSize)
        {
            logic->mode = logic->savedMode;
            logic->savedMode = -1;
            logic->msDelay = logic->savedMsDelay;
            logic->savedMsDelay = -1;

            return END_OF_ANIMATION;
        }

        logic->mode = 0;
        logic->msDelay = 300;

        logic->visualRepRectangle[logic->finishAnimationStep].color = 1;

        if (logic->finishAnimationStep < settings->batchSize)
            logic->finishAnimationStep++;

        printf("Finish animation sF %d/%d\n", logic->finishAnimationStep, settings->batchSize);

        return SUCCESS;
    }

    for (int i = 0; i < settings->moveMultiplier; i++)
    {
        logic->currentMove++;

        if (logic->currentMove > logic->totalMoves) {
            logic->currentMove = logic->totalMoves;

            printf("Hit end of simulation.\n");
            return END_OF_SIMULATION;
        }

        logic->indexesAffected++;
        printf("Stepping forwards to move %d indexes affected %d\n", logic->currentMove, ++logic->indexesAffected);

        switch(logic->sortType)
        {                    // 2 indexes being swapped, trivial stuff.
        case 0:         // Bubble sort
        case 1:         // Selection sort
        case 2:         // Cocktail sort
        case 3:         // Gnome sort
            {
                int indexOld = logic->history[logic->currentMove].changeLog[0].oldIndex;
                int indexNew = logic->history[logic->currentMove].changeLog[0].newIndex;

                int temporary = logic->walkableArray[indexOld] ;

                logic->walkableArray[indexOld] = logic->walkableArray[indexNew];
                logic->walkableArray[indexNew] = temporary;

                int old_x_coord = indexOf(logic->walkableArray, settings->batchSize,  logic->walkableArray[indexOld]);
                int old_y_coord = settings->height/settings->batchSize * (logic->walkableArray[indexOld] + 1);

                int old_coord_arr[] = {
                             settings->width/settings->batchSize * (old_x_coord + 1),
                             0,
                             settings->width/settings->batchSize * old_x_coord ,
                             0,
                             settings->width/settings->batchSize * old_x_coord,
                             old_y_coord,
                             settings->width/settings->batchSize * (old_x_coord + 1),
                             old_y_coord
                };

                logic->visualRepRectangle[indexOld].shape.m_setCoords(&logic->visualRepRectangle[indexOld], old_coord_arr, sizeof(old_coord_arr) / sizeof(old_coord_arr[0]));

                int new_x_coord = indexOf(logic->walkableArray, settings->batchSize,  logic->walkableArray[indexNew]);
                int new_y_coord = settings->height/settings->batchSize * (logic->walkableArray[indexNew] + 1);

                int new_coord_arr[] = {
                             settings->width/settings->batchSize * (new_x_coord + 1),
                             0,
                             settings->width/settings->batchSize * new_x_coord ,
                             0,
                             settings->width/settings->batchSize * new_x_coord,
                             new_y_coord,
                             settings->width/settings->batchSize * (new_x_coord + 1),
                             new_y_coord
                };

                logic->visualRepRectangle[indexNew].shape.m_setCoords(&logic->visualRepRectangle[indexNew], new_coord_arr, sizeof(new_coord_arr) / sizeof(new_coord_arr[0]));
                break;
            }
        }
    }

    if (logic->mode == 0 && logic->msDelayCount < logic->msDelay)
        logic->msDelayCount = logic->msDelay;

    return SUCCESS;
}

int stepBackward(Logic *logic, Settings *settings)
{
    if (logic->finishAnimationStep >= 0)
    {
        if (settings->batchSize == logic->finishAnimationStep)
        {
            logic->savedMode = logic->mode;
            logic->mode = 0;
            logic->savedMsDelay = logic->msDelay;
            logic->msDelay = 300;

            return END_OF_ANIMATION;
        }

        if (logic->finishAnimationStep > 0)
            logic->finishAnimationStep--;

        logic->visualRepRectangle[logic->finishAnimationStep].color = 0;

        printf("Finish animation sB %d/%d\n", logic->finishAnimationStep, settings->batchSize);

        if (logic->finishAnimationStep == 0)
        {
            logic->finishAnimationStep = -1;

            // Set back proper settings
            logic->savedMode = -3;
            logic->mode = logic->savedMode;
            logic->savedMsDelay = -1;
            logic->msDelay = logic->savedMsDelay;
        }

        return SUCCESS;
    }

    if (logic->savedMode == -3)
    {
        logic->savedMode = -1;
        return SPECIAL_CASE;
    }

    for (int i = settings->moveMultiplier; i > 0; i--)
    {
        logic->currentMove--;

        if (logic->currentMove < 0) {
            logic->currentMove = 0;

            printf("Hit the start of the simulation.\n");
            return END_OF_SIMULATION;
        }

        logic->indexesAffected--;
        printf("Stepping forwards to move %d indexes affected %d\n", logic->currentMove, --logic->indexesAffected);

        switch(logic->sortType)
        {                    // 2 indexes being swapped, trivial stuff.
        case 0:         // Bubble sort
        case 1:         // Selection sort
        case 2:         // Cocktail sort
        case 3:         // Gnome sort
            {
                int indexOld = logic->history[logic->currentMove + 1].changeLog[0].newIndex;
                int indexNew = logic->history[logic->currentMove + 1].changeLog[0].oldIndex;

                int temporary = logic->walkableArray[indexOld] ;

                logic->walkableArray[indexOld] = logic->walkableArray[indexNew];
                logic->walkableArray[indexNew] = temporary;

                int old_x_coord = indexOf(logic->walkableArray, settings->batchSize,  logic->walkableArray[indexOld]);
                int old_y_coord = settings->height/settings->batchSize * (logic->walkableArray[indexOld] + 1);

                int old_coord_arr[] = {
                             settings->width/settings->batchSize * (old_x_coord + 1),
                             0,
                             settings->width/settings->batchSize * old_x_coord ,
                             0,
                             settings->width/settings->batchSize * old_x_coord,
                             old_y_coord,
                             settings->width/settings->batchSize * (old_x_coord + 1),
                             old_y_coord
                };

                logic->visualRepRectangle[indexOld].shape.m_setCoords(&logic->visualRepRectangle[indexOld], old_coord_arr, sizeof(old_coord_arr) / sizeof(old_coord_arr[0]));

                int new_x_coord = indexOf(logic->walkableArray, settings->batchSize,  logic->walkableArray[indexNew]);
                int new_y_coord = settings->height/settings->batchSize * (logic->walkableArray[indexNew] + 1);

                int new_coord_arr[] = {
                             settings->width/settings->batchSize * (new_x_coord + 1),
                             0,
                             settings->width/settings->batchSize * new_x_coord ,
                             0,
                             settings->width/settings->batchSize * new_x_coord,
                             new_y_coord,
                             settings->width/settings->batchSize * (new_x_coord + 1),
                             new_y_coord
                };

                logic->visualRepRectangle[indexNew].shape.m_setCoords(&logic->visualRepRectangle[indexNew], new_coord_arr, sizeof(new_coord_arr) / sizeof(new_coord_arr[0]));
                break;
            }
        }
    }
}


void mapSort(Logic *logic, Settings *settings)
{
 switch(logic->sortType)
    {
    case 0:         // Bubble sort
        {
            // First sort to get the number of accesses need for allocating memory later
            for (int i = 0; i < settings->batchSize - 1; i++)
            {
                // Last i elements are already in place
                for (int j = 0; j < settings->batchSize - i - 1; j++)
                {
                    if (logic->numArrayCopyForPresort[j] > logic->numArrayCopyForPresort[j + 1])
                    {
                        swapNumbers(&logic->numArrayCopyForPresort[j], &logic->numArrayCopyForPresort[j + 1]);
                        logic->totalMoves++;
                    }
                }
            }

            printf("First precalculated array pass completed size: %d\n", logic->totalMoves);

            // Allocate the size of all states AND changes at once to logic->history
            logic->history = malloc(logic->totalMoves * (sizeof(c_State) + sizeof(st_Change)));

            c_State first_state;
            new_c_State(&first_state, 1);

            st_Change noChange;
            new_st_Change(&noChange, 0, 0);

            first_state.changeLog[0] = noChange;

            // Create first state
            memcpy(&logic->history[0], &first_state, sizeof(first_state));

            for (int i = 0; i < settings->batchSize - 1; i++)
            {
                // Last i elements are already in place
                for (int j = 0; j < settings->batchSize - i - 1; j++)
                {
                    if (logic->numArray[j] > logic->numArray[j + 1])
                    {
                        swapNumbers(&logic->numArray[j], &logic->numArray[j + 1]);

                        st_Change newChange;
                        new_st_Change(&newChange, j, j + 1);

                        c_State newState;
                        new_c_State(&logic->history[++logic->historySize], 1);

                        memcpy(&logic->history[logic->historySize].changeLog[0], &newChange, sizeof(newChange));
                    }
                }
            }

            printf("Finished presorting preset Bubble sort.\n");
            return;
        }

        case 1:      // Selection sort
            {
                int min_idx;

                // One by one move boundary of unsorted subarray
                for (int i = 0; i < settings->batchSize - 1; i++)
                {
                    // Find the minimum element in unsorted array
                    min_idx = i;
                    for (int j = i + 1; j < settings->batchSize; j++)
                        if (logic->numArrayCopyForPresort[j] < logic->numArrayCopyForPresort[min_idx])
                            min_idx = j;

                    // Swap the found minimum element with the first element
                    if (min_idx != i)
                    {
                        swapNumbers(&logic->numArrayCopyForPresort[min_idx], &logic->numArrayCopyForPresort[i]);
                        logic->totalMoves++;
                    }
                }

                printf("First precalculated array pass completed size: %d\n", logic->totalMoves);

                // Allocate the size of all states AND changes at once to logic->history
                logic->history = malloc(logic->totalMoves * (sizeof(c_State) + sizeof(st_Change)));

                c_State first_state;
                new_c_State(&first_state, 1);

                st_Change noChange;
                new_st_Change(&noChange, 0, 0);

                first_state.changeLog[0] = noChange;

                // Create first state
                memcpy(&logic->history[0], &first_state, sizeof(first_state));

                for (int i = 0; i < settings->batchSize - 1; i++)
                {
                    // Find the minimum element in unsorted array
                    min_idx = i;
                    for (int j = i + 1; j < settings->batchSize; j++)
                        if (logic->numArray[j] < logic->numArray[min_idx])
                            min_idx = j;

                    // Swap the found minimum element with the first element
                    if (min_idx != i)
                    {
                        swapNumbers(&logic->numArray[min_idx], &logic->numArray[i]);

                        st_Change newChange;
                        new_st_Change(&newChange, min_idx, i);

                        c_State newState;
                        new_c_State(&logic->history[++logic->historySize], 1);

                        memcpy(&logic->history[logic->historySize].changeLog[0], &newChange, sizeof(newChange));
                    }
                }

                printf("Finished presorting preset Selection sort.\n");
                return;
            }

        /// FIXME (Me#1#01/24/23): FIX COCKTAIL SORT
        case 2:
            {
                char swapped = 1;
                int start = 0;
                int arr_end = settings->batchSize - 1;

                // First pass to assess moves.
                while (swapped == 1) {
                    swapped = 0;

                    for (int i = start; i < arr_end; ++i) {
                        if (logic->numArrayCopyForPresort[i] > logic->numArrayCopyForPresort[i + 1]) {
                            swapNumbers(&logic->numArrayCopyForPresort[i], &logic->numArrayCopyForPresort[i + 1]);
                            logic->totalMoves++;
                            swapped = 1;
                        }
                    }

                    if (swapped == 0)
                        break;

                    swapped = 0;

                    arr_end--;
                    for (int i = arr_end - 1; i >= start; --i)
                    {
                        if (logic->numArrayCopyForPresort[i] > logic->numArrayCopyForPresort[i + 1])
                        {
                            swapNumbers(&logic->numArrayCopyForPresort[i], &logic->numArrayCopyForPresort[i + 1]);
                            logic->totalMoves++;
                            swapped = 1;
                        }
                    }

                    start++;
                }

                printf("First precalculated array pass completed size: %d\n", logic->totalMoves);

                // Allocate the size of all states AND changes at once to logic->history
                logic->history = malloc(logic->totalMoves * (sizeof(c_State) + sizeof(st_Change)));

                c_State first_state;
                new_c_State(&first_state, 1);

                st_Change noChange;
                new_st_Change(&noChange, 0, 0);

                first_state.changeLog[0] = noChange;

                // Create first state
                memcpy(&logic->history[0], &first_state, sizeof(first_state));

                // Second pass to make states
                start = 0;
                swapped = 1;
                arr_end = settings->batchSize - 1;

                while (swapped == 0) {
                    swapped = 0;

                    for (int i = start; i < arr_end; ++i) {
                        if (logic->numArray[i] > logic->numArray[i + 1]) {
                            swapNumbers(&logic->numArray[i], &logic->numArray[i + 1]);

                            st_Change newChange;
                            new_st_Change(&newChange, i, i + 1);

                            c_State newState;
                            new_c_State(&logic->history[++logic->historySize], 1);

                            memcpy(&logic->history[logic->historySize].changeLog[0], &newChange, sizeof(newChange));

                            swapped = 1;
                        }
                    }

                    if (swapped ==  0)
                        break;

                    swapped = 1;

                    arr_end--;
                    for (int i = arr_end - 1; i >= start; --i)
                    {
                        if (logic->numArray[i] > logic->numArray[i + 1])
                        {
                            swapNumbers(&logic->numArray[i], &logic->numArray[i + 1]);

                            st_Change newChange;
                            new_st_Change(&newChange, i, i + 1);

                            c_State newState;
                            new_c_State(&logic->history[++logic->historySize], 1);

                            memcpy(&logic->history[logic->historySize].changeLog[0], &newChange, sizeof(newChange));

                            swapped = 1;
                        }
                    }

                    start++;
                }

                printf("Finished presorting preset Cocktail sort.\n");
                return;
            }
        case 3:         // Gnome sort
            {       // First sort
                int index = 0;

                while (index < settings->batchSize)
                {
                    if (index == 0)
                        index++;

                    if (logic->numArrayCopyForPresort[index] >= logic->numArrayCopyForPresort[index - 1])
                    {
                        index++;
                    }
                    else
                    {
                        swapNumbers(&logic->numArrayCopyForPresort[index], &logic->numArrayCopyForPresort[index - 1]);
                        logic->totalMoves++;
                        index--;
                    }
                }

                printf("First precalculated array pass completed size: %d\n", logic->totalMoves);

                // Allocate the size of all states AND changes at once to logic->history
                logic->history = malloc(logic->totalMoves * (sizeof(c_State) + sizeof(st_Change)));

                c_State first_state;
                new_c_State(&first_state, 1);

                st_Change noChange;
                new_st_Change(&noChange, 0, 0);

                first_state.changeLog[0] = noChange;

                // Create first state
                memcpy(&logic->history[0], &first_state, sizeof(first_state));

                index = 0;

                while (index < settings->batchSize)
                {
                    if (index == 0)
                        index++;

                    if (logic->numArray[index] >= logic->numArray[index - 1])
                    {
                        index++;
                    }
                    else
                    {
                        swapNumbers(&logic->numArray[index], &logic->numArray[index - 1]);

                        st_Change newChange;
                        new_st_Change(&newChange, index, index - 1);

                        c_State newState;
                        new_c_State(&logic->history[++logic->historySize], 1);

                        memcpy(&logic->history[logic->historySize].changeLog[0], &newChange, sizeof(newChange));
                        index--;
                    }
                }

                printf("Finished presorting preset Gnome sort.\n");
                return;
            }
    }
}


void sortAnimation(Logic *logic, Settings *settings)
{
    logic->sortAnimationStep = 1;

    logic->savedMode = logic->mode;
    logic->savedMsDelay = logic->msDelay;
    logic->msDelay = 5;
    logic->mode = 0;

    logic->visualRepRandomPresortSize = 0;

    g_Rectangle *temp_sort = malloc(settings->batchSize * sizeof(g_Rectangle));
    for (int i = 0; i < settings->batchSize; i++)
    {
        logic->randomSortArray[i] = -1;

        new_g_Rectangle(&temp_sort[i]);

        int x_coord = i;
        int y_coord = 0;

        int coord_arr[] = {
                     settings->width/settings->batchSize * (x_coord + 1),
                     0,
                     settings->width/settings->batchSize * x_coord ,
                     0,
                     settings->width/settings->batchSize * x_coord,
                     y_coord,
                     settings->width/settings->batchSize * (x_coord + 1),
                     y_coord
        };

        temp_sort[i].shape.m_setCoords(&temp_sort[i], coord_arr, sizeof(coord_arr) / sizeof(coord_arr[0]));
    }

    memcpy(&logic->visualRepRandomPresort, &temp_sort, sizeof(temp_sort));

    printf("Sort animation started.\n");
}

void randomSortAnimationForward(Logic *logic, Settings *settings)
{
    if (logic->visualRepRandomPresortSize + 1 == settings->batchSize)
    {
        logic->sortAnimationStep = 0;
        logic->visualRepRandomPresortSize = 0;

        for (int i = 0; i < settings->batchSize; i++)
            logic->randomSortArray[i] = -1;

        logic->msDelay = logic->savedMsDelay;
        logic->mode = logic->savedMode;

        logic->savedMsDelay = -1;
        logic->savedMode = -1;

        printf("Sort animation finished.\n");
        return;
    }

    if (logic->mode == 0 && !(logic->msDelayCount <= 0))
        return;

    for (int i = 0; i < settings->randSortMultiplier; i++)
    {
        if (logic->visualRepRandomPresortSize + 1 == settings->batchSize)
            return;

        int randomNum = randInt(0, settings->batchSize - 1);
        while(indexOf(logic->randomSortArray, settings->batchSize, randomNum) != -1)
        {
            randomNum = randInt(0, settings->batchSize - 1);
        }

        logic->randomSortArray[++logic->visualRepRandomPresortSize] = randomNum;

        logic->visualRepRandomPresort[randomNum].shape.m_setCoords(
            &logic->visualRepRandomPresort[randomNum],
            logic->visualRepRectangle[randomNum].m_coords,
            sizeof(logic->visualRepRectangle[randomNum].m_coords) / sizeof(logic->visualRepRectangle[randomNum].m_coords[0]));

         logic->visualRepRandomPresort[randomNum].color = 2;
    }

    if (logic->mode == 0 && logic->msDelayCount < logic->msDelay)
        logic->msDelayCount = logic->msDelay;
}


void randomSort(Logic *logic, Settings *settings)
{
     for (int i = 0; i < settings->batchSize; i++)
    {
        logic->numArray[i] = -1;
        logic->numArrayCopyForPresort[i] = -1;
        logic->walkableArray[i] = -1;
    }

    // Create the necessary objects to perform the sim
    switch (logic->simVisType)
    {
    case 0: // Draw vertical lines close together
        {
            g_Rectangle *vis_rep_rect_arr = malloc(settings->batchSize * sizeof(g_Rectangle));

            int currentNumber = randInt(0, settings->batchSize);
            for (int i = 0; i < settings->batchSize; i++)
            {
                new_g_Rectangle(&vis_rep_rect_arr[i]);

                if (settings->uniqueValues || settings->batchSize > settings->height)
                    while(indexOf(logic->numArray, settings->batchSize, currentNumber) != -1)
                    {
                        currentNumber = randInt(0, settings->batchSize);
                    }
                else
                    currentNumber = randInt(0, settings->batchSize);

                logic->numArray[i] = currentNumber;
                logic->numArrayCopyForPresort[i] = currentNumber;
                logic->walkableArray[i] = currentNumber;

                // Set rectangle coordinates according to their index on the list as well as their value
                // X will be tied to their list position, Y will be tied to their value.
                int x_coord = indexOf(logic->numArray, settings->batchSize,  logic->numArray[i]);
                int y_coord = settings->height/settings->batchSize * (logic->numArray[i] + 1);

                int coord_arr[] = {
                             settings->width/settings->batchSize * (x_coord + 1),                  // X_BOTTOM_RIGHT
                             0,                                                                                                             // Y_BOTTOM_RIGHT
                             settings->width/settings->batchSize * x_coord ,                          // X_BOTTOM_LEFT
                             0,                                                                                                             // Y_BOTTOM_LEFT
                             settings->width/settings->batchSize * x_coord,                           // X_TOP_LEFT
                             y_coord,                                                                                                 // Y_TOP_LEFT
                             settings->width/settings->batchSize * (x_coord + 1),                 // X_TOP_RIGHT
                             y_coord                                                                                                  // Y_TOP_RIGHT
                };

                vis_rep_rect_arr[i].shape.m_setCoords(&vis_rep_rect_arr[i], coord_arr, sizeof(coord_arr) / sizeof(coord_arr[0]));

                printf("Generated number/drawable %d\n", i + 1);
            }

            // Copy over to the struct and delete the original
            memcpy(&logic->visualRepRectangle, &vis_rep_rect_arr, sizeof(vis_rep_rect_arr));

            printf("List has been filled.\n");
            break;
        }
    }
}


// Constructor
int setLogic(Logic *logic, Settings *settings)
{
    printf("Starting up logic.\n");
    logic->mode = settings->mode;
    logic->sortType = settings->sortType;
    logic->msDelay = settings->msDelay;
    logic->simVisType = settings->simVisType;
    logic->showSorting = settings->showSorting;
    printf("Settings applied to logic.\n");

    // By default
    logic->numArray = malloc(settings->batchSize * sizeof(int));
    logic->numArrayCopyForPresort = malloc(settings->batchSize * sizeof(int));
    logic->walkableArray = malloc(settings->batchSize * sizeof(int));
    logic->randomSortArray = malloc(settings->batchSize * sizeof(int));

    logic->simStep = 0;
    logic->simSection = 0;
    logic->totalMoves = 0;
    logic->currentMove = 0;
    logic->historySize = 0;
    logic->indexesAffected = 0;
    logic->finishAnimationStep = -1;

    logic->msDelayCount = logic->msDelay;

    printf("Logic created.\n");
    return SUCCESS;
}
