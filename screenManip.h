/* Charlie Ringler */

/* ----- Includes ----- */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* ----- Defines ----- */
#define PMap_WIDTH 4
#define PMap_HEIGHT 7
#define PIXEL_WIDTH 2
#define P_COLOR 7

#define L_C "    " \
            "  1 " \
            "    " \
            "    " \
            "    " \
            "  1 " \
            "    "

#define L_N "    " \
            "    " \
            "    " \
            "    " \
            "    " \
            "    " \
            "    "

#define L_0 "1111" \
            "1  1" \
            "1  1" \
            "1  1" \
            "1  1" \
            "1  1" \
            "1111"

#define L_1 " 11 " \
            "  1 " \
            "  1 " \
            "  1 " \
            "  1 " \
            "  1 " \
            " 111"

#define L_2 "1111" \
            "   1" \
            "   1" \
            "1111" \
            "1   " \
            "1   " \
            "1111"

#define L_3 "1111" \
            "   1" \
            "   1" \
            "1111" \
            "   1" \
            "   1" \
            "1111"

#define L_4 "1  1" \
            "1  1" \
            "1  1" \
            "1111" \
            "   1" \
            "   1" \
            "   1"

#define L_5 "1111" \
            "1   " \
            "1   " \
            "1111" \
            "   1" \
            "   1" \
            "1111"

#define L_6 "1111" \
            "1   " \
            "1   " \
            "1111" \
            "1  1" \
            "1  1" \
            "1111"

#define L_7 "1111" \
            "   1" \
            "   1" \
            "   1" \
            "   1" \
            "   1" \
            "   1"

#define L_8 "1111" \
            "1  1" \
            "1  1" \
            "1111" \
            "1  1" \
            "1  1" \
            "1111"

#define L_9 "1111" \
            "1  1" \
            "1  1" \
            "1111" \
            "   1" \
            "   1" \
            "1111"

/* ----- Type Defines ----- */
typedef struct {
        int S_WIDTH;
        int S_HEIGHT;
} Screen;

typedef struct {
	int x;
	int y;
} Coord;

typedef int* PMap;

/* ----- Function Definitions ----- */
Screen* screenInit();
void destroyScreen(Screen *screen);
void updateDimensions();
void getDimensions(Screen* screen, char *filename);
void printVoid();
void printPixel();

/* ----- Character print ----- */
PMap initPMap();
void destroyPMap(PMap p);
void formatPMap(PMap *p, char letter);
void printPMap(Coord *coord, PMap p);
void printTime(char *time_str, Screen *screen, PMap *p);
void moveCursor(Coord *coord);
