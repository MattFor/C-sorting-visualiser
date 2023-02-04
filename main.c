#define STRICT

#include "Window.h"
#include "Logic.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    /**
        Start of the program
    **/

    /// Create window, settings and logic
    Window window;
    Logic logic;

    /// Create the OpenGL window and retrieve and cache settings from the config.ini file
    if (!initWindow(&window, hInstance, hPrevInstance, lpCmdLine, nCmdShow))
    {
        printf("[CRITICAL ERROR] Window cannot launch!\n");
        return CRITICAL_ERROR;
    }

    /// Initiate sorting logic
    if (setLogic(&logic, &window.settings) != 0)
        return CRITICAL_ERROR;

    randomSort(&logic, &window.settings);
    printf("Sorted.\n");

    mapSort(&logic, &window.settings);

    if (logic.showSorting == 1)
        sortAnimation(&logic, &window.settings);


    /**
        Main loop
    **/

    while (!window.bQuit)
    {
        // Check for messages
        if (PeekMessage(&window.msg, NULL, 0, 0, PM_REMOVE))
        {
                        // Handle or dispatch messages
            switch (window.msg.message)
            {
            case WM_QUIT:
                {
                    printf("CLOSING....\n");
                    window.bQuit = true;
                    break;
                }
            case WM_KEYDOWN:
                {
                    window.keyDown = window.msg.wParam;
                    break;
                }
            case WM_KEYUP:
                {
                    window.keyUp = window.msg.wParam;
                    break;
                }
            default:
                {
                    TranslateMessage(&window.msg);
                    DispatchMessage(&window.msg);
                }
            }
        }
        else
        {
            logic.msDelayCount--;

            if (logic.sortAnimationStep == 1)
            {
                randomSortAnimationForward(&logic, &window.settings);

                for (int i = 0; i < window.settings.batchSize; i++)
                {
                    logic.visualRepRandomPresort[i].shape.m_draw(&logic.visualRepRandomPresort[i]);
                }

                goto RENDER;
            }

            for (int i = 0; i < window.settings.batchSize; i++)
            {
                logic.visualRepRectangle[i].shape.m_draw(&logic.visualRepRectangle[i]);
            }

            /// Special event, reset simulation
            if (window.keyDown == 'z' || window.keyDown == 'Z')
            {
                printf("Starting sorting animation.");

                logic.simStep = 0;
                logic.simSection = 0;
                logic.totalMoves = 0;
                logic.currentMove = 0;
                logic.historySize = 0;
                logic.indexesAffected = 0;

                free(logic.history);
                free(logic.visualRepRectangle);
                free(logic.numArray);
                free(logic.numArrayCopyForPresort);
                free(logic.walkableArray);
                free(logic.randomSortArray);

                // Refresh settings
                getSettings(&window.settings);
                applyDefaultSettings(&window.settings);

                // Reset logic
                setLogic(&logic, &window.settings);
                randomSort(&logic, &window.settings);

                mapSort(&logic, &window.settings);
                sortAnimation(&logic, &window.settings);

                window.keyUp = 0;
                window.keyDown = 0;

                continue;
            }

            // If the keyboard was hit and it's not auto mode
            if (logic.mode != 0)
            {
                // printf("%c %c %d\n", window.keyUp, window.keyDown, window.keyDown == window.keyDown);

                if (window.keyDown == window.keyUp || (logic.mode == 2 && window.keyDown == window.keyDown))
                    {
                        if (logic.mode == 2)
                        {
                             window.keyUp = 0;
                             window.keyDown = 0;
                        }

                        switch (window.keyDown)
                        {
                        case 'W':
                        case 'w':
                            {
                                if (logic.mode + 1 > 2)
                                {
                                    printf("Cannot change mode.\n");
                                    break;
                                }

                                printf("Switching to mode %d.\n",  ++logic.mode);
                                break;
                            }
                        case 'S':
                        case 's':
                            {
                                if (logic.mode - 1 < 0)
                                {
                                    printf("Cannot change mode.\n");
                                    break;
                                }

                                printf("Switching to mode %d.\n",  --logic.mode);
                                break;
                            }
                        case 'A':
                        case 'a':
                            {
                                if (stepBackward(&logic, &window.settings) == 3)
                                {
                                    window.keyUp = 0;
                                    break;
                                }

                                window.keyDown = 0;
                                break;
                            }
                        case 'D':
                        case 'd':
                            {
                                if (stepForward(&logic, &window.settings) == 3)
                                {
                                    window.keyUp = 0;
                                    break;
                                }

                                window.keyDown = 0;
                                break;
                            }
                        }
                    } else
                        window.keyUp = window.keyDown;
            }
            else
            {
                if ((logic.savedMode == 1 || logic.savedMode == 2) && logic.finishAnimationStep >= 0)
                {
                    switch (window.keyDown)
                    {
                        case 'D':
                        case 'd':
                            {
                                stepForward(&logic, &window.settings);
                                break;
                            }
                        case 'A':
                        case 'a':
                            {
                                stepBackward(&logic, &window.settings);
                                break;
                            }
                    }
                } else
                        stepForward(&logic, &window.settings);

            }

            RENDER:

            glFinish();
            glFlush();
            glPopMatrix();
            SwapBuffers(window.hDC);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    }


    /**
        Free memory and end the process
    **/

    // Shutdown OpenGL
    DisableOpenGL(window.hwnd, window.hDC, window.hRC);

    // Destroy the window explicitly
    DestroyWindow(window.hwnd);

    free(logic.history);
    free(logic.visualRepRectangle);
    free(logic.numArray);
    free(logic.numArrayCopyForPresort);
    free(logic.walkableArray);
    free(logic.randomSortArray);

    return window.msg.wParam;
}
