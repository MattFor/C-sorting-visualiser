#define STRICT

#include "Settings.h"


void getSettings(Settings *settings)
{
    char * iniPath = "C:\\Programming\\C\\2023\\07_01-sort_visualizer\\config.ini";

    char buffer[100];

    // Window
    GetPrivateProfileString("Window", "width", 0, buffer, 100, iniPath);
    settings->width = atoi(buffer);

    GetPrivateProfileString("Window", "height", 0, buffer, 100, iniPath);
    settings->height = atoi(buffer);

    // Sort
    GetPrivateProfileString("Sort", "size", 0, buffer, 100, iniPath);
    settings->batchSize = (long int)atoi(buffer);

    GetPrivateProfileString("Sort", "type", 0, buffer, 100, iniPath);
    settings->sortType = atoi(buffer);

    GetPrivateProfileString("Sort", "uniqueValues", 0, buffer, 100, iniPath);
    settings->uniqueValues = atoi(buffer);

    // Simulation
    GetPrivateProfileString("Simulation", "mode", 0, buffer, 100, iniPath);
    settings->mode = atoi(buffer);

    GetPrivateProfileString("Simulation", "msDelay", 0, buffer, 100, iniPath);
    settings->msDelay = atoi(buffer);

    GetPrivateProfileString("Simulation", "visualType", 0, buffer, 100, iniPath);
    settings->simVisType = atoi(buffer);

    GetPrivateProfileString("Simulation", "showRandSort", 0, buffer, 100, iniPath);
    settings->showSorting = atoi(buffer);

    GetPrivateProfileString("Simulation", "moveMultiplier", 0, buffer, 100, iniPath);
    settings->moveMultiplier = atoi(buffer);

    GetPrivateProfileString("Simulation", "randSortMultiplier", 0, buffer, 100, iniPath);
    settings->randSortMultiplier = atoi(buffer);

    printf("Settings cached.\n");
}


void applyDefaultSettings(Settings *settings)
{
    if (settings->msDelay == -1)
        switch(settings->sortType)
        {
        case 0:             // Bubble sort
        case 2:             // Cocktail sort
        case 3:             // Gnome sort
            {
                settings->msDelay = 0;
                break;
            }
        case 1:             // Insertion sort
            {
                settings->msDelay = 5;
                break;
            }
        }

    if (settings->showSorting == -1)
        settings->showSorting = 1;

    if (settings->batchSize == -1)
        settings->batchSize = 128;

    if (settings->simVisType == -1)
        settings->simVisType = 1;

    if (settings->sortType == -1)
        settings->sortType = 1;

    if (settings->mode == -1)
        settings->mode = 0;

    if (settings->randSortMultiplier == -1)
        settings->randSortMultiplier == 1;

    if (settings->moveMultiplier == -1)
        settings->moveMultiplier == 1;

    if (settings->uniqueValues == -1)
        settings->uniqueValues = 1;

    printf("Default settings applied.\n");
}
