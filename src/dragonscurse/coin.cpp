#include <stdlib.h>
#include "coin.h"

Coin::Coin(const char *fn, MediaDB *media)
    : Collectable(fn, media)
{
    m_value = 1 + rand () % get_attribute("max_value");
}

