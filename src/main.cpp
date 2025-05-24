#include "core_engine.h"
#include "game_manager.h"

// asset generated headers (grit)
#include <starField.h>
#include <planet.h>
#include <splash.h>
#include <moon.h>
/*
  For gameplay, we need a StateMachine for all different 'scenes'
  - OnEnter we need to instanciate all the Entity's (struct MyEntity : public Entity)
  - communication should be done through an EventManager (Observer pattern).
*/
extern glImage Shuttle[1];

GameManager gm;

int main(void) {
  CoreEngine::init();
  gm.init();
	while(true) {
    CoreEngine::update();

    glBegin2D();
      gm.updateAll();
    glEnd2D();
	}

  // These aren't really needed, just exit(1);
  gm.deinit();
  CoreEngine::deinit();
	return 0;
}
