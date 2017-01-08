#include "sys_console.h"
#include "app_signals.h"
#include "app_systems.h"
#include "components/app_enum.h"
#include "components/console.h"
#include "components/description.h"
#include "components/inventory.h"
#include "components/room.h"
#include "components/transform.h"
#include "gui.h"
#include "input.h"
#include "system.h"
#include <SDL2/SDL.h> //XXX
#include <stdio.h>
#include <time.h>

/* err prints the error msg to the console. */
#define err(msg, ...)                                                          \
	{                                                                      \
		char buff[128];                                                \
		if (console != NULL) {                                         \
			sprintf(buff, msg, __VA_ARGS__);                       \
			ConsoleAddLine(console, buff);                         \
		}                                                              \
	}

/* msg prints msg to the console. */
#define msg(msg, ...)                                                          \
	{                                                                      \
		char buff[128];                                                \
		if (console != NULL) {                                         \
			sprintf(buff, msg, __VA_ARGS__);                       \
			ConsoleAddLine(console, buff);                         \
		}                                                              \
	}

/* error messages */
#define ERR_UNKNOWN_COMMAND "unknown command: %s"
#define ERR_NUM_ARGS "expected %d argument(s); %d given"
#define ERR_ITEM_NOT_FOUND "I don't have a %s"
#define ERR_ITEM_NOT_VISIBLE "I don't see a %s"
#define ERR_UNKNOWN_DIRECTION "You can't go %s"
#define ERR_NO_EXIT "There is no exit %s"
#define ERR_NO_TARGET "There is no target named %s"

/* info messages */
#define MSG_ITEM_DROPPED "Dropped %s"
#define MSG_ITEM_TAKEN "The %s is in hand"
#define MSG_ATTACK_TARGET "You attack %s"
#define MSG_WIELD "You wield the %s"
#define MSG_WEAR "You don the the %s"

/* command names */
const char CMD_LS[] = "LS";
const char CMD_DROP[] = "RM";
const char CMD_LOOK[] = "LOOK";
const char CMD_TAKE[] = "TAKE";
const char CMD_MOVE[] = "GO";
const char CMD_KILL[] = "KILL";
const char CMD_WIELD[] = "WIELD";
const char CMD_WEAR[] = "WEAR";

const char DIRECTION_NORTH[] = "NORTH";
const char DIRECTION_SOUTH[] = "SOUTH";

static struct Transform *transform;
static struct Console *console;
static struct Room *room;
static struct Inventory *inv;
static time_t tmrstart;

static void err_unknowncommand(char *cmd) { err(ERR_UNKNOWN_COMMAND, cmd); }
static void err_nargs(int expected, int actual) {
	err(ERR_NUM_ARGS, expected, actual);
}
static void err_noitem(char *item) { err(ERR_ITEM_NOT_FOUND, item); }
static void err_unknowntarget(char *target) { err(ERR_NO_TARGET, target); }

void itemdropped(char *item) { err(MSG_ITEM_DROPPED, item); }
void msg_attacktarget(char *target) { msg(MSG_ATTACK_TARGET, target); }
void msg_wield(char *weapon) { msg(MSG_WIELD, weapon); }
void msg_wear(char *item) { msg(MSG_WEAR, item); }

/* getargs parses line, sets all the arguments found, and returns the number. */
static int getargs(char *line, char **args) {
	char *p;
	int count;

	count = 0;
	for (p = strtok(line, " \t"); p != NULL; p = strtok(NULL, " \t")) {
		args[count] = p;
		count++;
	}

	return count;
}

/* look examines target and displays its description if it has one. */
static void look(char *name) {
	struct tv_Entity *e;
	struct Description *d;

	if (console == NULL)
		return;

	e = tv_EntityGet(name);
	if (e == NULL)
		return;

	d = (struct Description *)tv_EntityGetComponent(e,
	                                                COMPONENT_DESCRIPTION);
	if (d == NULL) {
		return;
	}

	if (d->detailed != NULL)
		ConsoleAddLine(console, d->detailed);
}

/* take adds name to the inventory (if it exists can be added). */
static void take(char *name) {
	struct tv_Entity *e;

	if (console == NULL || inv == NULL)
		return;

	e = tv_EntityGet(name);
	if (e == NULL) {
		err(ERR_ITEM_NOT_VISIBLE, name);
		return;
	}

	InventoryAddItem(inv, e);
	e->enabled = false;
	msg(MSG_ITEM_TAKEN, name);
}

/* inventory displays the contents of the inventory in console. */
static void inventory() {
	unsigned i;

	if (console == NULL || inv == NULL)
		return;

	ConsoleAddLine(console, "INVENTORY:");
	for (i = 0; i < inv->numItems; ++i) {
		ConsoleAddLine(console, inv->items[i]->name);
	}
}

/* move moves the player to the exit matching dir. */
static void move(char *dir) {
	if (strcmp(dir, DIRECTION_NORTH) == 0) {
		if ((room != NULL) && (room->exits[ROOM_NORTH] != NULL)) {
			room->exits[ROOM_NORTH]();
		} else {
			err(ERR_NO_EXIT, dir);
		}
	} else if ((strcmp(dir, DIRECTION_SOUTH) == 0)) {
		if ((room != NULL) && (room->exits[ROOM_SOUTH] != NULL)) {
			room->exits[ROOM_SOUTH]();
		} else {
			err(ERR_NO_EXIT, dir);
		}
	} else {
		err(ERR_UNKNOWN_DIRECTION, dir);
	}
}

/* drop removes the item name from the inventory. */
static void drop(char *name) {
	struct Transform *t;
	struct tv_Entity *item;

	if (console == NULL || inv == NULL)
		return;

	item = InventoryGetItem(inv, name);
	if (item == NULL) {
		err_noitem(name);
		return;
	}

	t = (struct Transform *)tv_EntityGetComponent(item,
	                                              COMPONENT_TRANSFORM);
	if (t != NULL) {
		tv_Vector3Add(transform->pos, (tv_Vector3){0, 0, 1}, &t->pos);
		printf("dropped @ (%f, %f, %f)\n", t->pos.x, t->pos.y,
		       t->pos.z);
	}

	InventoryRemoveItem(inv, item);
	item->enabled = true;
	itemdropped(name);
}

/* kill engages target in combat and attempts to vanquish it. */
static void kill(char *target) {
	struct tv_Entity *e;
	e = tv_EntityGet(target);

	if (e == NULL) {
		err_unknowntarget(target);
		return;
	}
	msg_attacktarget(target);
}

/* wield equips weapon. */
static void wield(char *weapon) {
	struct tv_Entity *item;
	if (console == NULL || inv == NULL)
		return;

	item = InventoryGetItem(inv, weapon);
	if (item == NULL) {
		err_noitem(weapon);
		return;
	}

	msg_wield(weapon);
}

/* wear puts on attire. */
static void wear(char *attire) {
	struct tv_Entity *item;
	if (console == NULL || inv == NULL)
		return;

	item = InventoryGetItem(inv, attire);
	if (item == NULL) {
		err_noitem(attire);
		return;
	}

	msg_wear(attire);
}

/* exec executes line as a console command. */
static void exec(char *line) {
	int argc;
	char *argv[CONSOLE_WIDTH];
	char l[256];

	strcpy(l, line);
	argc = getargs(l, argv);

	if (strncmp(argv[0], CMD_LS, sizeof(CMD_LS)) == 0) {
		inventory();
	} else if (strncmp(argv[0], CMD_DROP, sizeof(CMD_DROP)) == 0) {
		if (argc != 2)
			err_nargs(1, argc - 1);
		else
			drop(argv[1]);
	} else if (strncmp(argv[0], CMD_LOOK, sizeof(CMD_LOOK)) == 0) {
		if (argc != 2)
			err_nargs(1, argc - 1);
		else
			look(argv[1]);
	} else if (strncmp(argv[0], CMD_TAKE, sizeof(CMD_TAKE)) == 0) {
		if (argc != 2)
			err_nargs(1, argc - 1);
		else
			take(argv[1]);
	} else if (strncmp(argv[0], CMD_MOVE, sizeof(CMD_MOVE)) == 0) {
		if (argc != 2)
			err_nargs(1, argc - 1);
		else
			move(argv[1]);
	} else if (strncmp(argv[0], CMD_KILL, sizeof(CMD_KILL)) == 0) {
		if (argc != 2)
			err_nargs(1, argc - 1);
		else
			kill(argv[1]);
	} else if (strncmp(argv[0], CMD_WIELD, sizeof(CMD_WIELD)) == 0) {
		if (argc != 2)
			err_nargs(1, argc - 1);
		else
			wield(argv[1]);
	} else if (strncmp(argv[0], CMD_WEAR, sizeof(CMD_WEAR)) == 0) {
		if (argc != 2)
			err_nargs(1, argc - 1);
		else
			wear(argv[1]);
	} else {
		err_unknowncommand(argv[0]);
	}
}

/* button is called when a button is pressed. */
static void button(int button) {
	unsigned c, r, l;
	char ch;

	if (console == NULL)
		return;

	ch = (char)button; // XXX

	c = console->col;
	r = console->row;
	l = console->numLines;

	tmrstart = time(NULL);
	console->blink = true;

	const char *keyname = SDL_GetScancodeName(button);

	switch (button) {
	case SDL_SCANCODE_UP:
		if (console->scroll > 0) {
			console->scroll--;
		}
		break;
	case SDL_SCANCODE_DOWN:
		if (console->scroll <= (console->numLines - CONSOLE_NUM_ROWS)) {
			console->scroll++;
		}
		break;
	case SDL_SCANCODE_RETURN:
		console->lines[l + 1] = console->lines[l] + c;
		console->numLines++;
		console->col = 0;
		if (r < (CONSOLE_NUM_ROWS - 1))
			console->row++;
		else
			console->scroll++;
		if (c > 0)
			exec(console->text + console->lines[l]);
		break;
	case SDL_SCANCODE_BACKSPACE:
		if (c > 0) {
			*(console->text + (console->lines[l] + c) - 1) = '\0';
			console->col--;
		}
		break;
	case SDL_SCANCODE_SPACE:
		keyname = " ";
	default:
		if (strlen(keyname) != 1)
			return;
		ch = keyname[0];
		if (c < (CONSOLE_WIDTH / CONSOLE_FONT_WIDTH)) {
			*(console->text + (console->lines[l] + c)) = ch;
			console->col++;
		}
		break;
	}
}

/* implements returns true if the given entity can be used as a console.
 */
static bool implements(struct tv_Entity *e) {
	return tv_EntityGetComponent(e, COMPONENT_CONSOLE) != NULL;
}

/* start inspects new entities for console-related data. */
static void start(struct tv_Entity *e) {
	struct tv_Component *c;

	if ((c = tv_EntityGetComponent(e, COMPONENT_CONSOLE)) != NULL) {
		console = (struct Console *)c;
		tmrstart = time(NULL);
		console->blinktmr = 0;
	}
	if ((c = tv_EntityGetComponent(e, COMPONENT_INVENTORY)) != NULL) {
		inv = (struct Inventory *)c;
	}
	if ((c = tv_EntityGetComponent(e, COMPONENT_TRANSFORM)) != NULL) {
		transform = (struct Transform *)c;
	}
}

/* globalUpdate updates and draws the console window. */
static void globalUpdate() {
	unsigned i, y, scroll;
	char buff[CONSOLE_WIDTH / CONSOLE_FONT_WIDTH + 2];

	if (console == NULL)
		return;

	console->blinktmr = time(NULL);
	if (difftime(console->blinktmr, tmrstart) > CONSOLE_BLINK_INTERVAL) {
		console->blinktmr -= tmrstart;
		tmrstart = time(NULL);
		console->blink = !console->blink;
	}

	tv_GuiRect(CONSOLE_START_X, CONSOLE_START_Y, CONSOLE_WIDTH,
	           CONSOLE_HEIGHT, CONSOLE_COLOR);

	y = CONSOLE_START_Y;
	scroll = console->scroll;
	for (i = 0; i <= (scroll + console->numLines); ++i) {
		int len, offset;

		if (y > (CONSOLE_START_Y + CONSOLE_HEIGHT))
			break;

		offset = console->lines[i + scroll];
		if (i + scroll == console->numLines)
			len = console->col;
		else
			len = console->lines[i + scroll + 1] - offset;

		memcpy(buff, console->text + offset, len);

		if (console->row == i && console->blink) {
			buff[len] = CONSOLE_CURSOR;
		} else {
			buff[len] = '\0';
		}
		buff[len + 1] = '\0';

		tv_GuiText(CONSOLE_START_X, y, buff, CONSOLE_FONT_WIDTH);
		y += CONSOLE_FONT_HEIGHT;
	}
}

/* InitConsoleSystem initializes the system used to display and interact
 * with
 * the console (text logging, user input, etc.). */
void InitConsoleSystem() {
	struct tv_System sys = {
	    .enabled = true,
	    .Start = start,
	    .Update = NULL,
	    .Implements = implements,
	    .GlobalUpdate = globalUpdate,
	};
	tv_RegisterSystem(&sys, SYSTEM_CONSOLE);
	GCONNECT(SIGGROUP_CONSOLE, ButtonDown, button);
}
