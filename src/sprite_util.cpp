#include "sprite_util.h"

void Sprite::oam::update(OAMTable *oam) {
  DC_FlushAll();
  dmaCopyHalfWords(SPRITE_DMA_CHANNEL, oam->oamBuffer, OAM, SPRITE_COUNT * sizeof(SpriteEntry));
}

void Sprite::oam::init(OAMTable *oam) {
  for (int i = 0; i < SPRITE_COUNT; i++) {
    oam->oamBuffer[i].attribute[0] = ATTR0_DISABLED;
    oam->oamBuffer[i].attribute[1] = 0;
    oam->oamBuffer[i].attribute[2] = 0;
  }
  for (int i = 0; i < MATRIX_COUNT; i++) {
    oam->matrixBuffer[i].hdx = 1 << 8;
    oam->matrixBuffer[i].hdy = 0;
    oam->matrixBuffer[i].vdx = 0;
    oam->matrixBuffer[i].vdy = 1 << 8;
  }
  Sprite::oam::update(oam);
}

void Sprite::rotate(SpriteRotation *spriteRotation, int angle) {
  s16 s = sinLerp(angle) >> 4;
  s16 c = cosLerp(angle) >> 4;

  spriteRotation->hdx = c;
  spriteRotation->hdy = s;
  spriteRotation->vdx = -s;
  spriteRotation->vdy = c;
}

void Sprite::setVisibility(SpriteEntry *spriteEntry, bool hidden, bool affine, bool doubleBound) {
  if (hidden) {
    spriteEntry->isRotateScale = false;
    spriteEntry->isHidden = false;
  } else {
    if (affine) {
      spriteEntry->isRotateScale = true;
      spriteEntry->isSizeDouble = doubleBound;
    } else {
      spriteEntry->isHidden = false;
    }
  }


}

