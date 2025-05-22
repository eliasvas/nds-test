#ifndef AUDIO_H
#define AUDIO_H

// TODO: learn more about maxmod, seems VERY high quality
#include <maxmod9.h>

// audio generated headers (mmutil + bin2o)
#include "soundbank.h"
#include "soundbank_bin.h"

namespace Audio {
  static inline void init() {
    mmInitDefaultMem((mm_addr)soundbank_bin);
  }
  static inline void play_sfx (u32 sfx_id) {
    mmEffect(sfx_id);
  }
};

#endif
