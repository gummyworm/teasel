#include "inventory.h"
#include <string.h>

/* NewInventory creates a new inventory component and returns it. */
struct Inventory NewInventory() {
	struct Inventory i = {.C = {.size = sizeof(struct Inventory)},
	                      .numItems = 0};
	memset(i.items, 0, sizeof(i.items));
	return i;
}

/* InventoryAddItem adds item to i. */
void InventoryAddItem(struct Inventory *i, struct tv_Entity *item) {
	if (i == NULL)
		return;

	if (i->numItems >= COMPONENT_INVENTORY_MAX_ITEMS)
		return;

	i->items[i->numItems] = item;
	i->numItems++;
}

/* InventoryRemoveItem removes item from inv and returns true if
 * the item was successfully dropped. */
bool InventoryRemoveItem(struct Inventory *inv, struct tv_Entity *item) {
	unsigned i;
	bool found;

	found = false;
	for (i = 0; i < inv->numItems; ++i) {
		if (found) {
			inv->items[i - 1] = inv->items[i];
		} else if (inv->items[i] == item) {
			inv->numItems--;
			inv->items[i] = NULL;
			found = true;
		}
	}

	return found;
}
