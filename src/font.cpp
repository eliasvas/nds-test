#include "font.h"

#include <font16.h>
#define FONT_ATLAS_DIM 256
#define FONT_ATLAS_GLYPH_PX_COUNT 16
#define FONT_ATLAS_GLYPHS_PER_LINE (FONT_ATLAS_DIM/FONT_ATLAS_GLYPH_PX_COUNT)
#define FONT_ATLAS_GLYPH_COUNT (FONT_ATLAS_GLYPHS_PER_LINE*FONT_ATLAS_GLYPHS_PER_LINE)

// TODO: maybe we can also have a hidden palette and you can modify it at runtime

void Font::fill_font_tc(unsigned int *tc) {
  for (u32 y = 0; y < FONT_ATLAS_GLYPHS_PER_LINE; ++y) {
    for (u32 x = 0; x < FONT_ATLAS_GLYPHS_PER_LINE; ++x) {
      tc[(x + y*16)*4 + 0] = x*FONT_ATLAS_GLYPH_PX_COUNT;
      tc[(x + y*16)*4 + 1] = y*FONT_ATLAS_GLYPH_PX_COUNT;
      tc[(x + y*16)*4 + 2] = FONT_ATLAS_GLYPH_PX_COUNT;
      tc[(x + y*16)*4 + 3] = FONT_ATLAS_GLYPH_PX_COUNT;
    }
  }
}

void Font::load() {
  unsigned int font_tc[FONT_ATLAS_GLYPH_COUNT * 4] = {};
  Font::fill_font_tc(font_tc);

  //font_16x16_texcoords,
  glLoadSpriteSet( font_glyphs,
    FONT_ATLAS_GLYPH_COUNT,
    font_tc,
    GL_RGB16,
    TEXTURE_SIZE_256,
    TEXTURE_SIZE_256,
    GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
    16,
    (u16*)font16Pal,
    (u8*)font16Bitmap
  );


}

#include "core_engine.h"
void Font::print(const char *text, int posx, int posy) {
      //glBegin2D();
      //glSprite(posx, posy, GL_FLIP_NONE, &font_glyphs[font_char]);
      for (size_t c = 0; c < strlen(text); ++c) {
        u8 glyph = text[c];
        glSprite(posx + c * FONT_ATLAS_GLYPH_PX_COUNT, posy, GL_FLIP_NONE, &font_glyphs[glyph]);
      }
      //glEnd2D();
}
