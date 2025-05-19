#include <nds.h>
#include <stdio.h>
#include <math.h>

//#define TOOLS_DEFINE_NUMERIC_LIMITS
#define TOOLS_DEFINE_HASHING
#define TOOLS_DEFINE_DYN_ARRAY
#include "tools.h"

// asset generated headers (grit)
#include <starField.h>
#include <planet.h>
#include <splash.h>

#include <nds.h>

void init_video() {
  vramSetPrimaryBanks(VRAM_A_MAIN_BG_0x06000000, VRAM_B_MAIN_BG_0x06020000, VRAM_C_SUB_BG_0x06200000, VRAM_D_LCD);
  videoSetMode(MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
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

  render_starfield();
  render_planet();
  render_splash_screen();

  for (;;) {
    //u32 ticks = cpuGetTiming();
    //REG_BG3PA_SUB = 1<<8 * (int)(ticks / 60.0); 
  }

  return 0;
}
