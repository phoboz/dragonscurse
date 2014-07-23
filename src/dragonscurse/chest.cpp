#include <stdio.h>
#include "world.h"
#include "world_db.h"
#include "chest.h"

Chest::Chest(const char *fn, MediaDB *media, int x, int y)
    : Object(TypeChest, x, y)
{
    load(fn, media);
}

void Chest::world_initialize(World *world)
{
    WorldDB *db = world->get_db();
    int chest_id = get_attribute("chest_id");
    if (chest_id) {
        ChestInfo info;
        if (db->get_chest_info(&info, chest_id, world->get_filename())) {
            printf("Chest %d has %d object(s) (once = %d), (user = %d):\n",
                    info.key, info.num_objects, info.once, info.user);
            for (int i = 0; i < info.num_objects; i++) {
                printf("\t#%d:\tKey: %d", i, info.objects[i].key);
                if (info.objects[i].object_type == Object::TypeItem) {
                    printf("\tItem: %s\n", info.objects[i].data.item.name);
                }
                else {
                    printf("\tType: %d\n", info.objects[i].object_type);
                }
            }
        }
    }
}

