#include <stdio.h>
#include "Tmx/Tmx.h"
#include "Tmx/TmxLayer.h"

void write_word(short value, FILE *fp) {
  fputc((value & 0xff00) >> 8, fp);
  fputc(value & 0x00ff, fp);
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage is: %s <tmxfile> <binfile>\n", argv[0]);
    return 1;
  }

  printf("converting file: %s\n", argv[1]);
  Tmx::Map *map = new Tmx::Map();
  map->ParseFile(argv[1]);

  if (map->HasError()) {
    printf("error code: %d\n", map->GetErrorCode());
    printf("error text: %s\n", map->GetErrorText().c_str());
    return map->GetErrorCode();
  }

  printf("Version: %1.1f\n", map->GetVersion());

  if (map->GetOrientation() != Tmx::TMX_MO_ORTHOGONAL) {
    printf("error: map orientation must be orthogonal\n");
    return 1;
  }

  const Tmx::Layer *layer = map->GetLayer(0);
  if (!layer) {
    printf("error: layer zero does not exist\n");
    return 1;
  }

  FILE *fp = fopen(argv[2], "wb");
  if (fp == NULL) {
    printf("error: unable to create file %s\n", argv[2]);
    return 1;
  }

  short w = (short) layer->GetWidth();
  short h = (short) layer->GetHeight();

  printf("Map size: %dx%d\n", w, h);

  write_word(w, fp);
  write_word(h, fp);

  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      char tile_id = (char) layer->GetTileId(x, y);
      fputc(tile_id, fp);
    }
  }
      

  return 0;
}

