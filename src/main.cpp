#include "core_engine.h"

// asset generated headers (grit)
#include <starField.h>
#include <planet.h>
#include <splash.h>
#include <orangeShuttle.h>
#include <moon.h>

int main(void) {
  CoreEngine::init();
	while(true) {
    CoreEngine::update();
	}
  CoreEngine::deinit();
	return 0;
}
