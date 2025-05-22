#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#include <nds.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "sprite_util.h"
#include "gl2d.h"
//#include "input.h"
//#include "audio.h"
#include "tools.h"


struct CoreEngine {
  static u32 frame_idx;
  // ---------------------
  static void init();
  static void deinit();
  static void update();
};

#endif
