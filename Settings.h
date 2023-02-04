#define STRICT

#ifndef DEFAULTSETTINGS_H_INCLUDED
#define DEFAULTSETTINGS_H_INCLUDED

#include <windows.h>


typedef struct {
    /// Sorting options
    int height;
    int width;
    long int batchSize;
    int uniqueValues;

    /// Visual options
    int mode;
    int sortType;
    int msDelay;
    int simVisType;
    int showSorting;
    int moveMultiplier;
    int randSortMultiplier;
} Settings;


void getSettings(Settings *settings);
void applyDefaultSettings(Settings *settings);


#endif // DEFAULTSETTINGS_H_INCLUDED
