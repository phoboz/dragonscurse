#include <stdlib.h>
#include "coin.h"

Coin::Coin(const char *fn, MediaDB *media, int x, int y)
    : Collectable(TypeGold, fn, media, x, y)
{
    set_value(1 + rand () % get_attribute("max_value"));
}

