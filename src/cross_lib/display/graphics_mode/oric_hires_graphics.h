#ifndef _MEMORY_MAPPED_GRAPHICS
#define _MEMORY_MAPPED_GRAPHICS

#include "standard_libs.h"

#define BASE_ADDR 0xA000

extern void _oric_hires_draw(uint8_t x, uint8_t y, uint8_t tile);
extern void _oric_hires_delete(uint8_t x, uint8_t y);


#define _XL_DRAW(x,y,tile,color) \
        _oric_hires_draw(x,y,tile)

#define _XL_DELETE(x,y) \
        _oric_hires_delete(x,y)


#endif // _MEMORY_MAPPED_GRAPHICS



