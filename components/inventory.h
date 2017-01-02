#ifndef INVENTORY_H
#define INVENTORY_H

#include "entity.h"

#define COMPONENT_INVENTORY_MAX_ITEMS 128

struct Inventory {
	TV_COMPONENT
	unsigned numItems;
	struct tv_Entity *items[COMPONENT_INVENTORY_MAX_ITEMS];
};

struct Inventory NewInventory();
void InventoryAddItem(struct Inventory *, struct tv_Entity *);
bool InventoryRemoveItem(struct Inventory *, struct tv_Entity *);

#endif
