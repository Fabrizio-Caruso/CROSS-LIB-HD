#ifndef _CONIO_GRAPHICS_H
#define _CONIO_GRAPHICS_H

#if defined(__NCURSES__)
    #define put_char(c) do { addch(c); refresh(); } while(0)
    #define move_cursor(x,y) do { move(y,x); refresh(); } while(0) 
#else
    #define put_char(c) cputc(c)
    #define move_cursor(x,y) gotoxy(x,y) 
#endif


#if !defined(_XL_NO_COLOR)

    #if defined(__FP1100__)
    
        #define _XL_DRAW(x,y,tile,color) \
        do \
        { \
            move_cursor((X_OFFSET+(x)),(Y_OFFSET+(y))); \
            _XL_SET_TEXT_COLOR(color); \
            put_char(tile); \
            move_cursor((X_OFFSET+((XSize)-1)),(Y_OFFSET+((YSize)))); \
            put_char(' '); \
        } \
        while(0)
            
    #else
        #if defined(__NO_BOTTOM)
            #define _XL_DRAW(x,y,tile,color) \
            do \
            { \
                if(y<YSize-1) \
                { \
                    move_cursor((X_OFFSET+(x)),(Y_OFFSET+(y))); \
                    _XL_SET_TEXT_COLOR(color); \
                    put_char(tile); \
                } \
            } \
            while(0)
        #else
            #define _XL_DRAW(x,y,tile,color) \
            do \
            { \
                move_cursor((X_OFFSET+(x)),(Y_OFFSET+(y))); \
                _XL_SET_TEXT_COLOR(color); \
                put_char(tile); \
            } \
            while(0)
            
        #endif
    #endif


#else

	#if defined(__NO_BOTTOM)
		#define _XL_DRAW(x,y,tile,color) \
		do \
		{ \
			if(y<YSize-1) \
			{ \
				move_cursor((X_OFFSET+x),(Y_OFFSET+y)); \
				put_char(tile); \
			} \
		} \
		while(0)
	#else

		#define _XL_DRAW(x,y,tile,color) \
		do \
		{ \
			move_cursor((X_OFFSET+x),(Y_OFFSET+y)); \
			put_char(tile); \
		} \
		while(0)
    #endif

#endif

#if defined(__NO_BOTTOM)
	#define _XL_DELETE(x,y) \
		do \
		{ \
			if(y<YSize-1) \
			{ \
				move_cursor((X_OFFSET+x),(Y_OFFSET+y)); \
				put_char(_SPACE); \
			} \
		} \
		while(0)
#else
	
	#define _XL_DELETE(x,y) \
		do \
		{ \
			move_cursor((X_OFFSET+x),(Y_OFFSET+y)); \
			put_char(_SPACE); \
		} \
		while(0)

#endif
		
#endif // _CONIO_GRAPHICS_H



