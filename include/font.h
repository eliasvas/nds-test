#ifndef FONT_H
#define FONT_H
#include <nds.h>
#include <gl2d.h>

struct Font {
  glImage font_glyphs[(256/16) * (256/16)];
  void fill_font_tc(unsigned int *tc);
  void load();
  void print(const char *text, int posx, int posy);
  void print_centered(const char *text, int posx, int posy);
};

#endif
