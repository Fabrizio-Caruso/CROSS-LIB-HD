/* --------------------------------------------------------------------------------------- */ 
// 
// CROSS CHASE by Fabrizio Caruso
//
// Fabrizio_Caruso@hotmail.com
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from
// the use of this software.

// Permission is granted to anyone to use this software for non-commercial applications, 
// subject to the following restrictions:

// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software in
// a product, an acknowledgment in the product documentation would be
// appreciated but is not required.

// 2. Altered source versions must be plainly marked as such, and must not
// be misrepresented as being the original software.

// 3. This notice may not be removed or altered from any source distribution.
/* --------------------------------------------------------------------------------------- */ 

#include <conio.h>
#include <peekpoke.h>
#include <atari.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "display_macros.h"

#include "graphics_settings.h"

#include "8x8_chars.h"

#define GRAPHICS_MODE_1 (1+16)

// #include "udg_map.h"	


#if (defined(__COMX__) || defined(__PECOM__) || defined(__MICRO__)) && !defined(NTSC)
    #define NUMBER_OF_LINES 9
#else
    #define NUMBER_OF_LINES 8
#endif

const struct redefine_struct
{
   const uint8_t ascii;
   const uint8_t bitmap[NUMBER_OF_LINES];
} ;



const struct redefine_struct redefine_map[] =
{
	{_TILE_0, _TILE_0_UDG},
	{_TILE_1, _TILE_1_UDG},
	{_TILE_2, _TILE_2_UDG},	
	{_TILE_3, _TILE_3_UDG},
	{_TILE_4, _TILE_4_UDG},
	{_TILE_5, _TILE_5_UDG},
	{_TILE_6, _TILE_6_UDG},
    {_TILE_7, _TILE_7_UDG},
    {_TILE_8, _TILE_8_UDG},
    {_TILE_9, _TILE_9_UDG},
    {_TILE_10, _TILE_10_UDG},
    {_TILE_11, _TILE_11_UDG},
    {_TILE_12, _TILE_12_UDG},
    {_TILE_13, _TILE_13_UDG},
    {_TILE_14, _TILE_14_UDG},
    {_TILE_15, _TILE_15_UDG},
    {_TILE_16, _TILE_16_UDG},
    {_TILE_17, _TILE_17_UDG},
    {_TILE_18, _TILE_18_UDG},
    {_TILE_19, _TILE_19_UDG},
    {_TILE_20, _TILE_20_UDG},
    {_TILE_21, _TILE_21_UDG},
    {_TILE_22, _TILE_22_UDG},
    {_TILE_23, _TILE_23_UDG},
    {_TILE_24, _TILE_24_UDG},
    {_TILE_25, _TILE_25_UDG},
    {_TILE_26, _TILE_26_UDG},
};

// #define REDEFINE_AT(addr) \
// { \
	// uint8_t i; \
	// \
	// for (i = 0; i < (sizeof(redefine_map)/sizeof(*redefine_map)); ++i) \
	// { \
		// memcpy((uint8_t *)(addr) + (redefine_map[i].ascii)*8, redefine_map[i].bitmap, 8); \
	// } \
// }


void REDEFINE_AT(void)
{
    uint16_t i;
	extern char _FONT_START__[];

    // for(i=0;i<240;++i)
    // {
        // POKE(_FONT_START__+i,i);
    // }
	for (i = 0; i < (sizeof(redefine_map)/sizeof(*redefine_map)); ++i)
	{ 
		memcpy((uint8_t *)(_FONT_START__) + (redefine_map[i].ascii)*8, redefine_map[i].bitmap, 8);
	} 
}


#if !defined(_XL_NO_UDG)
void set_udg(void)
{
	uint8_t *_CHBAS = (uint8_t *) 0x2F4;
	extern char _FONT_START__[];

	memcpy(_FONT_START__, (void *)0xE000, 512);
	
	/* modify your font at _FONT_START__, etc, then set the new font: */
	REDEFINE_AT();

	
	*_CHBAS = ((int)_FONT_START__ >> 8);  /* enable the new font */

    // {
        // uint16_t i;
        // for(i=0;i<240;++i)
        // {
            // POKE(_FONT_START__+i,i);
        // }
    // }

}
#endif

uint16_t BASE_ADDR;

#if defined(__ANTIC_MODE6_GRAPHICS)
uint8_t _atari_text_color;
#endif

// ; Hue values

// HUE_GREY        = 0
// HUE_GOLD        = 1
// HUE_GOLDORANGE  = 2
// HUE_REDORANGE   = 3
// HUE_ORANGE      = 4
// HUE_MAGENTA     = 5
// HUE_PURPLE      = 6
// HUE_BLUE        = 7
// HUE_BLUE2       = 8
// HUE_CYAN        = 9
// HUE_BLUEGREEN   = 10
// HUE_BLUEGREEN2  = 11
// HUE_GREEN       = 12
// HUE_YELLOWGREEN = 13
// HUE_YELLOW      = 14
// HUE_YELLOWRED   = 15

// ; Color defines, similar to c64 colors (untested)

// GTIA_COLOR_BLACK      = (HUE_GREY << 4)
// GTIA_COLOR_WHITE      = (HUE_GREY << 4 | 7 << 1)
// GTIA_COLOR_RED        = (HUE_REDORANGE << 4 | 1 << 1)
// GTIA_COLOR_CYAN       = (HUE_CYAN << 4 | 3 << 1)
// GTIA_COLOR_VIOLET     = (HUE_PURPLE << 4 | 4 << 1)
// GTIA_COLOR_GREEN      = (HUE_GREEN << 4 | 2 << 1)
// GTIA_COLOR_BLUE       = (HUE_BLUE << 4 | 2 << 1)
// GTIA_COLOR_YELLOW     = (HUE_YELLOW << 4 | 7 << 1)
// GTIA_COLOR_ORANGE     = (HUE_ORANGE << 4 | 5 << 1)
// GTIA_COLOR_BROWN      = (HUE_YELLOW << 4 | 2 << 1)
// GTIA_COLOR_LIGHTRED   = (HUE_REDORANGE << 4 | 6 << 1)
// GTIA_COLOR_GRAY1      = (HUE_GREY << 4 | 2 << 1)
// GTIA_COLOR_GRAY2      = (HUE_GREY << 4 | 3 << 1)
// GTIA_COLOR_LIGHTGREEN = (HUE_GREEN << 4 | 6 << 1)
// GTIA_COLOR_LIGHTBLUE  = (HUE_BLUE << 4 | 6 << 1)
// GTIA_COLOR_GRAY3      = (HUE_GREY << 4 | 5 << 1)
    
// #define SETCOLOR_LOW(reg, val) *((unsigned char *)12 + (reg)) = (val)

#if defined(__BACKGROUND_COLOR) && __BACKGROUND_COLOR==1
    #define _ATARI_BACKGROUND_COLOR GTIA_COLOR_WHITE
    #define _ATARI_EXTRA_COLOR GTIA_COLOR_BLACK
#else
    #define _ATARI_BACKGROUND_COLOR GTIA_COLOR_BLACK
    #define _ATARI_EXTRA_COLOR GTIA_COLOR_WHITE
#endif


void _XL_INIT_GRAPHICS(void)
{
	// Mode 12 with no last monochromatic lines (12+16)
	// _graphics(4+16);
    
    // #if defined(__USE_CYAN_YELLOW)
        // _setcolor_low(0,_gtia_mkcolor(HUE_REDORANGE,2));
        // _setcolor_low(1,_ATARI_EXTRA_COLOR);
        // _setcolor_low(2,GTIA_COLOR_CYAN);
        // _setcolor_low(3,GTIA_COLOR_YELLOW);
        // _setcolor_low(4, _ATARI_BACKGROUND_COLOR);
    // #elif defined(__USE_GREEN_YELLOW)
        // _setcolor_low(0,_gtia_mkcolor(HUE_REDORANGE,2));
        // _setcolor_low(1,_ATARI_EXTRA_COLOR);
        // _setcolor_low(2,GTIA_COLOR_YELLOW);
        // _setcolor_low(3,_gtia_mkcolor(HUE_GREEN  ,4));
        // _setcolor_low(4, _ATARI_BACKGROUND_COLOR);
    // #else
        // _setcolor_low(0,_gtia_mkcolor(HUE_REDORANGE,2));
        // _setcolor_low(1,_ATARI_EXTRA_COLOR);
        // _setcolor_low(2,GTIA_COLOR_CYAN);
        // _setcolor_low(3,_gtia_mkcolor(HUE_GREEN  ,4));
        // _setcolor_low(4, _ATARI_BACKGROUND_COLOR);
    // #endif

	#if !defined(_XL_NO_UDG)
	set_udg();
	#endif
    
    // BASE_ADDR = BASE_ADDR_VALUE;

    _setScreenColors();
    
    // {
        // uint16_t i;
        
        // for(i=0;i<1024;++i)
        // {
            // POKE(0xE000+i,255);
        // }
    // }
    // while(1){};
}


