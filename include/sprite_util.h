#ifndef SPRITE_UTIL_H
#define SPRITE_UTIL_H
#include <nds.h>

static const int SPRITE_DMA_CHANNEL = 3;

struct SpriteInfo {
    int oamId;
    int width;
    int height;
    int angle;
    SpriteEntry * entry;
};


namespace Sprite {
  namespace oam {
    void update(OAMTable *oam);
    void init(OAMTable *oam);
  };
  void rotate(SpriteRotation *spriteRotation, int angle);
  void setVisibility(SpriteEntry *spriteEntry, bool hidden, bool affine, bool doubleBound);
};

#endif
