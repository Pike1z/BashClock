/* Made by Charlie Ringler */

/* ----- Includes ----- */
#include "screenManip.h"
#include <time.h>

/* ----- Function Definitions ----- */
void handle_sigch();
void handle_sigint();
void getTime();
int timeChanged();

/* ----- Global Variables ----- */
time_t current_time;
int past_hour, past_minute;
struct tm * timeinfo;
int RUNNING;
int SCREENCHANGE;
char time_str[6];
Screen *screen;

/* ----- Main Function ----- */
int main() {
        /* Variable Declaration */
        int i;
        screen = screenInit();
        PMap letter = initPMap();
        Coord pos = {0, 0};
        char c = ':';

        RUNNING = 1;
        if (screen) {
            /* Initialize Global Variables */   
            updateDimensions();
            getDimensions(screen);
            SCREENCHANGE = 0;

            signal(SIGWINCH, handle_sigch);
            signal(SIGINT, handle_sigint);

            /* Get time */
            printf("\033[?25l");
            getTime();
            printTime(time_str, screen, &letter);
            while (RUNNING) {
                if (timeChanged() || SCREENCHANGE) {
                    getTime();
                    printTime(time_str, screen, &letter);
                    SCREENCHANGE = 0;
                }
            }
        }

        /* Return the screen to normal */
        printf("\033[1H");
        printf("\033[?25h");
        printf("\033[2J");

        /* Free allocated memory */
        destroyPMap(letter);
        destroyScreen(screen);

        return 0;
}

/* ----- Function Definitions ----- */

/* Function that will update the screen dimensions */
void handle_sigch() {
        updateDimensions();
        getDimensions(screen);
        SCREENCHANGE = 1;
}

/* On <ctrl><c> tell the program to shut down */
void handle_sigint() {
        RUNNING = 0;
}

/* Gets the current hour and minute, changes time_str global variable */
void getTime() {
        int hour, minute;

        time(&current_time);
        timeinfo = localtime(&current_time);

        hour = timeinfo->tm_hour;
        if (hour > 12) hour -= 12;
        else if (hour == 0) hour = 12;

        minute = timeinfo->tm_min;

        /* Change global past time to allow for time change check */
        past_hour = hour;
        past_minute = minute;

        /* Fill in time string */
        time_str[0] = hour / 10 + '0';
        time_str[1] = hour % 10 + '0';
        time_str[2] = ':';
        time_str[3] = minute / 10 + '0';
        time_str[4] = minute % 10 + '0';
}

/* Checks if the time has changed, returns true if it has */
int timeChanged() {
        int hour, minute;

        time(&current_time);
        timeinfo = localtime(&current_time);

        hour = timeinfo->tm_hour;
        if (hour > 12) hour -= 12;
        else if (hour == 0) hour = 12;

        minute = timeinfo->tm_min;

        return !(past_hour == hour && past_minute == minute);
}
