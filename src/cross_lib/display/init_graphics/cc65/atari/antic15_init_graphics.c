#if !defined(__ATARI5200__)
#include <atari.h>
#else
#include <atari5200.h>
#endif

#define SCREEN_WIDTH 40
#define CHAR_HEIGHT 8
#define CHAR_WIDTH 2

char nibble2byte[16] = {
	0x00, 0x03, 0x0C, 0x0F,
	0x30, 0x33, 0x3C, 0x3F,
	0xC0, 0xC3, 0xCC, 0xCF,
	0xF0, 0xF3, 0xFC, 0xFF
};

char background_mask = 0x00;
char foreground_mask = 0xFF;

void outc_left(const char *src, char *dest)
{
	char i, n, c;
	for (i=0; i<8; i++)
	{
		c = *src++;
		n = nibble2byte[c >> 4];
		c = ((n ^ 0xFF) & background_mask) | (n & foreground_mask);
		*dest = c;
		dest += SCREEN_WIDTH;
		// *dest = c;
		// dest += SCREEN_WIDTH;
	}
}

void outc_right(const char *src, char *dest)
{
	char i, n, c;
	for (i=0; i<8; i++)
	{
		c = *src++;
		n = nibble2byte[c & 15];
		c = ((n ^ 0xFF) & background_mask) | (n & foreground_mask);
		*dest = c;
		dest += SCREEN_WIDTH;
		// *dest = c;
		// dest += SCREEN_WIDTH;
	}
}

void output_char(char c)
{
	char *src, *dest;

    if (c >= 32 && c <= 95) c = c - 32;
    if (c >= 96 && c <= 127) c = (c + 64) & 127;
#if !defined(__ATARI5200__)
    src = (char *)(OS.chbas << 8) + (8 * c);
#else
    src = (char *)(0xF800 + (8 * c));
#endif
	dest = OS.savmsc;
	outc_left(src, dest);
	outc_right(src, ++dest);
	OS.savmsc = ++dest;
}

void output_str(const char *s)
{
	char c;
	for (c = *s; c != 0; c = *(++s))
	{
		output_char(c);
	}		
}

void set_position(char x, char y)
{
	char *dlist;
	dlist = (char *)(OS.sdlst);
	OS.savmsc = (char *)(*(unsigned int *)(dlist+4));
	OS.savmsc += (CHAR_HEIGHT * SCREEN_WIDTH * y);
	OS.savmsc += (x * CHAR_WIDTH);
}

void set_back_color(char c)
{
	background_mask = 0x55 * (c & 3);
}

void set_fore_color(char c)
{
	foreground_mask = 0x55 * (c & 3);
}

#if !defined(__ATARI5200__)
void getkey(void)
{
	OS.ch = 0xFF;
	while (OS.ch == 0xFF);
	OS.ch = 0xFF;
}
#else
extern void _graphics(char mode);
#endif




// void main(void)
void _XL_INIT_GRAPHICS(void)
{
	char i;
	char *msg = "Hi World!";

    _graphics(15+16);

	OS.color0 = 0x0E; // White
	OS.color1 = 0xD6; // Green
	OS.color2 = 0x86; // Blue
	OS.color4 = 0x00; // Black
	
	for (i=0; i<3; i++)
	{
		set_position(0, i);
		set_back_color(0);
		set_fore_color(i+1);
		output_str(msg);

		set_position(10, i);
		set_back_color(1);
		set_fore_color(i==0 ? 0 : i+1);
		output_str(msg);

		set_position(0, 4+i);
		set_back_color(2);
		set_fore_color(i==2 ? 3 : i);
		output_str(msg);

		set_position(10, 4+i);
		set_back_color(3);
		set_fore_color(i);
		output_str(msg);
	}



#if !defined(__ATARI5200__)
	getkey();
#else
	while (1);
#endif
}

// int main(void)
// {
    // _XL_INIT_GRAPHICS();
// }