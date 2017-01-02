#include "console.h"
#include <string.h>

/* NewConsole creates and returns a new console component. */
struct Console NewConsole() {
	struct Console c = {
	    .C = {.size = sizeof(struct Console)},
	    .numLines = 0,
	    .scroll = 0,
	    .row = 0,
	    .col = 0,
	};
	return c;
}

/* ConsoleAddLine appends line to the console. */
void ConsoleAddLine(struct Console *console, const char *text) {
	char *l;
	int n;

	if (console == NULL)
		return;

	n = console->numLines;
	l = console->text + console->lines[n];

	strncpy(l, text, CONSOLE_WIDTH / CONSOLE_FONT_WIDTH);
	console->lines[n + 1] = console->lines[n] + strlen(text);
	console->numLines++;

	if (console->row < (CONSOLE_HEIGHT / CONSOLE_FONT_HEIGHT - 1))
		console->row++;
	else
		console->scroll++;
}
