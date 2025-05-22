#include "core_engine.h"

#define TOOLS_DEFINE_HASHING
#define TOOLS_DEFINE_DYN_ARRAY
#include "tools.h"

// TODO: application should probably just register callbacks for rendering
// top and bottom display

u32 CoreEngine::frame_idx = 0;
touchPosition Input::tp = {};

void initSubSprites(void) {
	oamInit(&oamSub, SpriteMapping_Bmp_2D_256, false);
	int x = 0;
	int y = 0;
	int id = 0;
	for(y = 0; y < 3; y++) {
    for(x = 0; x < 4; x++)
    {
      oamSub.oamMemory[id].attribute[0] = ATTR0_BMP | ATTR0_SQUARE | (64 * y);
      oamSub.oamMemory[id].attribute[1] = ATTR1_SIZE_64 | (64 * x);
      oamSub.oamMemory[id].attribute[2] = ATTR2_ALPHA(1) | (8 * 32 * y) | (8 * x);
      id++;
    }
  }

	swiWaitForVBlank();

	oamUpdate(&oamSub);
}


void CoreEngine::init() {
  videoSetMode(MODE_5_3D);
  videoSetModeSub(MODE_5_2D);

  // init top screen (bg)
  initSubSprites();
	bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

 	glScreen2D();
  Audio::init();
}

void CoreEngine::deinit() {

}

void CoreEngine::swap_screens() {
  // wait for capute unit to be ready?
  while(REG_DISPCAPCNT & DCAP_ENABLE);
  // switch displays every frame (30 FPS)
  // This is so we can do rendering with gl2d (_3D) on both screens
  if(CoreEngine::is_bottom_screen_active()) {
    lcdMainOnBottom();
    vramSetBankC(VRAM_C_LCD);
    vramSetBankD(VRAM_D_SUB_SPRITE);
    REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3);
  }
  else {
    lcdMainOnTop();
    vramSetBankD(VRAM_D_LCD);
    vramSetBankC(VRAM_C_SUB_BG);
    REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3);
  }
}

bool CoreEngine::is_bottom_screen_active() { return ((frame_idx & 1) == 0); }

bool CoreEngine::is_top_screen_active() { return !is_bottom_screen_active(); }

void CoreEngine::update() {
  glFlush(0);
  swiWaitForVBlank();

  frame_idx+=1;

  CoreEngine::swap_screens();
  Input::update();
  // frame starts here I think
}
