#include "core_engine.h"

// asset generated headers (grit)
#include <starField.h>
#include <planet.h>
#include <splash.h>
#include <moon.h>

extern glImage Shuttle[1];

int main(void) {
  CoreEngine::init();
	while(true) {
    CoreEngine::update();

    static touchPosition tp;
    if (CoreEngine::is_bottom_screen_active()) {
      if (Input::key_down(Key::TOUCH)) tp = Input::get_tp();
      int red = 127;
      int green = 0;
      int blue = 0;
      glBegin2D();
      glBoxFilled(tp.px-50, tp.py-50, tp.px + 50, tp.py + 50, RGB15(red,green,blue));
      //glSprite(0, 0, GL_FLIP_NONE,Shuttle);
      glEnd2D();
    } else {
      glBegin2D();
      CoreEngine::default_font.print_centered("Epic Game", SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
      glEnd2D();
    }

    if (Input::key_pressed(Key::TOUCH)) Audio::play_sfx(SFX_HELLO);

	}
  CoreEngine::deinit();
	return 0;
}
