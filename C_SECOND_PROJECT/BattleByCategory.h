#ifndef BATTLEBYCATEGORY_H_
#define BATTLEBYCATEGORY_H_

#include "Defs.h"

typedef struct battle_s *Battle;

Battle createBattleByCategory(int capacity, int numberOfCategories, char *categories, equalFunction equalElement,
                              copyFunction copyElement, freeFunction freeElement, getCategoryFunction getCategory,
                              getAttackFunction getAttack, printFunction printElement);

status destroyBattleByCategory(Battle b);

status insertObject(Battle b, element elem);

void displayObjectsByCategories(Battle b);

element removeMaxByCategory(Battle b, char *category);

int getNumberOfObjectsInCategory(Battle b, char *category);

element fight(Battle b, element elem);


#endif /* BATTLEBYCATEGORY_H_ */