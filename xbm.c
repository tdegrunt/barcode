/*
 * XBM 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "xbm.h"

/**
 * newXBM
 *
 * XBM 'constructor'
 *
 * @param	width		width of the resulting XBM
 * @param	height	height of the resulting XBM
 */
XBM *newXBM( int width, int height ) {
   
   int xByte, y;
   
   XBM *result = malloc( sizeof( XBM ) );
   result->width = width;
   result->height = height;
   result->byteWidth = ( width + 7 ) / 8;
   result->data = malloc( height * result->byteWidth );

   for( y = 0; y < result->height; y++ ) {
      for( xByte = 0; xByte < result->byteWidth; xByte++ ) {
   		result->data[(result->byteWidth * y) + xByte] = 0x00;
   	}
	}

   
   return result;
   
}

/**
 * freeXBM
 *
 * XBM 'destructor'
 *
 * @param	xbm	reference to the XBM to be cleared
 */
void freeXBM( XBM *xbm ) {
 
   free( xbm->data );
   free( xbm );
     
}

/**
 * xbmGetByte
 *
 * Returns the byte at a certain xByte, y-pixel location in a XBM
 *
 * @param	xbm		reference to a XBM
 * @param	xByte		x-byte location in the XBM
 * @param	y			y-pixel location in the XBM
 * 
 * @returns	the byte at the requested location, or zero if out-of-range
 */
int xbmGetByte( XBM *xbm, int xByte, int y ) {

   if( ( xByte < 0 ) || ( xByte >= xbm->byteWidth ) || 
       ( y < 0 ) || ( y > xbm->height ) ) {
         return 0;
   }
   
   return xbm->data[(xbm->byteWidth * y) + xByte]; 
   
}

/**
 * xbmGet
 *
 * Returns the bit-value at a certain x-pixel, y-pixel location in a XBM
 *
 * @param	xbm		reference to a XBM
 * @param	x			x-pixel location in the XBM
 * @param	y			y-pixel location in the XBM
 * 
 * @returns	the bit-value at the requested location
 */
int xbmGet( XBM *xbm, int x, int y ) {
	
	int xByte = x >> 3;
	int xBit = x & 0x7;
	int byteValue = xbmGetByte( xbm, xByte, y );
	
	return( byteValue & ( 1 << xBit )) >> xBit;
		
}

/**
 * xbmSet
 *
 * Sets the bit-value at a certain x-pixel, y-pixel location in a XBM
 *
 * @param	xbm		reference to a XBM
 * @param	x			x-pixel location in the XBM
 * @param	y			y-pixel location in the XBM
 * @param	value		value of the bit you want to set
 */
void xbmSet( XBM *xbm, int x, int y, int value ) {
	
	int xByte = x >> 3;
	int xBit = x & 0x7;

	if ( ( x < 0 ) || ( x >= xbm->width ) || ( y < 0 ) || ( y >= xbm->height ) ) {
		return;
   }

	if ( value ) {
		xbm->data[xbm->byteWidth * y + xByte] |= 1 << xBit;
   } else {
		xbm->data[xbm->byteWidth * y + xByte] &= ~(1 << xBit);
	}
	
}

/**
 * xbmCopyRect
 *
 * Copies (part of) a XBM to another XBM
 *
 * @param	to			reference to the destination XBM
 * @param	dx			destination x-pixel location in the destination XBM
 * @param	dy			destination y-pixel location in the destination XBM
 * @param	from		reference to the source XBM
 * @param	sx			source x-pixel location in the source XBM
 * @param	sy			source y-pixel location in the source XBM
 * @param	width		width of the rect to be copied
 * @param	height	height of the rect to be copied
 */
void xbmCopyRect( XBM *to, int dx, int dy, XBM *from, int sx, int sy, int width, int height ) {

	int x, y;

	for( y = 0; y < height; y++ ) {
		for( x = 0; x < width; x++ ) {
			xbmSet( to, x + dx, y + dy, xbmGet( from, x + sx, y + sy ) );
		}
	}
}

/**
 * xbmHline
 *
 * Draws an horizontal line in a XBM
 *
 * @param	xbm		reference to a XBM
 * @param	y			y-pixel location in the XBM
 * @param	x1			from x-pixel location in the XBM
 * @param	x2			to x-pixel location in the XBM
 * @param	value		value of the bit you want to set
 */
void xbmHline( XBM *xbm, int y, int x1, int x2 ) {
	while( x1 <= x2 ) {
		xbmSet( xbm, x1, y, 1 );
		x1++;
	}
}

/**
 * xbmVline
 *
 * Draws an vertical line in a XBM
 *
 * @param	xbm		reference to a XBM
 * @param	x			y-pixel location in the XBM
 * @param	y1			from y-pixel location in the XBM
 * @param	y2			to y-pixel location in the XBM
 * @param	value		value of the bit you want to set
 */
void xbmVline( XBM *xbm, int x, int y1, int y2 ) {
	while( y1 <= y2 ) {
		xbmSet( xbm, x, y1, 1 );
		y1++;
	}
}

/**
 * xbmDrawChar5x8
 *
 * Draws an charater in a XBM
 *
 * @param	xbm		reference to a XBM
 * @param	x			x-pixel location in the XBM
 * @param	y			y-pixel location in the XBM
 * @param	c			character to draw
 */
void xbmDrawChar5x8( XBM *xbm, int x, int y, char c ) {
    xbmCopyRect( xbm, x, y, &font5x8, 0, c * 8, 5, 8 );
}

/**
 * xbmDrawString5x8
 *
 * Draws an string in a XBM
 *
 * @param	xbm		reference to a XBM
 * @param	x			x-pixel location in the XBM
 * @param	y			y-pixel location in the XBM
 * @param	str		string to draw
 */
void xbmDrawString5x8( XBM *xbm, int x, int y, char *str ) {

	int origx = x;

	while (*str != '\0') {
		char c = *str;
		
		if (c == '\n')	{
			x = origx;
			y += 8;
		} else {
			if ( c < ' ' ) {
				c = ' ';
			}

			xbmDrawChar5x8( xbm, x, y, c );
			x += 5;
		}
		
		str++;
	}
}

/**
 * xbmSaveXBM
 *
 * Saves a XBM
 *
 * @param	xbm		reference to a XBM
 * @param	name		name of the XBM
 * @param	comment	comment to be written in the XBM file
 */
void xbmSaveXBM( XBM *xbm, char *name, char *comment ) {
 
   int xByte, y, column;
 
   printf( "#define %s_width %d\n", name, xbm->width );  
   printf( "#define %s_height %d\n", name, xbm->height );  
   printf( "static char %s_bits[] = {\n   ", name );
   
   column = 0;
   
   for( y = 0; y < xbm->height; y++ ) {
   
      for( xByte = 0; xByte < xbm->byteWidth; xByte++ ) {
       
         printf( "0x%02x", xbmGetByte( xbm, xByte, y ) );
         if( ( y < xbm->height-1 ) || ( xByte < xbm->byteWidth-1 ) ) {
         	printf( ", " );	
         }
         
         column++;
         
         if( column == XBM_OUTPUT_DATA_COLUMNS ) {
         	printf( "\n   " );
         	column = 0;	
         }
         
      }   
      
   }
   
   printf( "\n};\n" );
   printf( "/* %s */\n", comment );
}
