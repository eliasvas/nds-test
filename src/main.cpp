#include <nds.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "sprite_util.h"

//#define TOOLS_DEFINE_NUMERIC_LIMITS
#define TOOLS_DEFINE_HASHING
#define TOOLS_DEFINE_DYN_ARRAY
#include "tools.h"

// asset generated headers (grit)
#include <starField.h>
#include <planet.h>
#include <splash.h>
#include <orangeShuttle.h>
#include <moon.h>

#include <nds.h>

void init_video() {
  vramSetPrimaryBanks(VRAM_A_MAIN_BG_0x06000000, VRAM_B_MAIN_BG_0x06020000, VRAM_C_SUB_BG_0x06200000, VRAM_D_LCD);
  videoSetMode(MODE_5_2D | DISPLAY_BG2_ACTIVE | 
      DISPLAY_BG3_ACTIVE | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D);
  vramSetBankE(VRAM_E_MAIN_SPRITE);
  videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE);
}
void init_backgrounds() {
  REG_BG3CNT = BG_BMP16_256x256 | BG_BMP_BASE(0) | BG_PRIORITY(3);
  REG_BG3PA = 1 << 8;
  REG_BG3PB = 0;
  REG_BG3PC = 0;
  REG_BG3PD = 1 << 8;
  REG_BG3X = 0;
  REG_BG3Y = 0;

  REG_BG2CNT = BG_BMP16_128x128 | BG_BMP_BASE(8) | BG_PRIORITY(2);
  REG_BG2PA = 1 << 8;
  REG_BG2PB = 0;
  REG_BG2PC = 0;
  REG_BG2PD = 1 << 8;
  REG_BG2X = -(SCREEN_WIDTH / 2 - 64) << 8;
  REG_BG2Y = -(SCREEN_HEIGHT / 2 - 64) << 8;

  REG_BG3CNT_SUB = BG_BMP16_256x256 | BG_BMP_BASE(0) | BG_PRIORITY(3); 
  REG_BG3PA_SUB = 1 << 8;
  REG_BG3PB_SUB = 0;
  REG_BG3PC_SUB = 0;
  REG_BG3PD_SUB = 1 << 8;
  REG_BG3X_SUB = 0;
  REG_BG3Y_SUB = 0;
}
void init_sprites(OAMTable *oam, SpriteInfo *spriteInfo) {
  static const int TILE_HALF_WORD_COUNT = 1 * 8 * 8;
  static const int BYTES_PER_16_COLOR_TILE = TILE_HALF_WORD_COUNT / 2;
  static const int COLORS_PER_PALETTE = 16;
  static const int BOUNDARY_VALUE = 32;
  static const int OFFSET_MULTIPLIER = BOUNDARY_VALUE / sizeof(SPRITE_GFX[0]);

  int next_free_tile_idx = 0;

  // Make the ship sprite
  static const int SHUTTLE_OAM_ID = 0;
  assert(SHUTTLE_OAM_ID < SPRITE_COUNT);
  SpriteInfo *shuttleInfo = &spriteInfo[SHUTTLE_OAM_ID];
  SpriteEntry *shuttle = &oam->oamBuffer[SHUTTLE_OAM_ID];
  shuttleInfo->oamId = SHUTTLE_OAM_ID;
  shuttleInfo->width = 64;
  shuttleInfo->height = 64;
  shuttleInfo->angle = 3186;
  shuttleInfo->entry = shuttle;
  shuttle->y = SCREEN_HEIGHT / 2 - shuttleInfo->height;
  shuttle->isRotateScale = true;
  assert(!shuttle->isRotateScale || (shuttleInfo->oamId < MATRIX_COUNT));
  shuttle->isSizeDouble = false;
  shuttle->blendMode = OBJMODE_NORMAL;
  shuttle->isMosaic = false;
  shuttle->colorMode = OBJCOLOR_16;
  shuttle->shape = OBJSHAPE_SQUARE;
  shuttle->x =
      SCREEN_WIDTH / 2 - shuttleInfo->width * 2 + shuttleInfo->width / 2;
  shuttle->rotationIndex = shuttleInfo->oamId;
  shuttle->size = OBJSIZE_64;
  shuttle->gfxIndex = next_free_tile_idx;
  next_free_tile_idx += orangeShuttleTilesLen / BYTES_PER_16_COLOR_TILE;
  shuttle->priority = OBJPRIORITY_0;
  shuttle->palette = shuttleInfo->oamId;

  Sprite::rotate(&oam->matrixBuffer[shuttleInfo->oamId], shuttleInfo->angle);

  dmaCopyHalfWords(SPRITE_DMA_CHANNEL, orangeShuttlePal, &SPRITE_PALETTE[shuttleInfo->oamId * COLORS_PER_PALETTE], orangeShuttlePalLen);
  dmaCopyHalfWords(SPRITE_DMA_CHANNEL, orangeShuttleTiles, &SPRITE_GFX[shuttle->gfxIndex * OFFSET_MULTIPLIER], orangeShuttleTilesLen);


  // Make the moon sprite
  static const int MOON_OAM_ID = 1;
  assert(SHUTTLE_OAM_ID < SPRITE_COUNT);
  SpriteInfo *moonInfo = &spriteInfo[MOON_OAM_ID];
  SpriteEntry *moon = &oam->oamBuffer[MOON_OAM_ID];
  moonInfo->oamId = MOON_OAM_ID;
  moonInfo->width = 32;
  moonInfo->height = 32;
  moonInfo->angle = 3186;
  moonInfo->entry = moon;
  moon->y = 0;
  moon->isRotateScale = false;
  moon->isHidden = false;
  moon->blendMode = OBJMODE_NORMAL;
  moon->isMosaic = false;
  moon->colorMode = OBJCOLOR_16;
  moon->shape = OBJSHAPE_SQUARE;
  moon->x = SCREEN_WIDTH-32;
  moon->hFlip = false;
  moon->vFlip = false;
  moon->size = OBJSIZE_32;
  moon->gfxIndex = next_free_tile_idx;
  next_free_tile_idx += moonTilesLen / BYTES_PER_16_COLOR_TILE;
  moon->priority = OBJPRIORITY_2;
  moon->palette = moonInfo->oamId;

  dmaCopyHalfWords(SPRITE_DMA_CHANNEL, moonPal, &SPRITE_PALETTE[moonInfo->oamId * COLORS_PER_PALETTE], moonPalLen);
  dmaCopyHalfWords(SPRITE_DMA_CHANNEL, moonTiles, &SPRITE_GFX[moon->gfxIndex * OFFSET_MULTIPLIER], moonTilesLen);

}

void render_shuttle(SpriteInfo *shuttleInfo) {
  static const int COLORS_PER_PALETTE = 16;
  static const int BOUNDARY_VALUE = 32;
  static const int OFFSET_MULTIPLIER = BOUNDARY_VALUE / sizeof(SPRITE_GFX[0]);


  dmaCopyHalfWords(SPRITE_DMA_CHANNEL, orangeShuttlePal, &SPRITE_PALETTE[shuttleInfo->oamId * COLORS_PER_PALETTE], orangeShuttlePalLen);
  dmaCopyHalfWords(SPRITE_DMA_CHANNEL, orangeShuttleTiles, &SPRITE_GFX[shuttleInfo->entry->gfxIndex * OFFSET_MULTIPLIER], orangeShuttleTilesLen);

}


static const int DMA_CHANNEL = 3;
void render_starfield() {
  dmaCopyHalfWords(DMA_CHANNEL, starFieldBitmap, (u16*)BG_BMP_RAM(0), starFieldBitmapLen); 
}
void render_planet() {
  dmaCopyHalfWords(DMA_CHANNEL, planetBitmap, (u16*)BG_BMP_RAM(8), planetBitmapLen); 
}
void render_splash_screen() {
  dmaCopyHalfWords(DMA_CHANNEL, splashBitmap, (u16*)BG_BMP_RAM_SUB(0), splashBitmapLen); 
}


int main() {
  powerOn(POWER_ALL_2D);
  lcdMainOnBottom();
  init_video();
  init_backgrounds();

  SpriteInfo spriteInfo[SPRITE_COUNT];
  OAMTable *oam = new OAMTable();
  Sprite::oam::init(oam);
  init_sprites(oam, spriteInfo);

  render_starfield();
  render_planet();
  render_splash_screen();

  swiWaitForVBlank();
  Sprite::oam::update(oam);

  for (;;) {
    swiWaitForVBlank();
    spriteInfo[0].entry->x += 1;
    render_shuttle(&spriteInfo[0]);
    Sprite::oam::update(oam);

    //u32 ticks = cpuGetTiming();
    //REG_BG3PA_SUB = 1<<8 * (int)(ticks / 60.0); 
  }

  return 0;
}
