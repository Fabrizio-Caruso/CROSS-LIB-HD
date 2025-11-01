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

#ifndef _UDG_SETTINGS
#define _UDG_SETTINGS

#define _TILE_0  (0x2A - _Z88DK_SPRITE_OFFSET)
#define _TILE_1  (0x3C - _Z88DK_SPRITE_OFFSET)
#define _TILE_2  (0x3D - _Z88DK_SPRITE_OFFSET) 
#define _TILE_3  (0x3E - _Z88DK_SPRITE_OFFSET)


#define _TILE_9  (0x3F-_Z88DK_SPRITE_OFFSET)

// YELLOW
#define _TILE_7  (0x27 - _Z88DK_SPRITE_OFFSET)
#define _TILE_12 (0x26 -_Z88DK_SPRITE_OFFSET)
#define _TILE_13 (0x2B -_Z88DK_SPRITE_OFFSET)
#define _TILE_25 (0x24 - _Z88DK_SPRITE_OFFSET)

// GREEN
#define _TILE_8  (0x2C - _Z88DK_SPRITE_OFFSET)

#define _TILE_17 (0x25 - _Z88DK_SPRITE_OFFSET)

#define _TILE_18 (0x3B - _Z88DK_SPRITE_OFFSET)

// RED
#define _TILE_5  (0x29 - _Z88DK_SPRITE_OFFSET)

// CYAN
#define _TILE_10 (0x21 - _Z88DK_SPRITE_OFFSET)
#define _TILE_11 (0x23 - _Z88DK_SPRITE_OFFSET)

// WHITE
#define _TILE_4  (0x28 - _Z88DK_SPRITE_OFFSET)

#if defined(__MO5__)||defined(__TO7__)|| defined(__COCO3__) || defined(__COCO__)||defined(__DRAGON__)
	#define _TILE_6 (0x3A - _Z88DK_SPRITE_OFFSET)
#else
	#define _TILE_6 (0x5B - _Z88DK_SPRITE_OFFSET)
#endif

#define _TILE_14 (0x22 - _Z88DK_SPRITE_OFFSET)

#define _TILE_15 (0x2E - _Z88DK_SPRITE_OFFSET )

#define _TILE_16 (0x2F - _Z88DK_SPRITE_OFFSET)


// 0x50 -> 0
#if defined(__MO5__)||defined(__TO7__)
    #define _TILE_19 49
    #define _TILE_20 50
    #define _TILE_21 51
    #define _TILE_22 52
    #define _TILE_23 53
    #define _TILE_24 54
    #define _TILE_26 (_TILE_8+1)
#elif defined(__COCO3__) || defined(__COCO__)||defined(__DRAGON__)
    #define _TILE_19 (_TILE_16+2)
    #define _TILE_20 (_TILE_16+3)
    #define _TILE_21 (_TILE_16+4)
    #define _TILE_22 (_TILE_16+5)
    #define _TILE_23 (_TILE_16+6)
    #define _TILE_24 (_TILE_16+7)
    #define _TILE_26 (_TILE_8+1)
#else
    #define _TILE_19 (0x3A - _Z88DK_SPRITE_OFFSET)
    #define _TILE_20 (0x40 - _Z88DK_SPRITE_OFFSET)
    #define _TILE_21 (0x5C - _Z88DK_SPRITE_OFFSET)
    #define _TILE_22 (0x5D - _Z88DK_SPRITE_OFFSET)
    #define _TILE_23 (0x5E - _Z88DK_SPRITE_OFFSET)
    #define _TILE_24 (0x5F - _Z88DK_SPRITE_OFFSET)
    #define _TILE_26 (_TILE_8+1)
#endif

#define _TILE_27 ('z'-26)
#define _TILE_28 ('z'-25)
#define _TILE_29 ('z'-24)
#define _TILE_30 ('z'-23)
#define _TILE_31 ('z'-22)
#define _TILE_32 ('z'-21)
#define _TILE_33 ('z'-20)
#define _TILE_34 ('z'-19)
#define _TILE_35 ('z'-18)
#define _TILE_36 ('z'-17)
#define _TILE_37 ('z'-16)
#define _TILE_38 ('z'-15)
#define _TILE_39 ('z'-14)
#define _TILE_40 ('z'-13)
#define _TILE_41 ('z'-12)
#define _TILE_42 ('z'-11)
#define _TILE_43 ('z'-10)
#define _TILE_44 ('z'-9)
#define _TILE_45 ('z'-8)
#define _TILE_46 ('z'-7)
#define _TILE_47 ('z'-6)
#define _TILE_48 ('z'-5)
#define _TILE_49 ('z'-4)
#define _TILE_50 ('z'-3)
#define _TILE_51 ('z'-2)
#define _TILE_52 ('z'-1)
#define _TILE_53 'z'
#define _TILE_54 ('z'+1)
#define _TILE_55 ('z'+2)
#define _TILE_56 ('z'+3)
#define _TILE_57 ('z'+4)
#define _TILE_58 ('z'+5)
#define _TILE_59 ('z'+6)
#define _TILE_60 ('z'+7)
#define _TILE_61 ('z'+8)
#define _TILE_62 ('z'+9)
#define _TILE_63 165
#define _TILE_64 166
#define _TILE_65 167
#define _TILE_66 168
#define _TILE_67 169
#define _TILE_68 170
#define _TILE_69 171
#define _TILE_70 172
#define _TILE_71 173
#define _TILE_72 174
#define _TILE_73 175
#define _TILE_74 176
#define _TILE_75 177
#define _TILE_76 178
#define _TILE_77 179
#define _TILE_78 180
#define _TILE_79 181
#define _TILE_80 182
#define _TILE_81 183
#define _TILE_82 184
#define _TILE_83 185
#define _TILE_84 186
#define _TILE_85 187
#define _TILE_86 188
#define _TILE_87 189
#define _TILE_88 190
#define _TILE_89 191
#define _TILE_90 192
#define _TILE_91 193
#define _TILE_92 194
#define _TILE_93 195
#define _TILE_94 196
#define _TILE_95 197
#define _TILE_96 198
#define _TILE_97 199
#define _TILE_98 200
#define _TILE_99 201


#endif // _UDG_SETTINGS


