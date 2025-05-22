#include "core_engine.h"

#include "input.h"
#include "audio.h"

#include "tools.h"
#define TOOLS_DEFINE_HASHING
#define TOOLS_DEFINE_DYN_ARRAY

u32 CoreEngine::frame_idx = 0;

void CoreEngine::init() {
  powerOn(POWER_ALL_2D);
  lcdMainOnBottom();

  videoSetMode( MODE_5_3D );
	consoleDemoInit();
	glScreen2D();

  Audio::init();
}

void CoreEngine::deinit() {

}

void CoreEngine::update() {
  Input::update();


  int red = abs(sinLerp(frame_idx*220)*31) >> 12 ;
  int green = abs(sinLerp(frame_idx*140)*31) >> 12 ;
  int blue = abs(sinLerp(frame_idx*40)*31) >> 12 ;


  touchPosition tp = Input::get_tp();

	glBegin2D();
  glBoxFilled(tp.px-50, tp.py-50, tp.px + 50, tp.py + 50, RGB15(green,blue,red));
	glEnd2D();


  //lines(frame_idx);
  glFlush(0);
  swiWaitForVBlank();
  frame_idx+=1;
}
