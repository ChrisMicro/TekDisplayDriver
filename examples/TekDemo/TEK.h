#ifndef __TEK_H__
#define __TEK_H__
// ********************************************************
// TEK4010/4014 basic 10bit commands library
// For details consult the TEK4010/4014 manual
// Pito 7/2017 for stm32duino
// ********************************************************


// Colors for print, plot, dot
#define black 0
#define red 1
#define green 2
#define yellow 3
#define blue 4
#define magenta 5
#define cyan 6
#define white 7

// Line styles
#define solid 0
#define dotted 1
#define dash_dotted 2
#define short_dashed 3
#define long_dashed 4

// Font sizes
#define large 0
#define normal 1
#define small 2
#define smallest 3

class TEK
{
	public:
	void Tekcls();


	void Tekcolor(uint8_t color) ;	// Select a color (0-7)


	void Tekgraph(uint8_t style) ;	// Switch to graphical mode with a line style (0-4)
	// Select a font size (0-3) for printing alphanumeric strings
	// The actual font type has to be set in the Emulator
	void Tekfont(uint8_t fontsize);
	// Normal style lines (0-4)
	void Tekstyle(uint8_t style) ;
	// Bold style lines (??)
	void Tekstyleb(uint8_t style) ;

	// Switch to alphanumeric mode
	void Tekalpha() ;
	// Draw a point as a small cross (??)
	void Tekpoint(uint16_t x, uint16_t y) ;

	// Draw a single dot
	void Tekdot(uint16_t x, uint16_t y) ;

	// Draw a line from (x1, y1) to (x2, y2)
	void Tekline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) ;

	// Continue with drawing a line to (x1, y1)
	void Tekplot(uint16_t x1, uint16_t y1) ;

	// Locate a point where to print a string
	void Teklocate(uint16_t x1, uint16_t y1) ;
	// Draw a box with left bottom corner at (bx, by) and top right corner at (tx, ty)
	void Tekbox(uint16_t bx, uint16_t by, uint16_t tx, uint16_t ty);

	// Draw small sprites
	void Teksprite(char* sprite);

	// Go to the Graphics-IN mode
	void Tekgin();
};
#endif
