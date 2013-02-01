#include <stdio.h>
#include <string.h>
#include "phoboz/ctrl.h"
#include "phoboz/dragon.h"

void Dragon::move(Map *map)
{
    Player::check(map);
    Player::move(map);
}

