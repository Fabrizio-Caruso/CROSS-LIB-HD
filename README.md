# CROSS-LIB-HD
CROSS-LIB-HD is Cross-Lib with a higher number of tiles.

**REMARK**
This is still a work process.

## CROSS-LIB-HD vs CROSS-LIB
Both CROSS-LIB and CROSS-LIB-HD have 37 fixed (26 letters, 10 digits and 1 empty tile). The main difference is the total number of supported tiles (fixed and redefinable).

- **CROSS-LIB-HD**: at least 128 total tiles, i.e., 91 redefinable tiles,
- **CROSS-LIB**: supports at most 64 total tiles: i.e.,  27 redefinable tiles.

### Same targets as CROSS-LIB
In principle it is possible to support the same set of targets as CROSS-LIB even for targets that cannot have 91 redefinable tiles in the same colors and video modes as the ones used by CROSS-LIB

We can use:

- __fewer colors__ -> When a given target cannot have 91 redefinable tiles for each available color in CROSS-LIB, it may be possible to have those tiles with fewer color variations or in a different screen mode.
- __ASCII tiles__ -> If there were a target with graphics that cannot have 91 redefinable monochromatic tiles, the target can still use 91 ASCII characters (no UDG mode).

## Compatible with CROSS-LIB
Source code of games and programs written with CROSS-LIB are compatible with CROSS-LIB-HD.

More information on Cross-Lib is here: https://github.com/Fabrizio-Caruso/CROSS-LIB


## CURRENTLY TESTED WORKING TARGETS
- Agon Light
- Amstrad CPC
- Amstrad NC100/NC150
- Amstrad NC200
- Bandai RX78
- Bondwell 2
- Camputers Lynx
- Casio FP-1100
- Casio PV-2000
- CCE MC-1000
- Commodore 128 Z80 40 column
- Coleco Vision
- Exidy Sorcerer
- GameGear
- Galaksija Plus
- Genius Leader GL6000SL
- Hector HR
- Memotech MTX 500
- Memotech MTX 512
- Microkey Primo
- Myvision
- MSX 1/2
- NEC PC-6001
- NEC PC-8801
- Hanimex Pencil II
- PK-01 LVIV/LVOV
- Robotron KC-85/2/3/4
- Robotron Z1013 with KRT
- Robotron Z9001 with KRT
- Tatung Einstein
- Tesla Ondra
- Sam Coupé
- Samsung SPC-1000
- Sanyo PHC-25
- Sega Master System
- Sega SC 3000
- Sega SG 1000
- Super-80r (VDUEB)
- Sony SMC-777
- Sord M5
- Spectravideo SVI
- VG 5000
- Vtech Laser 500
- Vtech VZ200
- Z80 TV GAME
- ZX Spectrum 16/48/128

## More features?
In the future a few extra features may be added but the highest priority goes to the number of tiles.


