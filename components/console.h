#ifndef CONSOLE_H
#define CONSOLE_H

#include "entity.h"
#include <time.h>

#define CONSOLE_HISTORY_SIZE 10000
#define CONSOLE_MAX_LINES 256
#define CONSOLE_BLINK_INTERVAL 0.10 /* seconds */

enum { CONSOLE_START_X = 0,
       CONSOLE_START_Y = 320,
       CONSOLE_WIDTH = 640 - CONSOLE_START_X,
       CONSOLE_HEIGHT = 480 - CONSOLE_START_Y,
       CONSOLE_COLOR = 0x7f007fff,

       CONSOLE_FONT_WIDTH = 16,
       CONSOLE_FONT_HEIGHT = 16,

       CONSOLE_NUM_ROWS = CONSOLE_HEIGHT / CONSOLE_FONT_HEIGHT,

       CONSOLE_CURSOR = '$',
};

/* Console is a component used to interface with the player, the player's
 * inventory, etc.
 */
struct Console {
	TV_COMPONENT
	unsigned numLines;
	unsigned scroll;
	unsigned row, col;
	time_t blinktmr;
	bool blink;

	int lines[CONSOLE_MAX_LINES];
	char text[CONSOLE_HISTORY_SIZE];
};

struct Console NewConsole();
void ConsoleAddLine(struct Console *, const char *);

#endif
