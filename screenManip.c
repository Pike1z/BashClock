/* Charlie Ringler */

/* ----- Includes ----- */
#include "screenManip.h"
#include <string.h>

/* ----- Function Declarations ----- */
/* Initializes the Screen struct */
Screen* screenInit() {
        Screen* screen;
        screen = malloc(sizeof(screen));
        return screen;
}

/* Frees the Screen struct */
void destroyScreen(Screen *screen) {
        free(screen);
}

/* Calls a script that updates the dimensions of the screen */
void updateDimensions() {
        system("bash screen.sh");
}

/* Grabs the dimensions of the screen from the dimensions file */
void getDimensions(Screen* screen) {
        FILE *fp;
	char path[1035];
	int width = -1, height = -1;

        /* Run commands to get screen dimensions and capture output */
        fp = popen("/bin/tput lines && /bin/tput cols", "r");
        if (fp == NULL) {
            printf("ERROR: failed to determine screen dimensions\n");
            exit(1);
        }

        /* Read screen height */
        if(fgets(path, sizeof(path), fp) != NULL) {
            height = atoi(path);
            screen->S_HEIGHT = height;
        } else {
            printf("ERROR: lines could not be fetched\n");
            exit(1);
        }

        /* Read screen width */
        if(fgets(path, sizeof(path), fp) != NULL) {
            width = atoi(path);
            screen->S_WIDTH = width;
        } else {
            printf("ERROR: columns could not be fetched\n");
            exit(1);
        }
        
        /* Close */
       	pclose(fp);
}

/* Prints spaces that look like a void background */
void printVoid() {
        int i;
        for (i = 0; i < PIXEL_WIDTH; i++)
            printf(" ");
}

/* Prints two spaces that have a background color */
void printPixel() {
        int i;
        for (i = 0; i < PIXEL_WIDTH; i++)
            printf("\033[48;5;%dm \033[m", P_COLOR);
}

/* Initializes the PMap struct */
PMap initPMap() {
        PMap p = malloc(sizeof(int) * (PMap_WIDTH * PMap_HEIGHT));  
        return p;
}

/* Frees the PMap struct */
void destroyPMap(PMap p) {
        free(p);
}

/* Formats the PMap into a visible character */
void formatPMap(PMap *p, char letter) {
        int i, j;
        /*char template[PMap_WIDTH * PMap_HEIGHT + 1];*/
        char *template = (char *)malloc(PMap_WIDTH * PMap_HEIGHT + 1);

        /* Get charcter number */
        switch ((int)letter - 48) {
            case 0:
                strcpy(template, L_0);
                break;
            case 1:
                strcpy(template, L_1);
                break;
            case 2:
                strcpy(template, L_2);
                break;
            case 3:
                strcpy(template, L_3);
                break;
            case 4:
                strcpy(template, L_4);
                break;
            case 5:
                strcpy(template, L_5);
                break;
            case 6:
                strcpy(template, L_6);
                break;
            case 7:
                strcpy(template, L_7);
                break;
            case 8:
                strcpy(template, L_8);
                break;
            case 9:
                strcpy(template, L_9);
                break;
            default:
                if (letter == ':')
                    strcpy(template, L_C);
                else
                    strcpy(template, L_N);
                break;
        }

        /* Format PMap */
        for (j = 0; j < PMap_HEIGHT; j++) {
            for (i = 0; i < PMap_WIDTH; i++)
                (*p)[PMap_WIDTH * j + i] = (int)(template[PMap_WIDTH * j + i]) - 32;
        }

        free(template);
}

/* Prints the PMap to the screen, showing a graphical number */
void printPMap(Coord *coord, PMap p) {
        int i, j;
        for (i = 0; i < PMap_HEIGHT; i++) {
            for (j = 0; j < PMap_WIDTH; j++) {
                if (p[PMap_WIDTH * i + j] == 0) printVoid();
                else printPixel();
            }
            coord->y++;
            moveCursor(coord);
        }   
}

/* Takes the time string and prints every character as a graphic */
void printTime (char *time_str, Screen *screen, PMap *p) {
        int i, y, total_width;
        char c;
        Coord pos = {0, 0};
        total_width = 5 * (PIXEL_WIDTH * PMap_WIDTH) + 4 * PIXEL_WIDTH;
        pos.x = (screen->S_WIDTH - total_width) / 2;
        y = ( screen->S_HEIGHT - PMap_HEIGHT ) / 2;
    
        pos.y = y;
    
        /* Clear the screen */
        printf("\033[2J");
    
    
        i = 0;
        while (time_str[i]) {
            moveCursor(&pos);
            formatPMap(p, time_str[i]);          
            printPMap(&pos, *p);
            pos.x += PIXEL_WIDTH * (PMap_WIDTH + 1); 
            pos.y = y;
            i++;
        }

    /* Put cursor at bottom of screen */
    printf("\n"); 
}

/* Moves the cursor to a specific position */
void moveCursor(Coord *coord) {
        /* Moves the cursor to (x, y) */
        printf("\033[%d;%dH", coord->y, coord->x);
}
