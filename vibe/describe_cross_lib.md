# Cross-Lib Game Programming Guide

## Header and Initialization

At the start of your `main.c` file, include the cross-lib header:
```c
#include "cross_lib.h"
```

Initialize your program with these commands:
```c
void _XL_INIT_GRAPHICS(void);
void _XL_INIT_INPUT(void);
void _XL_INIT_SOUND(void);
```

## Coordinate System

Coordinates must respect the following limits:
- 0 ≤ x ≤ XSize-1
- 0 ≤ y ≤ YSize-1

Where XSize and YSize are macros with ranges:
- 6 ≤ XSize ≤ 160
- 4 ≤ YSize ≤ 160

## Screen Output Functions

### Drawing Tiles
```c
void _XL_DRAW(uint8_t x, uint8_t y, uint8_t tile_id, uint8_t color_id);
```
Draws the tile `tile_id` at position (x,y) with color `color_id`.
Valid tile IDs: `_TILE_0`, `_TILE_1`, `_TILE_2`, ..., `_TILE_26`

### Deleting Tiles
```c
void _XL_DELETE(uint8_t x, uint8_t y);
```
Deletes the tile at position (x,y)

### Clearing Screen
```c
void _XL_CLEAR_SCREEN(void);
```
Clears the entire screen

## Color Constants

Only use these color values:
- `_XL_WHITE`
- `_XL_RED`
- `_XL_CYAN`
- `_XL_GREEN`
- `_XL_YELLOW`
- `_XL_BLUE`
- `_XL_MAGENTA`

To change text color before `_XL_PRINTD` or `_XL_PRINT`:
```c
void _XL_SET_TEXT_COLOR(uint8_t color);
```

## Displaying Values

### Display Numbers with Fixed Digits
```c
void _XL_PRINTD(uint8_t x, uint8_t y, uint8_t number_of_digits, uint16_t value);
```
Displays values with a given fixed number of digits (padding with zeros on the left if necessary)

### Text Output
```c
void _XL_PRINT(uint8_t x, uint8_t y, char * string);
```
Displays text using only capital letters, digits, and space characters

### Single Character Output
```c
void _XL_CHAR(uint8_t x, uint8_t y, char ch);
```

## Input Handling

Poll the input device with:
```c
uint8_t _XL_INPUT(void);
```

Check specific input states:
```c
uint8_t _XL_LEFT(uint8_t input);
uint8_t _XL_RIGHT(uint8_t input);
uint8_t _XL_UP(uint8_t input);
uint8_t _XL_DOWN(uint8_t input);
uint8_t _XL_FIRE(uint8_t input);
```

Example usage:
```c
uint8_t input = _XL_INPUT();
if (_XL_LEFT(input)) { /* LEFT key was pressed */ }
```

Wait for a key press:
```c
void _XL_WAIT_FOR_INPUT(void);
```

## Timing and Delays

### Sleep Function
```c
void _XL_SLEEP(uint8_t sec);
```
Waits for a given number of seconds

### Slow Down Function
```c
void _XL_SLOW_DOWN(uint16_t slowdown);
```
Waits for a number of loops. Use with multiples of `_XL_SLOW_DOWN_FACTOR` macro:
```c
_XL_SLOW_DOWN(_XL_SLOW_DOWN_FACTOR);
```

## Sound Functions

### Short Sounds
```c
void _XL_PING_SOUND(void);
void _XL_TOCK_SOUND(void);
void _XL_TICK_SOUND(void);
void _XL_SHOOT_SOUND(void);
```

### Long Blocking Sounds
```c
void _XL_EXPLOSION_SOUND(void);
void _XL_ZAP_SOUND(void);
```

## Random Number Generation

```c
uint16_t _XL_RAND(void);
```
Generates a non-negative integer in the range [0, 32767]

## Programming Rules and Constraints

### Include Files
- Do not include `stdint.h`
- Include only `cross_lib.h`
- No need to prototype `_XL_INIT_GRAPHICS()`, `_XL_INIT_INPUT()`, `_XL_INIT_SOUND()`

### Data Types
- Use strict ANSI C89
- Use only `uint8_t` and `uint16_t` for integers
- For signed integers, use `short`
- All local variable declarations must be at the beginning of functions

### Screen Operations
- Do not use `_XL_DRAW` or `_XL_DELETE` on tiles that have not changed
- Use `_XL_PRINTD` to display any integer value (score, lives, etc.)

### Game Loop
- Write an infinite main loop so that the game restarts after completion
- Do not redefine `_XL_DRAW`, `_XL_DELETE`, `_XL_SLOW_DOWN_FACTOR`, `XSize`, `YSize`

### Constants
- Do not redefine `_XL_DRAW`, `_XL_DELETE`, `_XL_SLOW_DOWN_FACTOR`, `XSize`, `YSize`
- Do not prototype `_XL_INIT_GRAPHICS()`, `_XL_INIT_INPUT()`, `_XL_INIT_SOUND()`
- Do not redefine any existing constants or functions

