# CROSS-LIB-HD
CROSS-LIB-HD is CROSS-LIB with a higher number of tiles but slightly larger binaries and fewer colors on a couple of targets.

More information on CROSS-LIB is here: https://github.com/Fabrizio-Caruso/CROSS-LIB

**REMARK**
This is still a work process.

## CROSS-LIB-HD vs CROSS-LIB
Both CROSS-LIB and CROSS-LIB-HD have 37 fixed (26 letters, 10 digits and 1 empty tile). The main difference is the total number of supported tiles (fixed and redefinable).

- **CROSS-LIB-HD**: at least 128 total tiles, i.e., 91 redefinable tiles,
- **CROSS-LIB**: supports at most 64 total tiles: i.e.,  27 redefinable tiles.

### Same targets as CROSS-LIB
It is possible to support the same set of targets as CROSS-LIB even for targets that cannot have 91 redefinable tiles in the same colors and video modes as the ones used by CROSS-LIB.

We can use:

- __fewer colors__ -> When a given target cannot have 91 redefinable tiles for each available color in CROSS-LIB, it may be possible to have those tiles with fewer color variations or in a different screen mode.
- __ASCII tiles__ -> If there were a target with graphics that cannot have 91 redefinable monochromatic tiles, the target can still use 91 ASCII characters (no UDG mode).


## Compatible with CROSS-LIB
Source code of games and programs written with CROSS-LIB are compatible with CROSS-LIB-HD.

More information on Cross-Lib is here: https://github.com/Fabrizio-Caruso/CROSS-LIB


## CURRENTLY TESTED WORKING TARGETS

All 91 redefined tiles have been tested on the following targets.

### Native compiler (host CPU) with redefined tiles (UDGs) 
- Terminal

### ACK (Intel 8088/8086) with redefined tiles (UDGs)
- MS-DOS 8088/8086
- PC 8088/8086 [bare metal]

### CC65 (MOS 6502) with redefined tiles (UDGs)
- Atari 7800
- Atari 8-bit
- Atari Lynx
- Bit Corporation Gamate
- Commander X16
- Commodore 128 [MOS 8502] [80 column display]
- Commodore 16 [16k, 32k/64k]
- Commodore 64
- Commodore VIC 20 [unexpanded, +3k, +8k/16k/24k]
- Creativision
- Nintendo NES
- PC-Engine
- Watara Supervision

### CMOC (Motorola 6809) with redefined tiles (UDGs)
- CoCo 1/2
- CoCo 3
- Dragon 32/64
- Thomson Mo5/Thomson Mo6/Olivetti Prodest PC 128
- Thomson To7/To8/To9

### GCC4TI (TMS9900) with redefined tiles (UDGs)
- Texas Instruments TI99/4A

### LCC1802 (RCA 1802) with redefined tiles (UDGs)
- COMX-35
- Pecom 32/64
- Microboard System [PAL] [128 chars]

### VBCC (MOS 6502) with redefined tiles (UDGs)
- BBC Master / Olivetti Prodest PC 128S
- BBC Micro

### Z88DK (Z80 and Intel 8080) with redefined tiles (UDGs)
- Agon Light
- Amstrad CPC
- Amstrad GX4000
- Amstrad NC100/NC150
- Amstrad NC200
- Aquarius Plus
- Bandai RX78
- Bit Corporation Bit90
- Bondwell 2
- Camputers Lynx
- Casio FP-1100
- Casio PV-1000
- Casio PV-2000
- CCE MC-1000
- Commodore 128 [Zilog 80] [40 column display]
- Coleco Adam
- Coleco Vision
- EACA Colour Genie EG2000
- Epson PX-4
- Epson PX-8
- Excalibur 64
- Exidy Sorcerer
- GameGear
- Galaksija Plus
- Game Boy
- Genius Leader GL6000SL
- Hector HR
- Hübler Grafik-MC
- Jupiter Ace
- LM-80C
- Memotech MTX 500
- Memotech MTX 512
- MicroBee
- MicroBee Premium
- MicroData Multi-8
- Microkey Primo
- Myvision
- MSX 1
- MSX 2
- NABU PC
- NEC PC-6001
- NEC PC-8801
- Hanimex Pencil II
- PK-01 LVIV/LVOV
- Robotron KC-85/2/3/4
- Robotron Z1013 with KRT
- Robotron Z9001 with KRT
- Tatung Einstein TC-01
- Tatung Einstein 256
- Tesla Ondra
- Tesla PMD 85
- Sam Coupé
- Samsung SPC-1000
- Sanyo PHC-25
- Sega Master System
- Sega SC 3000
- Sega SG 1000
- Seiko MAP-1010
- Sharp X1
- Sinclair ZX81
- Sinclair ZX Spectrum 128K
- Sinclair ZX Spectrum 16K/48K
- Sinclair ZX Spectrum Next
- Super-80r (VDUEB)
- Sony SMC-777
- Sord M5
- Spectravideo SVI
- Texas Instruments TI-83
- TIKI-100
- TIM-011
- Timex TS2068
- Vector-06C
- VG 5000
- Visual 1050
- Vtech Laser 500
- Vtech VZ200
- Z80 TV GAME



## More features?
In the future a few extra features may be added but the highest priority goes to the increased number of tiles.


