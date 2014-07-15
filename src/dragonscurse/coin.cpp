#include <stdlib.h>
#include "coin.h"

Coin::Coin(const char *fn, MediaDB *media, int x, int y)
    : Collectable(fn, media, x, y)
{
    m_value = 1 + rand () % get_attribute("max_value");
}

