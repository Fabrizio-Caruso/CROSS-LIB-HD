#include <peekpoke.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "graphics_settings.h"
#include "display_macros.h"

#include "6x8_chars.h"

#define BASE_ADDR 0xA000

#include "udg_map.h"


// #if defined(__BACKGROUND_COLOR) && __BACKGROUND_COLOR==1
    // #define ORIC_BACKGROUND_COLOR 23
    // #define ORIC_INK_COLOR 0
// #else
    // #define ORIC_BACKGROUND_COLOR 16
    // #define ORIC_INK_COLOR 3
// #endif

// void init_colors(void)
// {
    // POKE(0xBB80,0x1E);
	// uint8_t i;
	
	// Initialize colors 	
	// for(i=0;i<28;++i)
	// {
		// POKE(0xBB80+i*40,ORIC_BACKGROUND_COLOR);
		// POKE(0xBB81+i*40,ORIC_INK_COLOR); 
	// }
// }

#define TOTAL_TILES ((_XL_NUMBER_OF_TILES)+26+10+1)
// TODO: Pre-apply OR 64 to set tile data as a hires pattern 
uint8_t __oric__tiles[TOTAL_TILES][8] =
{
    _TILE_0_UDG,
    _TILE_1_UDG,
    _TILE_2_UDG,
    _TILE_3_UDG,
    _TILE_4_UDG,
    _TILE_5_UDG,
    _TILE_6_UDG,
    _TILE_7_UDG,
    _TILE_8_UDG,
    _TILE_9_UDG,
    _TILE_10_UDG,
    _TILE_11_UDG,
    _TILE_12_UDG,
    _TILE_13_UDG,
    _TILE_14_UDG,
    _TILE_15_UDG,
    _TILE_16_UDG,
    _TILE_17_UDG,
    _TILE_18_UDG,
    _TILE_19_UDG,
    _TILE_20_UDG,
    _TILE_21_UDG,
    _TILE_22_UDG,
    _TILE_23_UDG,
    _TILE_24_UDG,
    _TILE_25_UDG,
    _TILE_26_UDG,
    _TILE_27_UDG,
    _TILE_28_UDG,
    _TILE_29_UDG,
    _TILE_30_UDG,
    _TILE_31_UDG,
    _TILE_32_UDG,
    _TILE_33_UDG,
    _TILE_34_UDG,
    _TILE_35_UDG,
    _TILE_36_UDG,
    _TILE_37_UDG,
    _TILE_38_UDG,
    _TILE_39_UDG,
    _TILE_40_UDG,
    _TILE_41_UDG,
    _TILE_42_UDG,
    _TILE_43_UDG,
    _TILE_44_UDG,
    _TILE_45_UDG,
    _TILE_46_UDG,
    _TILE_47_UDG,
    _TILE_48_UDG,
    _TILE_49_UDG,
    _TILE_50_UDG,
    _TILE_51_UDG,
    _TILE_52_UDG,
    _TILE_53_UDG,
    _TILE_54_UDG,
    _TILE_55_UDG,
    _TILE_56_UDG,
    _TILE_57_UDG,
    _TILE_58_UDG,
    _TILE_59_UDG,
    _TILE_60_UDG,
    _TILE_61_UDG,
    _TILE_62_UDG,
    _TILE_63_UDG,
    _TILE_64_UDG,
    _TILE_65_UDG,
    _TILE_66_UDG,
    _TILE_67_UDG,
    _TILE_68_UDG,
    _TILE_69_UDG,
    _TILE_70_UDG,
    _TILE_71_UDG,
    _TILE_72_UDG,
    _TILE_73_UDG,
    _TILE_74_UDG,
    _TILE_75_UDG,
    _TILE_76_UDG,
    _TILE_77_UDG,
    _TILE_78_UDG,
    _TILE_79_UDG,
    _TILE_80_UDG,
    _TILE_81_UDG,
    _TILE_82_UDG,
    _TILE_83_UDG,
    _TILE_84_UDG,
    _TILE_85_UDG,
    _TILE_86_UDG,
    _TILE_87_UDG,
    _TILE_88_UDG,
    _TILE_89_UDG,
    _TILE_90_UDG,
    _TILE_A,
    _TILE_B,
    _TILE_C,
    _TILE_D,
    _TILE_E,
    _TILE_F,
    _TILE_G,
    _TILE_H,
    _TILE_I,
    _TILE_J,
    _TILE_K,
    _TILE_L,
    _TILE_M,
    _TILE_N,
    _TILE_O,
    _TILE_P,
    _TILE_Q,
    _TILE_R,
    _TILE_S,
    _TILE_T,
    _TILE_U,
    _TILE_V,
    _TILE_W,
    _TILE_X,
    _TILE_Y,
    _TILE_Z,
    _TILE_DIGIT_0,
    _TILE_DIGIT_1,
    _TILE_DIGIT_2,
    _TILE_DIGIT_3,
    _TILE_DIGIT_4,
    _TILE_DIGIT_5,
    _TILE_DIGIT_6,
    _TILE_DIGIT_7,
    _TILE_DIGIT_8,
    _TILE_DIGIT_9,
    _SPACE_TILE
};


void preprocess_tiles(void)
{
    uint8_t i;
    uint8_t j;
    
    for(i=0;i<TOTAL_TILES;++i)
    {
        for(j=0;j<8;++j)
        {
            __oric__tiles[i][j]|=64;
        }
    }
}

void _oric_hires_draw(uint8_t x, uint8_t y, uint8_t tile)
{
    uint8_t i;
    uint16_t x_offset;
    
    for(i=0,x_offset = BASE_ADDR+x+320U*(uint16_t)y; i<8;++i, x_offset+=40)
    {
        POKE(x_offset,__oric__tiles[tile][i]);
    }
}


void _oric_hires_delete(uint8_t x, uint8_t y)
{
    uint8_t i;
    uint16_t x_offset;
    
    for(i=0,x_offset = BASE_ADDR+x+320U*(uint16_t)y; i<8;++i, x_offset+=40)
    {
        POKE(x_offset,64);
    }
}

void _XL_INIT_GRAPHICS(void)
{
    // REDEFINE_AT(((uint8_t *)BASE_ADDR));

    // init_colors();
    uint16_t i;
    preprocess_tiles();
    // POKE(0x026A,2); // turn flashing cursor off

    for(i=0;i<8192;++i)
    {
        POKE(BASE_ADDR+i,16);
    };
    
    POKE(0xBFDF ,0x1E); // Set screen to hires


    // _setScreenColors();
}
